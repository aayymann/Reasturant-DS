#include "FOPQ.h"



FOPQ::FOPQ()
{
}

int FOPQ::PriorityEquation(Order * item)
{
	//Finish time has bigger weight since orders must be sorted according to Finish time then Service time 
	return -((item->GetFinishTime()*50) + (item->GetServiceTime()*2));
}


FOPQ::~FOPQ()
{
}
