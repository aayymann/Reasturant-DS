#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"

#include "..\Events\Event.h"
#include "..\CancelEvent.h"
#include "..\PromotionEvent.h"
#include "..\Region.h"
#include "..\Rest\Order.h"


// the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Region Regions[REG_CNT]; //Array of Regions. 1 for REG_A, 2for REG_B .. etc
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	int EventsCount;

	REGION GetRegionByID(int ID) const; //Gets the region of the passed ID

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep

	void AddOrder(Order* pOrd); //Adds new order to it's Region
	bool CancelOrder(int oID); //Calls cancel request for region of passed order id
	bool PromoteOrder(int oID, double Extramny); //Calls promotion request fot region of passed order id

	//Input and Output Files
	void ReadFile();
	void WriteFile();

	//Simulations
	void RunSimulation();
	void printInfo(int ts); //print current timestep information
	void Step_By_Step();
	void InterActive();
	void Silent();
};

#endif