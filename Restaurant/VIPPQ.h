#pragma once
#include "PriorityQueue.h"
#include"Rest/Order.h"

class VIPPQ : public PriorityQueue<Order*>
{
public:
	virtual int PriorityEquation(Order* item);
	bool NormalEnqueue(Order* item);

};

