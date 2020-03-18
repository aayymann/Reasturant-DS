#pragma once
#include "PriorityQueue.h"
#include"Rest/Motorcycle.h"
class RestingMotorsPQ : public PriorityQueue<Motorcycle*>
{
public:
	virtual int PriorityEquation(Motorcycle *);

};

