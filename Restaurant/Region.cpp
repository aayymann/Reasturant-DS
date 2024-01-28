#include "Region.h"
#include<fstream>


Region::Region(): PromotionLimit(0), AvgWaitingTime(0), AvgServiceTime(0), NumNormal(0), NumVIP(0), NumFrozen(0),
NumNormalMotors(0), NumFrozenMotors(0), NumFastMotors(0), NumRestingMotors(0)
{
}


Region::~Region()
{
}

void Region::SetPromotionLimit(int ts)
{
	PromotionLimit = ts;
}

int Region::GetPromotionLimits() const
{
	return PromotionLimit;
}

void Region::AddOrder(Order * pOrd) 
{
	switch (pOrd->GetType())
	{
	case TYPE_NRM: 
		NormalOrders.InsertEnd(pOrd);
		NumNormal++;
		break;
	case TYPE_FROZ: 
		FrozenOrders.enqueue(pOrd);
		NumFrozen++;
		break;
	case TYPE_VIP: 
		VipOrders.enqueue(pOrd);
		NumVIP++;
		break;
	}
}

bool Region::CancelOrder(int ID)
{
	for (auto i = NormalOrders.begin(); i != NormalOrders.end(); i++) {
		if ((*i)->GetID() == ID) {
			NormalOrders.Remove((*i));
			NumNormal--;
			return true;
		}
	}
	return false;
}

bool Region::PromoteOrder(int ID, double Extramny)
{
	for (auto i = NormalOrders.begin(); i != NormalOrders.end(); i++) {
		if ((*i)->GetID() == ID) {

			///Removing from normal orders list
			Order* pOrd = (*i);
			NormalOrders.Remove((pOrd));
			NumNormal--;

			///Adding to vip orders queue
			pOrd->IncrementMoney(Extramny);
			pOrd->SetType(TYPE_VIP);
			VipOrders.enqueue(pOrd);
			NumVIP++;
			return true;
		}
	}
	return false;
}

void Region::IncrementOrdersWT()
{
	Order* pOrd;

	///For VIP orders 
	Queue<Order*> temp; // used since the last element in the priority queue doesn't change by deque and enque the same object
	for (int i = 0; i < NumVIP; i++)
	{
		VipOrders.dequeue(pOrd);
		pOrd->IncrementWaitingTime();
		temp.enqueue(pOrd);
	}
	for (int i = 0; i < NumVIP; i++) {
		temp.dequeue(pOrd);
		VipOrders.enqueue(pOrd);
	}
		
	///For normal orders
	for (auto i = NormalOrders.begin(); i != NormalOrders.end(); i++)
	{
		(*i)->IncrementWaitingTime();
	}

	///For frozen orders
	for (int i = 0; i < NumFrozen; i++)
	{
		FrozenOrders.dequeue(pOrd);
		pOrd->IncrementWaitingTime();
		FrozenOrders.enqueue(pOrd);
	}
}

void Region::CheckInServiceMC(int ts)
{
	if (InServiceMC.isEmpty())
		return;

	Motorcycle* pMotor;
	while (InServiceMC.peekFront(pMotor) && pMotor->GetFinishTime() == ts )
	{
		InServiceMC.dequeue(pMotor);
		RestingMotors.enqueue(pMotor);
		pMotor->SetStatus(REST);
		NumRestingMotors++;

		Order* pOrd = nullptr;
		pMotor->ReleaseOrder(pOrd);
		FinishedOrders[pOrd->GetType()].Insert(pOrd);
		AvgServiceTime += pOrd->GetServTime();
		AvgWaitingTime += pOrd->GetWaitingTime();
	}
}

void Region::CheckRestMC(int ts)
{
	if (RestingMotors.isEmpty())
		return;

	Motorcycle* pMotor;
	RestingMotors.peekFront(pMotor);
	if (pMotor->GetFinishTime() + pMotor->GetRestingTime() == ts) {
		switch (pMotor->GetType()) {
		case NORMAL:
				RestingMotors.dequeue(pMotor);
				NormalMotors.enqueue(pMotor);
				NumNormalMotors++;

		case FAST:
				RestingMotors.dequeue(pMotor);
				FastMotors.enqueue(pMotor);
				NumFastMotors++;

		case FROZEN:
				RestingMotors.dequeue(pMotor);
				FrozenMotors.enqueue(pMotor);
				NumFrozenMotors++;
		}
		pMotor->SetStatus(IDLE);
		NumRestingMotors--;
	}
}

void Region::CreateMotorCycles(ifstream & InputFile)
{
	int Number, Speed, ID; // Number is the number of motorcycles of each type : Normal, Frozen & Fast

	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		ID = NumNormalMotors;
		NormalMotors.enqueue(new Motorcycle(Speed, NORMAL, ID));
		NumNormalMotors++;
	}

	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		ID = NumNormalMotors + NumFrozenMotors;
		FrozenMotors.enqueue(new Motorcycle(Speed, FROZEN, ID));
		NumFrozenMotors++;
	}

	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		ID = NumNormalMotors + NumFrozenMotors + NumFastMotors;
		FastMotors.enqueue(new Motorcycle(Speed, FAST, ID));
		NumFastMotors++;
	}
}

void Region::FillInfo(string * Order, string * Motorcycle)
{
	int totalOrders = NumNormal + NumFrozen + NumVIP;
	char TO[10]; // number of total orders
	char NO[10]; // number of normal orders 
	char FO[10]; // number of frozen orders
	char VO[10]; // number of VIP orders 

	itoa(totalOrders, TO, 10);
	itoa(NumNormal, NO, 10);
	itoa(NumFrozen, FO, 10);
	itoa(NumVIP, VO, 10);

	*Order += "Orders:" + (string)TO + "[Norm: " + (string)NO + ", Froz: " + (string)FO + " ,VIP: " + (string)VO + "]                ";

	int TotalMC = NumFastMotors + NumFrozenMotors + NumNormalMotors;
	char TotalMotorcycle[10];
	char FrozenMotorcycle[10];
	char NormalMotorcycle[10];
	char FastMotorcycle[10];

	itoa(NumFrozenMotors, FrozenMotorcycle, 10);
	itoa(NumNormalMotors, NormalMotorcycle, 10);
	itoa(NumFastMotors, FastMotorcycle, 10);
	itoa(TotalMC, TotalMotorcycle, 10);

	*Motorcycle += "Motorcycles: " + (string)TotalMotorcycle + "[Norm: " + (string)NormalMotorcycle + 
		", Froz: " + (string)FrozenMotorcycle + ", VIP:" + (string)FastMotorcycle + "]           ";
}

void Region::WriteInfo(ofstream & Output)
{
	PriorityQueue<Order*, FinishedOrdersComp> FinishedOrdersQueue; // priority queue that sort orders according to their finishing time
	int NumFinished = GetFinishedOrdersCount();

	// Adding all finished orders to priority queue 
	for (int i = 0; i < TYPE_CNT; i++) 
		for (auto j = FinishedOrders[i].begin(); j != FinishedOrders[i].end(); j++)
			FinishedOrdersQueue.enqueue((*j));


	// Printing finished orders
	Output << "FT\t" << "ID\t" << "AT\t" << "WT\t" << "ST\n";
	Order* pOrd;
	for (int i = 0; i < NumFinished; i++) {
		FinishedOrdersQueue.dequeue(pOrd);
		Output << pOrd->GetFinishTime() << '\t' << pOrd->GetID() << '\t'
			<< pOrd->GetArrTime() << '\t' << pOrd->GetWaitingTime() << '\t' << pOrd->GetServTime() << endl ;
	}
	Output << endl;

	// Prinitng Statistics
	Output << "Orders:" << NumFinished << "\t[Norm:  " << FinishedOrders[TYPE_NRM].GetCount() << ", Froz:  " << FinishedOrders[TYPE_FROZ].GetCount() 
		<< ", VIP:  " << FinishedOrders[TYPE_VIP].GetCount() << "]" << endl;

	int totalMotors = NumFastMotors + NumFrozenMotors + NumNormalMotors;
	Output << "MotorCycles:" << totalMotors << "\t[Norm:  " << NumNormalMotors << ", Froz:  " << NumFrozenMotors << ", Fast:  " << NumFastMotors << "]" << endl;

	if (NumFinished != 0)
		Output << "Avg Wait = " << GetAvgWT() << ",\tAvg Serv = " << GetAvgServT() << endl;

}

int Region::GetAvgWT() const
{
	return AvgWaitingTime / GetFinishedOrdersCount();
}

int Region::GetAvgServT() const
{
	return AvgServiceTime / GetFinishedOrdersCount();
}

int Region::GetFinishedOrdersCount() const
{
	int NumFinished = 0;
	for (int i = 0; i < TYPE_CNT; i++)
		NumFinished += FinishedOrders[i].GetCount();

	return NumFinished;
}

void Region::printOrders(GUI * pGUI)
{
	Order* pOrd;

	///For VIP orders 
	Queue<Order*> temp; // used since the last element in the priority queue doesn't change by deque and enque the same object
	for (int i = 0; i < NumVIP; i++)
	{
		VipOrders.dequeue(pOrd);
		pGUI->AddOrderForDrawing(pOrd);
		temp.enqueue(pOrd);
	}
	for (int i = 0; i < NumVIP; i++) {
		temp.dequeue(pOrd);
		VipOrders.enqueue(pOrd);
	}

	///For normal orders
	for (auto i = NormalOrders.begin(); i != NormalOrders.end(); i++)
	{
		pGUI->AddOrderForDrawing(*i);
	}

	///For frozen orders
	for (int i = 0; i < NumFrozen; i++)
	{
		FrozenOrders.dequeue(pOrd);
		pGUI->AddOrderForDrawing(pOrd);
		FrozenOrders.enqueue(pOrd);
	}
}

void Region::AutomaticPromotion()
{
	Order* pOrd;
	NormalOrders.PeekHead(pOrd);

	while (pOrd && (pOrd->GetWaitingTime() > PromotionLimit)) {
		PromoteOrder(pOrd->GetID());
		NormalOrders.PeekHead(pOrd);
	}
}

void Region::AssignMotorsToVip(int ts)
{
	if (NumVIP == 0 || (FastMotors.isEmpty() && NormalMotors.isEmpty() && FrozenMotors.isEmpty() ))
		return;

	int numOfOrders = NumVIP;
	for (int i = 0; i < numOfOrders; i++)
	{
		Order* pOrd = NULL;
		Motorcycle* pMotor = NULL;

		if (FastMotors.isEmpty() == false) //Use fast motors first
		{
			VipOrders.dequeue(pOrd);
			FastMotors.dequeue(pMotor);
			NumFastMotors--;
			NumVIP--;

			pOrd->SetWaitingTime(ts);
			pMotor->SetOrder(pOrd);
			InServiceMC.enqueue(pMotor);
			pMotor->SetStatus(SERV);
		}
		else if (NormalMotors.isEmpty() == false)
		{
			VipOrders.dequeue(pOrd);
			NormalMotors.dequeue(pMotor);
			NumNormalMotors--;
			NumVIP--;

			pOrd->SetWaitingTime(ts);
			pMotor->SetOrder(pOrd);
			InServiceMC.enqueue(pMotor);
			pMotor->SetStatus(SERV);
		}
		else if ( FrozenMotors.isEmpty() == false)
		{
			VipOrders.dequeue(pOrd);
			FrozenMotors.dequeue(pMotor);
			NumFrozenMotors--;
			NumVIP--;

			pOrd->SetWaitingTime(ts);
			pMotor->SetOrder(pOrd);
			InServiceMC.enqueue(pMotor);
			pMotor->SetStatus(SERV);
		}
	}
}

void Region::AssignMotorsToNormal(int ts)
{
	if (NumNormal == 0 || (NormalMotors.isEmpty() && FastMotors.isEmpty()))
		return;

	int numOfOrders = NumNormal;
	for (int i = 0; i < numOfOrders; i++)
	{
		Order* pOrd = NULL;
		Motorcycle* pMotor = NULL;

		if (NormalMotors.isEmpty() == false)
		{
			NormalOrders.PopHead(pOrd);
			NormalMotors.dequeue(pMotor);
			NumNormalMotors--;
			NumNormal--;

			pOrd->SetWaitingTime(ts);
			pMotor->SetOrder(pOrd);
			InServiceMC.enqueue(pMotor);
			pMotor->SetStatus(SERV);
		}

		else if (FastMotors.isEmpty() == false)
		{
			NormalOrders.PopHead(pOrd);
			FastMotors.dequeue(pMotor);
			NumFastMotors--;
			NumNormal--;

			pOrd->SetWaitingTime(ts);
			pMotor->SetOrder(pOrd);
			InServiceMC.enqueue(pMotor);
			pMotor->SetStatus(SERV);
		}
	}
}

void Region::AssignMotorsToFrozen(int ts)
{
	if (NumFrozen == 0 || FrozenMotors.isEmpty())
		return;

	Order* pOrd = NULL;
	Motorcycle*pMotor = NULL;
	int numOfOrders = NumFrozen;
	for (int i = 0; i < numOfOrders; i++)
	{
		FrozenOrders.dequeue(pOrd);
		FrozenMotors.dequeue(pMotor);
		NumFrozenMotors--;
		NumFrozen--;

		pOrd->SetWaitingTime(ts);
		pMotor->SetOrder(pOrd);
		InServiceMC.enqueue(pMotor);
		pMotor->SetStatus(SERV);
	}

}

void Region::AssignMotorCycles(int ts)
{
	AssignMotorsToVip(ts);
	AssignMotorsToFrozen(ts);
	AssignMotorsToNormal(ts);
}
