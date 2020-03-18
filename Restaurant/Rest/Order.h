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

	int ArrTime, ServTime, FinishTime  , WaitingTime;	//arrival, service start, and finish times
	//WaitingTime=ArrivalTime-TimeOFAssigningMotors

public:
	Order(int id, ORD_TYPE r_Type, REGION r_region, int distance, double Money);
	Order();
	virtual ~Order();
	void setID(int id);
	void setRegion(REGION r_region);
	void setType(ORD_TYPE r);
	int GetID();
	void SetArrtime(int ts);
	int GetType() const;
	REGION GetRegion() const;

	//This fn Sets the Time when the order is assigned to a Motor 
	void SetWaitingTime(int AssignMotorT);

	//Increment Waiting time. Should be called every timestep
	void IncrementWT();

	void SetServiceTime(int ts);
	int GetArrivalTime()const;
	int GetWaitingTime() const;
	int GetServiceTime();
	int GetFinishTime() const;
	void SetFinishTime();
    void SetMoney(double mny);// testing 
	void SetDistance(int d);
	int GetDistance() const;
	double GetMoney() const;
};

#endif