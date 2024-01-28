#include "RestingMotorsComp.h"



RestingMotorsComp::RestingMotorsComp()
{
}

bool RestingMotorsComp::operator()(Motorcycle * Lhs, Motorcycle * Rhs) const
{
	return Lhs->GetRestingTime() < Rhs->GetRestingTime();
}


RestingMotorsComp::~RestingMotorsComp()
{
}
