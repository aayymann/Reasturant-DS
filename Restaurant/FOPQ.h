#pragma once
#include"PriorityQueue.h"
#include"Rest/Order.h"

//Finished Orders Priority Queue
class FOPQ : public PriorityQueue<Order*>
{
public:
	FOPQ();
	virtual int PriorityEquation(Order* item);
	~FOPQ();
};

