#include "VIPPQ.h"

int VIPPQ::PriorityEquation(Order *item)
{
	int z;
	z = item->GetDistance() * 3 + item->GetMoney() * 7;
	return z;
}

bool VIPPQ::NormalEnqueue(Order * item)
{
	Node<Order*>* newNodePtr = new Node<Order*>(item);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true;
}
