#include "VIPOrdersComp.h"



VIPOrdersComp::VIPOrdersComp()
{
}

bool VIPOrdersComp::operator()(Order * Lhs, Order * Rhs) const
{
	int p1 = Lhs->GetDistance() * 3 + Lhs->GetMoney() * 7;
	int p2 = Rhs->GetDistance() * 3 + Rhs->GetMoney() * 7;
	return p1 < p2;
}


VIPOrdersComp::~VIPOrdersComp()
{
}
