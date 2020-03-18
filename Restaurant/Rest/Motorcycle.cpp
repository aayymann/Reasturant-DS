#include "Motorcycle.h"


Motorcycle::Motorcycle()
{

}
Motorcycle::Motorcycle(int S,MC_TYPE t, int id1)
{
	ID = id1;
	type = t;
	speed = S;
	RestingTime = 0;
}
void Motorcycle::SetOrdAndMotor(Order * pOrd)
{
	ptr = pOrd;
}
void Motorcycle::SetOrderServiceTime()
{
	int svt = ptr->GetDistance() *2/ speed;
	ptr->SetServiceTime(svt);
}


Order * Motorcycle::GetOrder()
{
	return this->ptr;
}



int Motorcycle::GetFinishTime()
{
	return ptr->GetFinishTime();
}

MC_TYPE Motorcycle::GetMCType()
{
	return type;
}

int Motorcycle::GetSpeed()
{
	return speed;
}


void Motorcycle::SetRestingTime()
{
	int dist = ptr->GetDistance();
	if (dist > 20 && dist < 60)
	{
		RestingTime = 2;
	}
	else if (dist > 60 && dist < 100)
	{
		RestingTime = 4;
	}
	else
	{
		RestingTime = 6;
	}

}
int Motorcycle::GetRestingTime()
{
	return RestingTime;
}

void Motorcycle::SetSpeed(int value)
{
	speed = value;
}

Motorcycle::~Motorcycle()
{
}
