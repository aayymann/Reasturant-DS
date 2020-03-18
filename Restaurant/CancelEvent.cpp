#include "CancelEvent.h"




CancelEvent::CancelEvent(int eTime, int ID) : Event (eTime , ID)
{
	

}

void CancelEvent::Execute(Restaurant * pRest)
{
	pRest->CancelOrder(Event ::OrderID);
	
}


CancelEvent::~CancelEvent()
{
}
