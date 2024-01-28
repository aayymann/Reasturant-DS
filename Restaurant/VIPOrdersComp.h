#ifndef _VIP_ORDERS_COMPARATOR_H
#define _VIP_ORDERS_COMPARATOR_H

#include"Comparator.h"
#include"Rest/Order.h"

class VIPOrdersComp :
	public Comparator<Order*>
{
public:
	VIPOrdersComp();
	virtual bool operator()(Order* Lhs, Order* Rhs) const;
	virtual ~VIPOrdersComp();
}; // end VIPOrdersComp 

#endif
