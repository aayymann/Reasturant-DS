#ifndef __PROMOTION_EVENT_H_
#define __PROMOTION_EVENT_H_

#include "Events/Event.h"
class PromotionEvent : public Event
{
	double ExtraMoney;
public:
	PromotionEvent(int eTime, int ID, double Extramoney);
	virtual void Execute(Restaurant* pRest);
	virtual ~PromotionEvent();
}; // end PromotionEvent

#endif 