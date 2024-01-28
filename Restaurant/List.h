#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include"Error.h"
#include"Generic_DS\Node.h"

template<typename T>
class List {
private:
	int count;
	Node<T>* Head;

	/**
	Get a pointer to the first node containing passed item
	@return nullptrptr if the list doesn't contain the passed item
	*/
	Node<T>* GetPtr(T item)const;

public:
	List();

	// Add item to the first position in the list
	void Insert(T item); 
	void InsertEnd(T item);
	bool Remove(T item);
	bool DeleteAll();
	bool Contains(T item)const;
	int GetCount()const;

	// Gets the first item in list and removes it 
	bool PopHead(T& item);   

	// Gets the first item in list 
	bool PeekHead(T& item) const;	
	bool isEmpty() const;

	/**
	Gets item by index
	@throw OutOfRange error if index is out of range
	*/
	T GetItem(int pos) const;
	~List();

	class Iterator; //Forward declaration
	Iterator begin();
	Iterator end(); // End of LinkedList wrapped in Iterator type 

}; //end List

template<typename T>
class List<T>::Iterator {
private:
	const Node<T>* currNode;

public:
	Iterator() : currNode(Head) { }

	Iterator(const Node<T>* pNode) : currNode(pNode) { }

	bool operator!=(const Iterator& iterator) { return currNode != iterator.currNode; }

	bool operator==(const Iterator& iterator) { return currNode == iterator.currNode; }

	T operator*() { return currNode->getItem(); }

	Iterator& operator=(Node<T>* pNode)
	{
		this->currNode = pNode;
		return *this;
	}

	// Prefix ++ overload 
	Iterator& operator++() 
	{
		if (currNode)
			currNode = currNode->getNext();
		return *this;
	}

	// Postfix ++ overload
	Iterator operator++(int) 
	{
		Iterator iter = *this;
		++*this;
		return iter;
	}

	Iterator& operator+(int i)
	{
		Iterator iter = *this;
		while (i-- > 0 && iter.p)
		{
			++iter;
		}
		return iter;
	}
}; // end Iterator

template<typename T>
Node<T>* List<T>::GetPtr(T item) const
{
	Node<T>* temp = Head;
	while (temp != nullptr)
	{
		if (temp->getItem() == item)
		{
			return temp;
		}
		temp = temp->getNext();
	}
	temp = nullptr;
	return temp;
}

template<typename T>
List<T>::List()
{
	count = 0;
	Head = nullptr;
}

template<typename T>
void List<T> ::Insert(T item)
{
	Node<T>* NewNode = new Node<T>;
	NewNode->setItem(item);
	NewNode->setNext(Head);
	Head = NewNode;
	count++;
}

template<typename T>
T List<T> ::GetItem(int pos) const
{
	if (pos > count || pos < 0)
		throw error::OUT_OF_RANGE;

	Node<T>* temp = Head;
	for (int i = 1; i <= count; i++) {
		if (i == pos)
			break;
		else
			temp = temp->getNext();
	}
	return temp->getItem();
}

template<typename T>
bool List<T>::PopHead(T & item)
{
	if (Head) {
		item = Head->getItem();
		return Remove(Head->getItem());
	}
	else
		return false;
}

template<typename T>
void  List<T> ::InsertEnd(T item)
{
	Node<T>* NewNode = new Node<T>(item, nullptr);

	if (count == 0)
	{
		Head = NewNode;
		count++;
		return;
	}

	Node<T>* temp = Head;
	while (temp) {
		if (temp->getNext() == nullptr)
			break;
		else
			temp = temp->getNext();
	}
	temp->setNext(NewNode);
	count++;
	return;
}

template<typename T>
bool List<T>::Remove(T item)
{
	if (Head == nullptr)
		return false;

	Node<T>* prev = Head;
	Node<T>* curr = Head;

	if (Head->getItem() == item) //if the item is the first in the list
	{
		if (Head->getNext() != nullptr)
		{
			Head = Head->getNext();
			delete curr;
			curr = nullptr;
			prev = nullptr;
			count--;
			return true;
		}
		else
		{
			delete Head;
			Head = nullptr;
			curr = nullptr;
			prev = nullptr;
			count--;
			return true;
		}
	}

	while (curr->getNext() != nullptr)
	{
		prev = curr;
		curr = curr->getNext();

		if (curr->getItem() == item)
		{
			prev->setNext(curr->getNext());
			delete curr;
			curr = prev;
			count--;
			return true;
		}
	}

	return false; //if the item is not found
}

template<typename T>
bool List<T>::DeleteAll()
{
	Node<T>* temp;
	temp = Head;
	while (temp != nullptr)
	{
		temp = Head->getNext();
		delete Head;
		Head = temp;
		count--;
	}

	return true;
}

template<typename T>
bool List<T>::Contains(T item)const
{
	if (GetPtr(item))
		return true;
	else
		return false;
}

template<typename T>
int List<T>::GetCount() const
{
	return count;
}

template<typename T>
bool List<T>::PeekHead(T& item) const
{
	if (Head) {
		item = Head->getItem();
		return true;
	}
	else {
		item = nullptr;
		return false;
	}
}

template<typename T>
bool List<T>::isEmpty() const
{
	return count == 0;
}

template<typename T>
List <T>::~List()
{
	DeleteAll();
}

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	return Iterator(Head);
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
	return Iterator(nullptr);
}

#endif