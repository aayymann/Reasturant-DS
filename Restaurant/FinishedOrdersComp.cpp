#include "FinishedOrdersComp.h"

FinishedOrdersComp::FinishedOrdersComp()
{
}

bool FinishedOrdersComp::operator()(Order * Lhs, Order * Rhs) const
{
	int p1 = ((Lhs->GetFinishTime() * 50) + (Lhs->GetServTime()));
	int p2 = ((Rhs->GetFinishTime() * 50) + (Rhs->GetServTime()));
	return p1 < p2;
}


FinishedOrdersComp::~FinishedOrdersComp()
{
}
