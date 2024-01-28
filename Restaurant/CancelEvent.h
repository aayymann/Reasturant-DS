#ifndef __CANCEL_EVENT_H_
#define __CANCEL_EVENT_H_

#include "Events/Event.h"

class CancelEvent : public Event
{
public:
	CancelEvent(int eTime, int ID);
	virtual void Execute(Restaurant* pRest);
	virtual ~CancelEvent();
}; // end CancelEvent


#endif
