#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\PromotionEvent.h"
#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"../CancelEvent.h"
#include"..\Events\ArrivalEvent.h"
#include "Order.h"
#include "..\Region.h"
#include"../FOPQ.h"

// it is the maestro of the project
class Restaurant  
{	
protected:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	int EventCount;

	//Branches
	Region A;		
	Region B;
	Region C;
	Region D;
	
public:
	
	Restaurant();
	~Restaurant();

	//adds a new event to the queue of events
	void AddEvent(Event* pE);	

	//executes all events at current timestep
	void ExecuteEvents(int TimeStep);	
	void CancelOrder(int id1);		

	//call promotion function in it's region
	void PromoteOrder(int id1, int mny);

	//Add order to it's region
	void AddOrder(Order* pOrd);

	void RunSimulation();

	//RInput and Output Files
	void ReadFile();
	void WriteFile();

	void Step_By_Step();
	void InterActive();
	void Silent();

	// return region by iD as first number on the Id column represents the region the event is in if 1 , region A , ect..
	REGION getRegionByID(int id);


};

#endif