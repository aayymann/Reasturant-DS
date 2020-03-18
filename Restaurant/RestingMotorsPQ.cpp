#include "RestingMotorsPQ.h"





int RestingMotorsPQ::PriorityEquation(Motorcycle *A)
{
	int z = A->GetRestingTime();
	return -z;

}
