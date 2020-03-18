#pragma once
#include "PriorityQueue.h"
#include "Rest/Motorcycle.h"
class MCPQ :public PriorityQueue<Motorcycle*> {
public:
	virtual int PriorityEquation(Motorcycle* item);
};