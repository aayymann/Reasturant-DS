#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"

class ArrivalEvent: public Event
{
	int OrdDistance;	//Order distance
	ORD_TYPE OrdType;	//Order type: Normal, Frozen, VIP
	REGION OrdRegion;	//Region of this order	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent(int eTime, int oID, ORD_TYPE typ, REGION reg);
	ArrivalEvent(int eTime, int oID, ORD_TYPE typ, REGION reg, int dist, double mny);

	// Creates and order and and fills its data and pass it to restaurant object 
	virtual void Execute(Restaurant *pRest); 	

	int GetOrdDistance() const;
	bool SetOrdDistance(int dist);

	ORD_TYPE GetOrdType() const;
	bool SetOrdType(ORD_TYPE typ);

	REGION GetOrdRegion() const;
	bool SetOrdRegion(REGION reg);

	double GetOrdMoney() const;
	bool SetOrdMoney(double mny);

}; // end ArrivalEvent

#endif