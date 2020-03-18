#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg, int distance, double money):Event(eTime, oID)
{

	OrdType = oType;
	OrdRegion = reg;
	OrdDistance = distance;
	OrdMoney = money;
}

ORD_TYPE ArrivalEvent::getOrderType() const
{
	return OrdType;
}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
	Order* pOrd = new Order(OrderID, OrdType, OrdRegion,OrdDistance,OrdMoney);
	pRest->AddOrder(pOrd);
	pOrd->SetArrtime(Event::EventTime);
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2


//	pRest->AddtoDemoQueue(pOrd);
}

int ArrivalEvent::GetDist() const {
	return OrdDistance;
}
double ArrivalEvent::GetOrdMoney() const {
	return OrdMoney;
}
