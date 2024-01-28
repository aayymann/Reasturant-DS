#ifndef _RESTING_MOTORS_COMPARATOR_H_
#define _RESTING_MOTORS_COMPARATOR_H_

#include"Comparator.h"
#include"Rest/Motorcycle.h"

#include "Comparator.h"
class RestingMotorsComp :
	public Comparator<Motorcycle*>
{
public:
	RestingMotorsComp();
	virtual bool operator()(Motorcycle* Lhs, Motorcycle* Rhs) const;
	virtual ~RestingMotorsComp();
}; // end RestingMotorsComp

#endif 

