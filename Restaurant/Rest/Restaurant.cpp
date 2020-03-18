#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "Restaurant.h"
//#include "..\Events\ArrivalEvent.h"



Restaurant::Restaurant() 
{
	EventCount = 0;
	pGUI = NULL;
}


void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InterActive();
	case MODE_STEP:
		Step_By_Step();
	case MODE_SLNT:
		Silent();
	case MODE_DEMO:
		break;

	};


}

void Restaurant::ReadFile()
{
	pGUI->PrintMessage("Enter File Name:");
	string filename = pGUI->GetString()+".txt";
	ifstream InputFile(filename);

	while (!InputFile.is_open()){
		pGUI->PrintMessage("No such a file, enter new file name:");
		filename = pGUI->GetString() + ".txt";
		InputFile.open(filename.c_str());
	}

	int Number, Speed;
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		A.CreateMotorcycle(Speed, NORMAL);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		A.CreateMotorcycle(Speed, FROZEN);
	}

	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		A.CreateMotorcycle(Speed, FAST);
	}

	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		B.CreateMotorcycle(Speed, NORMAL);
	}

	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		B.CreateMotorcycle(Speed, FROZEN);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		B.CreateMotorcycle(Speed, FAST);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		C.CreateMotorcycle(Speed, NORMAL);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		C.CreateMotorcycle(Speed, FROZEN);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		C.CreateMotorcycle(Speed, FAST);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		D.CreateMotorcycle(Speed, NORMAL);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		D.CreateMotorcycle(Speed, FROZEN);
	}
	InputFile >> Number;
	for (int i = 0; i < Number; i++)
	{
		InputFile >> Speed;
		D.CreateMotorcycle(Speed, FAST);
	}

	int AutoS;
	InputFile >> AutoS;
	A.SetPromotionLimit(AutoS);
	B.SetPromotionLimit(AutoS);
	C.SetPromotionLimit(AutoS);
	D.SetPromotionLimit(AutoS);

	int NumOfEvents;
	InputFile >> NumOfEvents;
	EventCount = NumOfEvents;
	int Ts, ID, Distance;
	char EventType, type, Region;
	double Money;
	ORD_TYPE ordtype;
	REGION reg;

	for (int i = 0; i < NumOfEvents; i++)
	{
		InputFile >> EventType;
		switch (EventType )
		{
		case 'R'  :
			InputFile >> Ts >> type >> ID >> Distance >> Money >> Region;
			switch (type) {
			case 'N': ordtype = TYPE_NRM; break;
			case 'F' : ordtype = TYPE_FROZ; break;
			case 'V' : ordtype = TYPE_VIP; break;
			}

			switch (Region) {
			case 'A': reg = A_REG; break;
			case 'B': reg = B_REG; break;
			case 'C': reg = C_REG; break;
			case 'D': reg = D_REG; break;
			}

			EventsQueue.enqueue(new ArrivalEvent(Ts, ID, ordtype, reg, Distance, Money));
			break;
		case 'X':
			InputFile >> Ts >> ID;
			EventsQueue.enqueue(new CancelEvent(Ts, ID));
			break;
		case 'P':
			InputFile >> Ts >> ID >> Money;
			EventsQueue.enqueue(new PromotionEvent(Ts,ID,Money));
			break;
		}
	}

}

void Restaurant::WriteFile()
{
	//Making File for saving
	pGUI->PrintMessage("Enter Output File Name:");
	string filename = pGUI->GetString() + ".txt";
	ofstream OutputFile(filename, ios::out);

	while (!OutputFile.is_open()) {
		pGUI->PrintMessage("Failed  to save the file !");
	}

	//Getting finished orders from regions 
	FOPQ FinishedOrders;
	A.GetFinishedOrders(FinishedOrders);
	B.GetFinishedOrders(FinishedOrders);
	C.GetFinishedOrders(FinishedOrders);
	D.GetFinishedOrders(FinishedOrders);

	//Printing finished orders
	OutputFile << "FT\t" << "ID\t" << "AT\t" << "WT\t" << "ST\n";
	Order* pOrd;
	while (!(FinishedOrders.isEmpty()))
	{
		FinishedOrders.dequeue(pOrd);
		OutputFile << pOrd->GetFinishTime() << '\t' << pOrd->GetID() << '\t'
			<< pOrd->GetArrivalTime() << '\t' << pOrd->GetWaitingTime() << '\t' << pOrd->GetServiceTime() << endl;
	}

	//Printing statistics for each region
	OutputFile << ".................................." << endl << ".................................." << endl;
	OutputFile << "Region A:" << endl;
	A.WriteFile(OutputFile);

	OutputFile << ".................................." << endl << ".................................." << endl;
	OutputFile << "Region B:" << endl;
	B.WriteFile(OutputFile);

	OutputFile << ".................................." << endl << ".................................." << endl;
	OutputFile << "Region C:" << endl;
	C.WriteFile(OutputFile);

	OutputFile << ".................................." << endl << ".................................." << endl;
	OutputFile << "Region D:" << endl;
	D.WriteFile(OutputFile);
}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}




//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue

	
		delete pE;		//deallocate event object from memory
	}

}

void Restaurant::CancelOrder(int id1)
{
		//pGUI->Remove(id1);
		switch (getRegionByID(id1)) {
		case A_REG: A.CancelOrderRegion(id1); break;
		case B_REG: B.CancelOrderRegion(id1); break;
		case C_REG: C.CancelOrderRegion(id1); break;
		case D_REG: D.CancelOrderRegion(id1); break;
		}
}

void Restaurant::PromoteOrder(int id1, int mny)
{
	Order* pOrd;
	switch (getRegionByID(id1)) {
	case A_REG: pOrd = A.Promote(id1, mny); break;
	case B_REG: pOrd = B.Promote(id1, mny); break;
	case C_REG: pOrd = C.Promote(id1, mny); break;
	case D_REG: pOrd = D.Promote(id1, mny); break;
	}
}

void Restaurant::AddOrder(Order * pOrd)
{
	switch (pOrd->GetRegion())
	{
	case A_REG: A.HandleOrder(pOrd); break;
	case B_REG: B.HandleOrder(pOrd); break;
	case C_REG: C.HandleOrder(pOrd); break;
	case D_REG: D.HandleOrder(pOrd); break;
	}
}


Restaurant::~Restaurant()
{
		delete pGUI;
}

void Restaurant :: InterActive()
{
	ReadFile();
	int EventCnt;
	EventCnt = EventCount;

	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	int NormalsDoneA = 0;
	int NormalsDoneB = 0;
	int NormalsDoneC = 0;
	int NormalsDoneD = 0;
	
	pGUI->PrintMessage("InterActive Simulation!!");
	string TimeStep;
	string Regions;
	string Orders;
	string MotorCycles;
	string Time;
	string OrdersDone;
	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{

		//increment waiting time for waiting orders
		A.IncrementOrdersWT();
		B.IncrementOrdersWT();
		C.IncrementOrdersWT();
		D.IncrementOrdersWT();

		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		pGUI->ResetDrawingList();
		A.printOrders(pGUI);
		B.printOrders(pGUI);
		C.printOrders(pGUI);
		D.printOrders(pGUI);
		pGUI->UpdateInterface();

		A.AssignMotorCycles(CurrentTimeStep);
		B.AssignMotorCycles(CurrentTimeStep);
		C.AssignMotorCycles(CurrentTimeStep);
		D.AssignMotorCycles(CurrentTimeStep);

		A.TazbeetMakan(CurrentTimeStep);
		B.TazbeetMakan(CurrentTimeStep);
		C.TazbeetMakan(CurrentTimeStep);
		D.TazbeetMakan(CurrentTimeStep);

		A.DistibuteMotors(CurrentTimeStep);
		B.DistibuteMotors(CurrentTimeStep);
		C.DistibuteMotors(CurrentTimeStep);
		D.DistibuteMotors(CurrentTimeStep);

		A.AutomaticPromotion();
		B.AutomaticPromotion();
		C.AutomaticPromotion();
		D.AutomaticPromotion();

		A.OrdersDone(NormalsDoneA);
		B.OrdersDone(NormalsDoneB);
		C.OrdersDone(NormalsDoneC);
		D.OrdersDone(NormalsDoneD);

		char TotalNormal1[10];
		char TotalVIP1[10];
		char TotalFrozen1[10];
		char TotalOrdersD[10];
		itoa(NormalsDoneA, TotalNormal1, 10);
		itoa(NormalsDoneB, TotalVIP1, 10);
		itoa(NormalsDoneC, TotalFrozen1, 10);
		itoa(NormalsDoneD, TotalOrdersD, 10);

		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		char NumberOfActiveOrders[10];
		itoa(pGUI->GetOrderCount(), NumberOfActiveOrders, 10);
		
		TimeStep = (string)timestep;
		Regions = "Region A:                                                       Region B:                                                       Region C:                                                       Region D:                                                       ";
		Orders = "      ";
		MotorCycles = "      ";
		OrdersDone = "      OrdersDone A="+(string)TotalNormal1+"                                       OrdersDone B="+(string)TotalFrozen1+"                                       OrdersDone C="+(string)TotalVIP1+"                                       OrdersDone D="+(string)TotalOrdersD;

		A.GetInfo(&Orders, &MotorCycles, &Time);
		B.GetInfo(&Orders, &MotorCycles, &Time);
		C.GetInfo(&Orders, &MotorCycles, &Time);
		D.GetInfo(&Orders, &MotorCycles, &Time);
		pGUI->PrintMessage(TimeStep, Regions, Orders, MotorCycles,OrdersDone);
		pGUI->UpdateInterface();

		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep

	}

	WriteFile();
	pGUI->PrintMessage("generation done, click to END program ");
	pGUI->waitForClick();
}

void Restaurant::Step_By_Step()
{
	ReadFile();
	int EventCnt;
	EventCnt = EventCount;

	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Step By Step Simulation!!");
	string TimeStep;
	string Regions;
	string Orders;
	string MotorCycles;
	string Time;
	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//increment waiting time for waiting orders
		A.IncrementOrdersWT();
		B.IncrementOrdersWT();
		C.IncrementOrdersWT();
		D.IncrementOrdersWT();

		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

		//Drawing orders
		pGUI->ResetDrawingList();
		A.printOrders(pGUI);
		B.printOrders(pGUI);
		C.printOrders(pGUI);
		D.printOrders(pGUI);
		pGUI->UpdateInterface();
		
		A.AssignMotorCycles(CurrentTimeStep);
		B.AssignMotorCycles(CurrentTimeStep);
		C.AssignMotorCycles(CurrentTimeStep);
		D.AssignMotorCycles(CurrentTimeStep);
		
		A.TazbeetMakan(CurrentTimeStep);
		B.TazbeetMakan(CurrentTimeStep);
		C.TazbeetMakan(CurrentTimeStep);
		D.TazbeetMakan(CurrentTimeStep);

		A.DistibuteMotors(CurrentTimeStep);
		B.DistibuteMotors(CurrentTimeStep);
		C.DistibuteMotors(CurrentTimeStep);
		D.DistibuteMotors(CurrentTimeStep);

		A.AutomaticPromotion();
		B.AutomaticPromotion();
		C.AutomaticPromotion();
		D.AutomaticPromotion();


		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		char NumberOfActiveOrders[10];
		itoa(pGUI->GetOrderCount(), NumberOfActiveOrders, 10);

		TimeStep = (string)timestep;
		Regions = "Region A:                                                       Region B:                                                       Region C:                                                       Region D:                                                       " ;
		Orders = "      ";
		MotorCycles = "      ";


		A.GetInfo(&Orders, &MotorCycles, &Time);
		B.GetInfo(&Orders, &MotorCycles, &Time);
		C.GetInfo(&Orders, &MotorCycles, &Time);
		D.GetInfo(&Orders, &MotorCycles, &Time);
		pGUI->PrintMessage(TimeStep,Regions,Orders,MotorCycles);
		pGUI->UpdateInterface();

		Sleep(1000);
		CurrentTimeStep++;	//advance timestep

	}

	WriteFile();
	//pGUI->PrintMessage(TimeStep, Regions, Orders, MotorCycles, Time);
	pGUI->PrintMessage("generation done, click to END program ");
	pGUI->waitForClick();
	

}
 void Restaurant :: Silent()
 {
	ReadFile();
	int EventCnt;
	EventCnt = EventCount;

	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	string TimeStep;
	string Regions;
	string Orders;
	string MotorCycles;
	string Time;
	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{

		//increment waiting time for waiting orders
		A.IncrementOrdersWT();
		B.IncrementOrdersWT();
		C.IncrementOrdersWT();
		D.IncrementOrdersWT();

		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		
		A.AssignMotorCycles(CurrentTimeStep);
		B.AssignMotorCycles(CurrentTimeStep);
		C.AssignMotorCycles(CurrentTimeStep);
		D.AssignMotorCycles(CurrentTimeStep);
		
		A.TazbeetMakan(CurrentTimeStep);
		B.TazbeetMakan(CurrentTimeStep);
		C.TazbeetMakan(CurrentTimeStep);
		D.TazbeetMakan(CurrentTimeStep);

		A.DistibuteMotors(CurrentTimeStep);
		B.DistibuteMotors(CurrentTimeStep);
		C.DistibuteMotors(CurrentTimeStep);
		D.DistibuteMotors(CurrentTimeStep);


		A.AutomaticPromotion();
		B.AutomaticPromotion();
		C.AutomaticPromotion();
		D.AutomaticPromotion();
		//print current timestep
		CurrentTimeStep++;	//advance timestep
	}

	WriteFile();
	//pGUI->PrintMessage(TimeStep, Regions, Orders, MotorCycles, Time);

 }

REGION Restaurant::getRegionByID(int id)
{
	if ((id>=11 && id<=19) || (id>=100 && id<=199 ) || (id>=1000 && id<=1999))
	{
		return A_REG;
	}
	else if ((id >= 21 && id <= 29) || (id >= 200 && id <= 299) || (id >= 2000 && id <= 2999))
	{
		return B_REG;
	}
	else if ((id >= 31 && id <= 39) || (id >= 300 && id <= 399) || (id >= 3000 && id <= 3999))
	{
		return C_REG;
	}
	else
	{
		return D_REG;
	}
}
