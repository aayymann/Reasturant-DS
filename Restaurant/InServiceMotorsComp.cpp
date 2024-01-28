#include "InServiceMotorsComp.h"



InServiceMotorsComp::InServiceMotorsComp()
{
}

bool InServiceMotorsComp::operator()(Motorcycle * Lhs, Motorcycle * Rhs) const
{
	return -(Lhs->GetFinishTime()) < -(Rhs->GetFinishTime());
}


InServiceMotorsComp::~InServiceMotorsComp()
{
}
