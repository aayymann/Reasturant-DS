#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE typ, REGION reg): OrdType(typ), OrdRegion(reg), Event(eTime, oID)
{

}

ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE typ, REGION reg, int dist, double mny) : OrdType(typ), OrdRegion(reg),
OrdDistance(dist), OrdMoney(mny), Event(eTime, oID)
{

}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion, OrdDistance, OrdMoney);
	pOrd->SetArrtime(EventTime);
	pRest->AddOrder(pOrd);
}

int ArrivalEvent::GetOrdDistance() const
{
	return OrdDistance;
}

bool ArrivalEvent::SetOrdDistance(int dist)
{
	OrdDistance = dist;
	return true;
}

ORD_TYPE ArrivalEvent::GetOrdType() const
{
	return OrdType;
}

bool ArrivalEvent::SetOrdType(ORD_TYPE typ)
{
	OrdType = typ;
	return true;
}

REGION ArrivalEvent::GetOrdRegion() const
{
	return OrdRegion;
}

bool ArrivalEvent::SetOrdRegion(REGION reg)
{
	OrdRegion = reg;
	return true;
}

double ArrivalEvent::GetOrdMoney() const
{
	return OrdMoney;
}

bool ArrivalEvent::SetOrdMoney(double mny)
{
	OrdMoney = mny;
	return true;
}
