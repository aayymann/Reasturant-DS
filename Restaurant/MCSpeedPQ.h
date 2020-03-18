#pragma once
#include"PriorityQueue.h"
#include"Rest/Motorcycle.h"
class MCSpeedPQ : public PriorityQueue<Motorcycle*>
{

	virtual int PriorityEquation(Motorcycle * A);

};

