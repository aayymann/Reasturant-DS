#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"
#include "Order.h"
#pragma once
class Motorcycle	
{
	int ID;
	int speed;		//meters it can move in one clock tick (in one timestep)
	//REGION	region;	//region of the motorcycle
	Order*ptr;
	STATUS	status;	//idle or in-service
	MC_TYPE type; //Motorcycle type
	int RestingTime;
public:
	Motorcycle();
	Motorcycle(int S, MC_TYPE t, int id1);
	void SetOrdAndMotor(Order*pOrd);
	void SetOrderServiceTime();
	void SetSpeed(int value);
	Order*GetOrder();
	int GetFinishTime();
	MC_TYPE GetMCType();

	int GetSpeed();
	int GetRestingTime();
	void SetRestingTime();
	virtual ~Motorcycle();
};

#endif