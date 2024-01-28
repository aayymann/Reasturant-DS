#ifndef _FINISHED_ORDERS_COMPARATOR_H
#define _FINISHED_ORDERS_COMPARATOR_H

#include"Comparator.h"
#include"Rest/Order.h"

class FinishedOrdersComp :
	public Comparator<Order*>
{
public:
	FinishedOrdersComp();
	virtual bool operator()(Order* Lhs, Order* Rhs) const;
	virtual ~FinishedOrdersComp();
}; // end FinishedOrdersComp

#endif 

