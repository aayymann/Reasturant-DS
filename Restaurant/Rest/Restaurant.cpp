#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


REGION Restaurant::GetRegionByID(int ID) const
{
	// 1 is for REG_A, 2 for REG_B ... etc

	while (ID > 9) ID /= 10;
	return (REGION)ID;
}

Restaurant::Restaurant()
{
	pGUI = NULL;
	EventsCount = 0;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)
	{
	case MODE_INTR:
		InterActive();
		break;
	case MODE_STEP:
		Step_By_Step();
		break;
	case MODE_SLNT:
		Silent();
		break;
	};
}

void Restaurant::printInfo(int ts)
{
	string TimeStep, RegionStr, OrderStr, MotorCycleStr, Time;
	
	char timestep[10];
	itoa(ts, timestep, 10);

	char NumberOfActiveOrders[10];
	itoa(pGUI->GetOrderCount(), NumberOfActiveOrders, 10);

	TimeStep = (string)timestep;
	RegionStr = "Region A:                                                       Region B:                                                       Region C:                                                       Region D:                                                       ";
	
	OrderStr = "      ";
	MotorCycleStr = "      ";
	for (int i = 0; i < REG_CNT; i++) {
		Regions[i].FillInfo(&OrderStr, &MotorCycleStr);
	}

	pGUI->PrintMessage(TimeStep, RegionStr, OrderStr, MotorCycleStr);
	pGUI->UpdateInterface();
}

void Restaurant::Step_By_Step()
{
	pGUI->PrintMessage("Step By Step Simulation!!");
	ReadFile();

	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

		pGUI->ResetDrawingList();
		for (int i = 0; i < REG_CNT; i++) { //Drawing orders
			Regions[i].printOrders(pGUI);
		}
		pGUI->UpdateInterface();

		for (int i = 0; i < REG_CNT; i++) {
			Regions[i].AssignMotorCycles(CurrentTimeStep);
			Regions[i].CheckInServiceMC(CurrentTimeStep);
			Regions[i].CheckRestMC(CurrentTimeStep);
			Regions[i].AutomaticPromotion();
			Regions[i].IncrementOrdersWT();
		}

		printInfo(CurrentTimeStep);
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}

	WriteFile();
	pGUI->PrintMessage("generation done, click to END program ");
	pGUI->waitForClick();
}

void Restaurant::InterActive()
{
	pGUI->PrintMessage("Interactive Simulation!!");
	ReadFile();

	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

		pGUI->ResetDrawingList();
		for (int i = 0; i < REG_CNT; i++) { //Drawing orders
			Regions[i].printOrders(pGUI);
		}
		pGUI->UpdateInterface();

		for (int i = 0; i < REG_CNT; i++) {
			Regions[i].CheckInServiceMC(CurrentTimeStep);
			Regions[i].CheckRestMC(CurrentTimeStep);
			Regions[i].AutomaticPromotion();
			Regions[i].IncrementOrdersWT();
			Regions[i].AssignMotorCycles(CurrentTimeStep);
		}

		printInfo(CurrentTimeStep);
		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
	}

	WriteFile();
	pGUI->PrintMessage("generation done, click to END program ");
	pGUI->waitForClick();
}

void Restaurant::Silent()
{
	ReadFile();
	srand(time(NULL));
	int CurrentTimeStep = 1;

	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step

		for (int i = 0; i < REG_CNT; i++) {
			Regions[i].AssignMotorCycles(CurrentTimeStep);
			Regions[i].CheckInServiceMC(CurrentTimeStep);
			Regions[i].CheckRestMC(CurrentTimeStep);
			Regions[i].AutomaticPromotion();
			Regions[i].IncrementOrdersWT();
		}

		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}
	WriteFile();
}

void Restaurant::AddEvent(Event* pE)
{
	EventsQueue.enqueue(pE);
}

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

Restaurant::~Restaurant()
{
		delete pGUI;
}

void Restaurant::AddOrder(Order * pOrd)
{
	Regions[pOrd->GetRegion()].AddOrder(pOrd);
}

bool Restaurant::CancelOrder(int oID)
{
	return Regions[GetRegionByID(oID)].CancelOrder(oID); 
}

bool Restaurant::PromoteOrder(int oID, double Extramny)
{
	return Regions[GetRegionByID(oID)].PromoteOrder(oID, Extramny);
}

void Restaurant::ReadFile()
{
	// Opening file
	pGUI->PrintMessage("Enter File Name:");
	string filename = pGUI->GetString() + ".txt";
	ifstream InputFile(filename);

	while (!InputFile.is_open()) {
		pGUI->PrintMessage("No such a file, enter new file name:");
		filename = pGUI->GetString() + ".txt";
		InputFile.open(filename.c_str());
	}

	// Creating motorcycles for each region
	for (int i = 0; i < REG_CNT; i++) {
		Regions[i].CreateMotorCycles(InputFile);
	}

	// Setting promotion limit for each region
	int AutoS;
	InputFile >> AutoS;
	for (int i = 0; i < REG_CNT; i++) {
		Regions[i].SetPromotionLimit(AutoS);
	}

	// Creating and storing events
	InputFile >> EventsCount;
	int Ts, ID, Distance;
	char EventType, type, Region;
	double Money;
	ORD_TYPE ordtype;
	REGION reg;

	for (int i = 0; i < EventsCount; i++)
	{
		InputFile >> EventType;
		switch (EventType)
		{
		case 'R':
			InputFile >> Ts >> type >> ID >> Distance >> Money >> Region;
			switch (type) {
			case 'N': ordtype = TYPE_NRM; break;
			case 'F': ordtype = TYPE_FROZ; break;
			case 'V': ordtype = TYPE_VIP; break;
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
			EventsQueue.enqueue(new PromotionEvent(Ts, ID, Money));
			break;
		}
	}
}

void Restaurant::WriteFile()
{
	// Creating File 
	pGUI->PrintMessage("Enter Output File Name:");
	string filename = pGUI->GetString() + ".txt";
	ofstream OutputFile(filename, ios::out);

	while (!OutputFile.is_open()) {
		pGUI->PrintMessage("Failed  to save the file !");
	}

	// Writing information of each region
	for (int i = 0; i < REG_CNT; i++) {
		OutputFile << "Region " << letters[i] << ':' << endl;
		Regions[i].WriteInfo(OutputFile);
		OutputFile << ".................................." << endl << ".................................." << endl << endl << endl;
	}

}
