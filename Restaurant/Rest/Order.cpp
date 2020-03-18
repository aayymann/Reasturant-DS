#include "Order.h"
#include<iostream>
using namespace std;

Order::Order(int id, ORD_TYPE r_Type, REGION r_region, int distance, double money)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
	WaitingTime = 0;
	Distance = distance;
	totalMoney = money;
}

Order::Order()
{
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}
void Order::SetArrtime(int ts)
{
	ArrTime = ts;
}
void Order :: setRegion(REGION r_region)
{
	Region = r_region;
}
void Order :: setType(ORD_TYPE r)
{
	type = r;
}

void Order :: setID(int id)
{
	ID = id;
}
int Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetWaitingTime(int AssignMotorT)
{
	WaitingTime =   AssignMotorT- ArrTime;
}

void Order::IncrementWT()
{
	WaitingTime++;
}

void Order::SetServiceTime(int ts)
{
	ServTime = ts;
}

int Order::GetArrivalTime() const
{
	return ArrTime;
}

int Order::GetWaitingTime() const
{
	return WaitingTime;
}

int Order::GetServiceTime()
{
	return ServTime;
}

int Order::GetFinishTime() const
{
	return ArrTime + ServTime + WaitingTime;
}

void Order::SetFinishTime()
{
	FinishTime = ArrTime+ServTime+WaitingTime;
}

void Order::SetMoney(double mny)
{
	totalMoney = mny;
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
/*
void Order::Print()
{
	cout << totalMoney << endl;
	cout << Distance << endl;
}
*/
