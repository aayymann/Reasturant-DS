#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_

#include "..\Defs.h"
#include"Order.h"

#pragma once
class Motorcycle	
{
	int ID;
	MOTOR_TYPE type;	//for each order type there is a corresponding motorcycle type 
	double speed;		//meters it can move in one clock tick (in one timestep)
	STATUS	status;	//idle or in-service
	Order* Ord; //Order assigned to the motor
	int RestingTime; 
	int OrdFinishTime;

public:
	Motorcycle(double ISpeed, MOTOR_TYPE typ, int oID);
	~Motorcycle();

	int GetID() const;
	MOTOR_TYPE GetType() const;
	double GetSpeed() const;
	STATUS GetStatus() const;
	Order* GetOrder() const;
	int GetRestingTime() const; 
	int GetFinishTime() const;
	
	void SetOrder(Order* pOrd);
	void SetSpeed(int ISpeed);
	void SetStatus(STATUS st);

	bool ReleaseOrder(Order*& pOrd); // return Ord and it to NULL 
	void UpdateRestTime(); //updates the motor resting time according to the distance it have moved in the last delivery
	void UpdateOrderServTime(); //updates the order service time

}; // end Motorcycle

#endif