#include "MotorCyclesComp.h"



MotorCyclesComp::MotorCyclesComp()
{
}

bool MotorCyclesComp::operator()(Motorcycle * Lhs, Motorcycle * Rhs) const
{
	return Lhs->GetSpeed() < Rhs->GetSpeed();
}


MotorCyclesComp::~MotorCyclesComp()
{
}
