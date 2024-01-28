#ifndef _INSERVICE_MOTORS_COMPARATOR_H
#define _INSERVICE_MOTORS_COMPARATOR_H

#include "Comparator.h"
#include"Rest/Motorcycle.h"

class InServiceMotorsComp :
	public Comparator<Motorcycle*>
{
public:
	InServiceMotorsComp();
	virtual bool operator()(Motorcycle* Lhs, Motorcycle* Rhs) const;
	virtual ~InServiceMotorsComp();

}; // end  InServiceMotorsComp

#endif