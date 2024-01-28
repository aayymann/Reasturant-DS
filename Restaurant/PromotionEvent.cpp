#include "PromotionEvent.h"
#include"Rest/Restaurant.h"

PromotionEvent::PromotionEvent(int eTime, int ID, double Extramoney) : ExtraMoney(Extramoney), Event(eTime, ID)
{
}

void PromotionEvent::Execute(Restaurant * pRest)
{
	pRest->PromoteOrder(OrderID, ExtraMoney);
}

PromotionEvent::~PromotionEvent()
{
}
