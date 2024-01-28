#ifndef _MOTOR_CYCLES_COMPARATOR
#define _MOTOR_CYCLES_COMPARATOR

#include"Comparator.h"
#include"Rest/Motorcycle.h"

#include "Comparator.h"
class MotorCyclesComp :
	public Comparator<Motorcycle*>
{
public:
	MotorCyclesComp();
	virtual bool operator()(Motorcycle* Lhs, Motorcycle* Rhs) const;
	virtual ~MotorCyclesComp();
}; // end MotorCyclesComp

#endif 