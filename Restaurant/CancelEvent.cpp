#include "CancelEvent.h"
#include "Rest/Restaurant.h"


CancelEvent::CancelEvent(int eTime, int ID) : Event(eTime, ID)
{
}

void CancelEvent::Execute(Restaurant * pRest)
{
	pRest->CancelOrder(OrderID);
}

CancelEvent::~CancelEvent()
{
}
