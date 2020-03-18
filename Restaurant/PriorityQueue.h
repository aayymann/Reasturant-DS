#pragma once
#include <iostream>
using namespace std;
#include"Generic_DS/Queue.h"
template <class T>
class PriorityQueue : public Queue<T>
{
public :
	PriorityQueue();
	virtual int PriorityEquation(T item) = 0;
	virtual bool enqueue(const T& newEntry );
     void PrintQueue()const ;                              //TESTING 
	virtual ~ PriorityQueue() ;
};

template <class T>
PriorityQueue<T>::PriorityQueue():Queue<T>() {

}
template <class T>
 bool PriorityQueue<T>:: enqueue(const T& newEntry)
{
	 Node<T>* A = new Node<T>(newEntry);
	 A->setNext(nullptr);
	 Node<T>* temp = frontPtr;

	 if (temp == NULL)     //if the P Queue is empty 
	 {
		 frontPtr = A;
		 backPtr = A;
		 return true;
	 }
	 if (temp->getNext() == NULL)      // if the P Queue has only one Node 
	 {
		 if (PriorityEquation(newEntry) > PriorityEquation(temp->getItem()))  // if the P Queue has one Node and priority A is greater than the first Node
		 {
			 A->setNext(frontPtr);
			 frontPtr = A;
			 return true;
		 }
		 else // if the P Queue has one Node and priority A is less than the first Node
		 {
			 temp->setNext(A);
			 backPtr = A;
			 return true;
		 }
	 }
	 if (PriorityEquation(temp->getItem()) < PriorityEquation(A->getItem()))   //if A has greater priority than All
	 {
		 A->setNext(temp);
		 frontPtr = A;
		 return true;
	 }
	 if (PriorityEquation(A->getItem()) < PriorityEquation(backPtr->getItem())) // if A has least prio
	 {
		 backPtr->setNext(A);
		 backPtr = A;
		 return true;
	 }
	 Node<T>* temp2 = temp->getNext();
	 while (temp2)               //for the rest of the cases
	 {
		 
		 if (PriorityEquation(temp->getItem()) > PriorityEquation(A->getItem()) && PriorityEquation(A->getItem()) > PriorityEquation(temp2->getItem()))
		 {
			 temp->setNext(A);
			 A->setNext(temp2);
			 return true;
		 }
		 temp = temp2;
		 temp2 = temp2->getNext();
	 }
	 return false;
}

 
 template<class T>
 void PriorityQueue<T>::PrintQueue() const  {
	 Node<T>* temp = frontPtr;
	 if (temp == NULL) {
		 cout << "List is clear!" << endl;
		 return;
	 }
	 while (temp) {
		temp->getItem()->Print();
		 temp = temp->getNext();
	 }
	 cout << endl;
 }
 
 template<class T>
 PriorityQueue<T> ::~PriorityQueue()
 {

 }