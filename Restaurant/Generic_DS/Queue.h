#ifndef __QUEUE_H_
#define __QUEUE_H_

#include "Node.h"

template <typename T>
class Queue
{
protected:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	Queue();
	~Queue();
	bool isEmpty() const;

	/**
	Adds newEntry at the back of this queue.
	@return True if the addition is successful, or False otherwise.
	*/
	bool enqueue(const T& newEntry);


	/**
	Removes the front of this queue. That is, removes the item that was added earliest.
	@return True if the operation is successful; otherwise false.
	*/
	bool dequeue(T& frntEntry);


	/**
	Gets the front of this queue. The operation does not modify the queue.
	@param frntEntry return The front of the queue.
	@return False if Queue is empty
	*/
	bool peekFront(T& frntEntry)  const;

}; // end Queue

template <typename T>
Queue<T>::Queue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

template <typename T>
bool Queue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool Queue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	return true;
}

template <typename T>
bool Queue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;
}

template <typename T>
bool Queue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
Queue<T>::~Queue()
{
}

#endif