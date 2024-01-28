#ifndef __EVENT_H_
#define __EVENT_H_

#include "..\Defs.h"

class Restaurant;	//Forward declation

class Event
{
protected:
	int EventTime;	//Timestep when this event takes place
	int OrderID;	//each event is related to certain order
public:
	Event(int eTime, int ordID);
	int getEventTime();
	int getOrderID();
	virtual ~Event();

	// @param pRest a pointer to current Restaurant object 
	virtual void Execute(Restaurant* pRest)=0;	

}; // end Event


#endif