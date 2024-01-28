#include "Motorcycle.h"


Motorcycle::Motorcycle(double ISpeed, MOTOR_TYPE typ, int oID): speed(ISpeed), type(typ), ID(oID)
, Ord(nullptr), status(IDLE), RestingTime(0), OrdFinishTime(0)
{

}

int Motorcycle::GetID() const
{
	return ID;
}

MOTOR_TYPE Motorcycle::GetType() const
{
	return type;
}

double Motorcycle::GetSpeed() const
{
	return speed;
}

STATUS Motorcycle::GetStatus() const
{
	return status;
}

Order * Motorcycle::GetOrder() const
{
	return Ord;
}

int Motorcycle::GetRestingTime() const
{
	return RestingTime;
}

int Motorcycle::GetFinishTime() const
{
	return OrdFinishTime;
}

void Motorcycle::SetOrder(Order * pOrd)
{
	Ord = pOrd;
	UpdateRestTime();
	UpdateOrderServTime();
	OrdFinishTime = Ord->GetFinishTime();
}

void Motorcycle::SetSpeed(int ISpeed)
{
	speed = ISpeed;
}

void Motorcycle::SetStatus(STATUS st)
{
	status = st;
}

bool Motorcycle::ReleaseOrder(Order* & pOrd)
{
	if (!Ord)
		return false;

	pOrd = Ord;
	Ord = nullptr;
	return true;
}

void Motorcycle::UpdateRestTime()
{
	if (!Ord)
		return;

	int dist = Ord->GetDistance();
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

void Motorcycle::UpdateOrderServTime()
{
	if (!Ord)
		return;

	int SVT = Ord->GetDistance() * 2 / speed;
	Ord->SetServTime(SVT);
}


Motorcycle::~Motorcycle()
{
}
