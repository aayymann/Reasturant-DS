#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	double totalMoney;	//Total order money
	int ArrTime, ServTime, WaitingTime;	//arrival, service and waiting times

public:
	Order(int oID, ORD_TYPE r_Type, REGION r_region, int distance, double mny);
	virtual ~Order();

	int GetID() const;
	REGION GetRegion() const;
	int GetDistance() const;
	double GetMoney() const;
	int GetType() const;

	int GetArrTime() const;
	int GetServTime() const;
	int GetWaitingTime() const;
	int GetFinishTime() const;

	void SetID(int oID);
	void SetRegion(REGION r_region);
	void SetDistance(int d);
	void SetMoney(double mny);
	void SetType(ORD_TYPE r);

	void SetArrtime(int ts);
	void SetServTime(int ts);
	void SetWaitingTime(int ts);

	void IncrementWaitingTime();
	void IncrementMoney(double mny);

}; //end Order

#endif