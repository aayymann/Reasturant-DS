#ifndef __PRIORITY_QUEUE_H_
#define __PRIORITY_QUEUE_H_

#include"Generic_DS/Queue.h"
#include"Comparator.h"

template <typename T, class PriorityEquation = Comparator<T> >
class PriorityQueue : public Queue<T>
{
private: 

	// Functor that @return True if the first parameter is less than the second paramater
	PriorityEquation PE; 
public:
	PriorityQueue();
	virtual bool enqueue(const T& newEntry);
	virtual ~PriorityQueue();
}; // end PriorityQueue

template <typename T, class PriorityEquation>
PriorityQueue<T, PriorityEquation>::PriorityQueue() :Queue<T>() {
	(void)static_cast<Comparator<T>*>((PriorityEquation*)0); // To check that the PriorityEquation class is derived from Comparator class
}

template <typename T, class PriorityEquation>
bool PriorityQueue<T, PriorityEquation>::enqueue(const T& newEntry)
{
	Node<T>* NewNode = new Node<T>(newEntry, nullptr);
	Node<T>* temp = frontPtr;

	if (temp == nullptr)     //if the P Queue is empty 
	{
		frontPtr = NewNode;
		backPtr = NewNode;
		return true;
	}

	if (frontPtr->getNext() == nullptr)      // if the P Queue has only one Node 
	{
		if ( PE(temp->getItem()), newEntry)  // if the Queue has one Node and priority NewNode is greater than the first Node
		{
			NewNode->setNext(frontPtr);
			frontPtr = NewNode;
			return true;
		}

		else // if the Queue has one Node and priority NewNode is less than the first Node
		{
			temp->setNext(NewNode);
			backPtr = NewNode;
			return true;
		}
	}

	if ( PE(temp->getItem(), newEntry) )   //if NewNode has greater priority than All
	{
		NewNode->setNext(temp);
		frontPtr = NewNode;
		return true;
	}

	if (  PE(newEntry, backPtr->getItem()) ) // if NewNode has the least priority
	{
		backPtr->setNext(NewNode);
		backPtr = NewNode;
		return true;
	}

	Node<T>* temp2 = temp->getNext();
	while (temp2)  // General case
	{
		if ( PE(newEntry, temp->getItem()) && PE(temp2->getItem(), newEntry) )
		{
			temp->setNext(NewNode);
			NewNode->setNext(temp2);
			return true;
		}
		temp = temp2;
		temp2 = temp2->getNext();
	}
	return false;
}

template <typename T, class PriorityEquation>
PriorityQueue<T, PriorityEquation> ::~PriorityQueue()
{

}

#endif 