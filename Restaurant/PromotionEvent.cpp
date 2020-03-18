#include "PromotionEvent.h"


PromotionEvent::PromotionEvent(int Ts, int ID, int Extramoney) :Event(Ts, ID) {
	ExtraMoney = Extramoney;
}


void PromotionEvent::Execute(Restaurant* pRest)
{
	pRest->PromoteOrder(Event::OrderID, ExtraMoney);
}
