#pragma once
#include "Region.h"
#include<fstream>
//int Region::RestT = 2;   // zeyadaaa
Region::Region()
{
	FrozenMotorcycle = 0;
	FastMotorCycle = 0;
	NormalMotorCycle = 0;
	NormalOrder = 0;
	FrozenOrder = 0;
	VIPOrder = 0;
	AverageServiceTime = 0;
	AverageWaitingTime = 0;
	NumofRestMotors = 0;
	
	
}

void Region::HandleOrder(Order * pOrd)
{
	switch (pOrd->GetType())
	{
	case TYPE_NRM: NormalOrders.InsertEnd(pOrd);
		NormalOrder++;
		break;
	case TYPE_FROZ: FrozenOrders.enqueue(pOrd); 
		FrozenOrder++;
		break;
	case TYPE_VIP: VIPQueue.enqueue(pOrd); 
		VIPOrder++;
		break;
	}
}

void Region::CreateMotorcycle(int Speed, MC_TYPE type, int NumberofMC)
{
	switch (type) {
	case FROZEN:
		for (int i = 0; i < NumberofMC; i++)
		{
			FrozenMotorCycles.enqueue(new Motorcycle(Speed,type , FrozenMotorcycle));
			FrozenMotorcycle++;
		}
		break;
	case NORMAL:
		for (int i = 0; i < NumberofMC; i++)
		{
			NormalMotorCycles.enqueue(new Motorcycle(Speed,type, NormalMotorCycle + FrozenMotorcycle));
			NormalMotorCycle++;
		}
		break;
	case FAST:
		for (int i = 0; i < NumberofMC; i++)
		{
			FastMotorCycles.enqueue(new Motorcycle(Speed,type , FastMotorCycle + NormalMotorCycle + FrozenMotorcycle));
			FastMotorCycle++;
		}
		break;
	}
}

void Region::OrdersDone(int & Normal)
{
	Normal = FinishedOrders.GetCount();
}



void Region::AssignVIPToMotorCycles(int ts)
{
	while (VIPOrder != 0 && (FastMotorCycles.isEmpty()==false || NormalMotorCycles.isEmpty()==false || FrozenMotorCycles.isEmpty()==false))
	{

		for (int i = 0; i < VIPOrder; i++)
		{
			Order* pOrd = NULL;
			Motorcycle* A = NULL;
			if (FastMotorCycles.isEmpty() == false)
			{
				VIPQueue.dequeue(pOrd);
				FastMotorCycles.dequeue(A);
				FastMotorCycle--;
				A->SetOrdAndMotor(pOrd);
				VIPOrder--;
				pOrd->SetWaitingTime(ts);
				A->SetRestingTime();
				A->SetOrderServiceTime();
				InServiceMC.enqueue(A);
			}
			else if (NormalMotorCycles.isEmpty() == false)
			{
				VIPQueue.dequeue(pOrd);
				NormalMotorCycles.dequeue(A);
				NormalMotorCycle--;
				A->SetOrdAndMotor(pOrd);
				VIPOrder--;
				pOrd->SetWaitingTime(ts);
				A->SetRestingTime();
				A->SetOrderServiceTime();
				InServiceMC.enqueue(A);
			}
			else if (FrozenMotorCycles.isEmpty() == false)
			{
				VIPQueue.dequeue(pOrd);
				FrozenMotorCycles.dequeue(A);
				FrozenMotorcycle--;
				A->SetOrdAndMotor(pOrd);
				VIPOrder--;
				pOrd->SetWaitingTime(ts);
				A->SetOrderServiceTime();
				A->SetRestingTime();
				InServiceMC.enqueue(A);
			}
		}
	}
	
	
}

void Region::AssignNormalToMotorCycles(int ts)
{
	while (NormalOrder != 0 && (NormalMotorCycles.isEmpty() == false || FastMotorCycles.isEmpty() == false))
	{
		for (int i = 0; i < NormalOrder; i++)
		{
			Order* pOrd = NULL;
			Motorcycle* A = NULL;
			if (NormalMotorCycles.isEmpty() == false)
			{

				NormalOrders.PeekHead(pOrd);
				NormalMotorCycles.dequeue(A);
				NormalMotorCycle--;
				A->SetOrdAndMotor(pOrd);
				NormalOrder--;
				pOrd->SetWaitingTime(ts);
				A->SetRestingTime();
				A->SetOrderServiceTime();
				InServiceMC.enqueue(A);
			}


			else if (FastMotorCycles.isEmpty() == false)
			{
				pOrd = NormalOrders.GetItem(pOrd->GetID());
				NormalOrders.Remove(pOrd);
				NormalMotorCycles.dequeue(A);
				NormalMotorCycle--;
				A->SetOrdAndMotor(pOrd);
				NormalOrder--;
				pOrd->SetWaitingTime(ts);
				A->SetRestingTime();
				A->SetOrderServiceTime();
				InServiceMC.enqueue(A);
			}
		}
	}
}
			
			
void Region::AssignMotorFrzoenToCycles(int ts)
{
	while (FrozenOrder != 0 && FrozenMotorCycles.isEmpty() == false)
	{
		Order* pOrd = NULL;
		Motorcycle* A = NULL;
		for (int i = 0; i < FrozenOrder; i++)
		{
			FrozenOrders.dequeue(pOrd);
			FrozenMotorCycles.dequeue(A);
			FrozenMotorcycle--;
			A->SetOrdAndMotor(pOrd);
			FrozenOrder--;
			pOrd->SetWaitingTime(ts);
			A->SetOrderServiceTime();
			InServiceMC.enqueue(A);
			A->SetRestingTime();
		}
	}
}

void Region::AssignMotorCycles(int ts)
{

	AssignVIPToMotorCycles(ts);
	AssignMotorFrzoenToCycles(ts);
	AssignNormalToMotorCycles(ts);
	
}

bool Region::CancelOrderRegion(int id)
{
	Order* pOrd = NormalOrders.GetItem(id);
	if (pOrd){
		if (NormalOrders.Remove(pOrd)) {
			NormalOrder--;
			return true;
		}
	}
	else return false;
}

void Region::SetPromotionLimit(int pl)
{
	PromotionLimit = pl;
}

int Region::GetPromotionLimit()
{
	return PromotionLimit;
}

Order* Region::Promote(int id, int extraM)
{
	Order * pOrd;
	pOrd=NormalOrders.GetItem(id);
	if (NormalOrders.Remove(pOrd))
	{
		pOrd->SetMoney(pOrd->GetMoney() + extraM);
		pOrd->setType(TYPE_VIP); // ADDED
		VIPQueue.enqueue(pOrd);
		VIPOrder++;
		NormalOrder--;
		return pOrd;
	}
}

void Region::TazbeetMakan(int ts)
{
	if (InServiceMC.isEmpty()) {
		return;
	}
	Motorcycle*A;
	InServiceMC.peekFront(A);
	int x = A->GetFinishTime();
	while (A->GetFinishTime() == ts && InServiceMC.peekFront(A))
	{
		InServiceMC.dequeue(A);
		RestingMotors.enqueue(A);
		NumofRestMotors++;
		FinishedOrders.Add(A->GetOrder());
		AverageServiceTime += A->GetOrder()->GetServiceTime();
		AverageWaitingTime += A->GetOrder()->GetWaitingTime();

	}
}


void Region::DistibuteMotors(int ts)
{
	if (RestingMotors.isEmpty() == true)
	{
		return;
	}
	Motorcycle* A;
	RestingMotors.peekFront(A);
	if (A->GetFinishTime() + A->GetRestingTime() == ts) {
		if (A->GetMCType() == NORMAL) {

			RestingMotors.dequeue(A);
			NormalMotorCycles.enqueue(A);
			NormalMotorCycle++;
			NumofRestMotors--;

		}
		else if (A->GetMCType() == FAST) {
			RestingMotors.dequeue(A);
			FastMotorCycles.enqueue(A);
			FastMotorCycle++;
			NumofRestMotors--;


		}
		else if (A->GetMCType() == FROZEN) {
			RestingMotors.dequeue(A);
			FrozenMotorCycles.enqueue(A);
			FrozenMotorcycle++;
			NumofRestMotors--;

		}
	}
	else
		return;
}

void Region::AutomaticPromotion()
{
	Order* pOrd;
	pOrd = NormalOrders.PeekHead2();

	while (pOrd && (pOrd->GetWaitingTime() > PromotionLimit)) {
			Promote(pOrd->GetID());
			pOrd = NormalOrders.PeekHead2();
	}
}


void Region::GetInfo(string* Order,string* Motorcycle,string*Time)
{
	int nc = NormalOrder;
	int fc = FrozenOrder;
	int vc = VIPOrder;
	int tc = nc + fc + vc;
	char tc1[10];
	char nc1[10];
	char vc1[10];
	char fc1[10];
	itoa(tc, tc1, 10);
	itoa(nc, nc1, 10);
	itoa(vc, vc1, 10);
	itoa(fc, fc1, 10);
	*Order += "Orders:" + (string)tc1 + "[Norm:" + (string)nc1 + ", Froz:" + (string)fc1 + " ,VIP:" + (string)vc1 + "]                ";

	char FrozenMotorcycle1[10];
	char NormalMotorcycle1[10];
	char FastMotorcycle1[10];
	int TotalMC = FrozenMotorcycle + FastMotorCycle + NormalMotorCycle;
	char TotalMC1[10];
	itoa(FrozenMotorcycle, FrozenMotorcycle1, 10);
	itoa(NormalMotorCycle, NormalMotorcycle1, 10);
	itoa(FastMotorCycle, FastMotorcycle1, 10);
	itoa(TotalMC, TotalMC1, 10);
	
	*Motorcycle += "MotorC:" + (string)TotalMC1 + "[Norm:" + (string)NormalMotorcycle1 + ", Froz:" + (string)FrozenMotorcycle1 + ", VIP:" + (string)FastMotorcycle1 + "]           ";
	//char AverageWaitingTime1[10];
	//char AverageServiceTime1[10];
	//itoa(GetAverageWaitingTime(), AverageWaitingTime1, 10);
	//itoa(GetAverageServiceTime(), AverageServiceTime1, 10);
	//*Time += "AvG SV Time:" + (string)AverageServiceTime1 + "  AvG WT Time:" + (string)AverageWaitingTime1+"  ";
}

void Region::IncrementOrdersWT()
{
	Order* pOrd;
	for (int i = 0; i < VIPOrder; i++)
	{
		VIPQueue.dequeue(pOrd);
		pOrd->IncrementWT();
		VIPQueue.NormalEnqueue(pOrd);
	}

	for (int i = 1; i <= NormalOrder; i++)
	{
		pOrd = NormalOrders.GetItemByPosition(i);
		pOrd->IncrementWT();
	}

	for (int i = 0; i < FrozenOrder; i++)
	{
		FrozenOrders.dequeue(pOrd);
		pOrd->IncrementWT();
		FrozenOrders.enqueue(pOrd);
	}
}

int Region::GetAverageWaitingTime()
{
	return AverageWaitingTime / FinishedOrders.GetCount();
}

void Region::printOrders(GUI * pGUI)
{
	Order* pOrd;
	for (int i=0;i<VIPOrder;i++)
	{
		VIPQueue.dequeue(pOrd);
		pGUI->AddOrderForDrawing(pOrd);
		//pGUI->UpdateInterface();
		VIPQueue.NormalEnqueue(pOrd);
	}


	for (int i = 1; i <= NormalOrder; i++)
	{
		pOrd = NormalOrders.GetItemByPosition(i);
		pGUI->AddOrderForDrawing(pOrd);
		//pGUI->UpdateInterface();
	}

	for (int i = 0; i < FrozenOrder; i++)
	{
		FrozenOrders.dequeue(pOrd);
		pGUI->AddOrderForDrawing(pOrd);
		//pGUI->UpdateInterface();
		FrozenOrders.enqueue(pOrd);
	}
}


int Region::GetAverageServiceTime()
{
	return AverageServiceTime / FinishedOrders.GetCount();
}

int Region::GetNumberOFFinishedOrders()
{
	return FinishedOrders.GetCount();
}

void Region::WriteFile(ofstream& OutFile)
{
	int Normal = 0;
	int Frozen = 0;
	int VIP = 0;
	for (int i = 1; i <= FinishedOrders.GetCount(); i++) {
		switch (FinishedOrders.GetItemByPosition(i)->GetType()) {
		case TYPE_NRM:Normal++;
		case TYPE_VIP:VIP++;
		case TYPE_FROZ:Frozen++;
		}
	}
	
	OutFile<< "\tOrders:" << FinishedOrders.GetCount() << "\t[Norm:  " << Normal << ", Froz:  " << Frozen << ", VIP:  " << VIP << "]" << endl;
	OutFile<<"\tMotorC:"<<FrozenMotorcycle+FastMotorCycle+NormalMotorCycle<<"\t[Norm:  " << NormalMotorCycle << ", Froz:  " << FrozenMotorcycle << ", VIP:  " << FastMotorCycle << "]" << endl;
	if(FinishedOrders.GetCount()!=0)
		OutFile << "\tAvg Wait = " << GetAverageWaitingTime() << ",\tAvg Serv = " << GetAverageServiceTime() << endl;
}

void Region::GetFinishedOrders(FOPQ & finishedOrders)
{
	Order* pOrd;
	for (int i = 1; i <= FinishedOrders.GetCount(); i++) {
		pOrd = FinishedOrders.GetItemByPosition(i);
		finishedOrders.enqueue(pOrd);
	}
}
 


Region::~Region()
{
}
