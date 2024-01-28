#include "Order.h"

Order::Order(int oID, ORD_TYPE r_Type, REGION r_region, int distance, double mny)
{
	ID = (oID>0&&oID<1000)?oID:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	Distance = distance;
	totalMoney = (mny > 0) ? mny : 0;
}

Order::~Order()
{
}

int Order::GetID() const
{
	return ID;
}

void Order::SetID(int oID)
{
	ID = oID;
}


int Order::GetType() const
{
	return type;
}

int Order::GetArrTime() const
{
	return ArrTime;
}

int Order::GetServTime() const
{
	return ServTime;
}

int Order::GetWaitingTime() const
{
	return WaitingTime;
}

int Order::GetFinishTime() const
{
	return ArrTime + ServTime + WaitingTime;
}

void Order::SetType(ORD_TYPE r)
{
	type = r;
}

void Order::SetArrtime(int ts)
{
	ArrTime = ts;
}

void Order::SetServTime(int ts)
{
	ServTime = ts;
}

void Order::SetWaitingTime(int ts)
{
	WaitingTime = ArrTime - ts;
}

void Order::IncrementWaitingTime()
{
	WaitingTime++;
}

void Order::IncrementMoney(double mny)
{
	totalMoney += mny;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetRegion(REGION r_region)
{
	Region = r_region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

double Order::GetMoney() const
{
	return totalMoney;
}

void Order::SetMoney(double mny)
{
	totalMoney = mny;
}
