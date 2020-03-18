#pragma once
#include <iostream>
using namespace std;
#include"Generic_DS/Node.h"
template<class T>
class List
{
	Node <T>* Head;
	int count;
	Node <T>* GetPtr(T item)const;
public:
    List();
	~List();
	void Add(T item);
	void InsertEnd(T item);
	bool Remove(T item);
	bool DeleteAll();
	bool IsHere(T item)const;
	T GetItem(int ID);
	bool PeekHead(T& item);   //Returns the item in the Head Node in Item and removes it
	int GetCount()const;
	void PrintList()const;
	T GetItemByPosition(int i);
	T PeekHead2();	//Returns the item in the Head Node in Item without removing
};
template<class T>
List<T>::List()
{
	count = 0;
	Head = nullptr;
}
template<class T>
void List<T> :: Add(T item)
{
	Node <T>*A = new Node<T>;
	A->setItem(item);
	A->setNext(Head);
	Head = A;
	count++;


}
template<class T>

T List<T> :: GetItem(int ID)
{
	Node<T> * temp = Head;
	while (temp != NULL)
	{
		if (temp->getItem()->GetID() == ID)
		{
			return temp->getItem();
		}
		temp = temp->getNext();
	}
	return NULL;
}
template<class T>
bool List<T>::PeekHead(T & item)
{
	if (Head) {
		item = Head->getItem();
		return Remove(Head->getItem());
	}
	else {
		item = NULL;
		return false;
	}
}
template<class T>
void  List<T> ::InsertEnd(T item)
{
	Node<T>* A = new Node<T>;
	A->setItem(item);
	A->setNext(nullptr);
	Node<T>* temp = Head;
	if (temp == nullptr)
	{
		Head = A;
		count++;
		return;
	}
	while (temp) {
		if (temp->getNext() == nullptr)
			break;
		else
		temp=temp->getNext();
	}
	temp->setNext(A);
	count++;
}
template<class T>
bool List<T>:: Remove(T item) //Modified
{
	Node<T> * prev = Head;
	Node<T> * curr = Head;
	if(Head==NULL)
		return false;
	else
	{
		if(Head->getItem()==item)
		{
			if(Head->getNext()!=NULL)
			{
				Head = Head->getNext();
				delete curr;
				prev = Head;
				curr = prev;
				count--;
				return true;
			}
			else
			{
				delete Head;
				Head = NULL;
				curr = NULL;
				prev = NULL;
				count--;
				return true;
			}
		}
		else
		{
			while(curr->getNext()!=NULL)
			{
				prev=curr;
				curr = curr->getNext();
				if(curr->getItem()==item)
				{
					prev ->setNext(curr->getNext());
					delete curr;
					curr = prev;
					count--;
					return true;
				}
			}
		}
		return false;
	}
}
template<class T>
bool List<T>:: DeleteAll()
{
	Node <T> * temp;
	temp = Head;
	while (temp != NULL)
	{
		temp = Head->getNext();
		delete Head;
		Head = temp;
		count--;

	}
	if (count == 0)
		return true;
	else
		return false;

}
template<class T>
bool List<T>:: IsHere(T item)const
{
	if (GetPtr(item))
		return true;
	else
		return false;
}

template<class T>
int List<T>:: GetCount()const
{
	return count;

}
template<class T>
Node <T> * List<T> :: GetPtr(T item)const
{
	Node<T> * temp = Head;
	while (temp != nullptr)
	{
		if (temp->getItem() == item)
		{
			return temp;
		}
		temp=temp->getNext();
		
	}
	temp = nullptr;
	return temp;
}
template<class T>
void List<T>::PrintList() const{
	Node<T>* temp=Head;
	if (Head == NULL) {
		cout << "List is clear!" << endl;
		return;
	}
	cout << "count=" << count<<endl;
	while (temp) {
		cout << temp->getItem() << "   ";
		temp = temp->getNext();
	}
	cout << endl;
}
template<class T>
T List<T>::GetItemByPosition(int i)
{
	Node<T>*A = Head;
	if (i > count || i<0) {
		return NULL;
	}
	for (int j = 1; j <= count; j++) {
		if (j == i) 
		{
			return A->getItem();
		}
		else {
			A = A->getNext();
		}
	}
}
template<class T>
T List<T>::PeekHead2()
{
	if (Head == NULL)
	{
		return NULL;
	}
	else
	{
		return Head->getItem();
	}

}
template<class T>
List <T>::~List()
{
	DeleteAll();
}

