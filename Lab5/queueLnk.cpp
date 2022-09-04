//2018112072_Á¶±¤È£
#include "queueLnk.h"
#include <iostream>

using namespace std;

template<class DT>
QueueNode<DT>::QueueNode(const DT& nodeData, QueueNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

template<class DT>
Queue<DT>::Queue(int maxNumber)
{
	front = NULL;
	rear = NULL;
}

template<class DT>
Queue<DT>::~Queue()
{
	clear();
}

template<class DT>
void Queue<DT>::enqueue(const DT& newData)
{
	if (isFull())
	{
		cout << "Enqueue Failed. The queue is Full" << endl;
		return;
	}

	QueueNode<DT>* newNode = new QueueNode<DT>(newData, NULL);	

	if (isEmpty())
	{
		front = newNode;
	}
	else
	{
		rear->next = newNode;
	}
	rear = newNode;
}

template<class DT>
DT Queue<DT>::dequeue()
{
	if (isEmpty())
	{
		cout << "Dequeue Failed. The queue is Empty" << endl;
		return NULL;
	}

	DT temp = front->dataItem;
	front = front->next;

	if (front == NULL)
		rear = NULL;

	return temp;
}

template<class DT>
void Queue<DT>::clear()
{
	QueueNode<DT>* tempPtr;

	while (front != NULL)
	{
		tempPtr = front;
		front = front->next;
		delete tempPtr;
	}
	rear = NULL;
}

template<class DT>
bool Queue<DT>::isEmpty() const
{
	if (front == NULL)
		return true;
	else
		return false;
}

template<class DT>
bool Queue<DT>::isFull() const
{
	QueueNode<DT>* ptr = new QueueNode<DT>(0, NULL);
	if (ptr == NULL)
		return true;
	else {
		delete ptr;
		return false;
	}
}

template<class DT>
void Queue<DT>::showStructure() const
{
	if (isEmpty())
	{
		cout << "The Queue is empty" << endl;
		return;
	}

	QueueNode<DT>* temp = front;
	while (temp != NULL)
	{
		cout << temp->dataItem << "\t";
		temp = temp->next;
	}
	cout << endl;

	delete temp;
}

template<class DT>
void Queue<DT>::putFront(const DT& newDataItem)
{
	if (isFull())
	{
		cout << "putFront Failed. The queue is Full" << endl;
		return;
	}

	QueueNode<DT>* newNode = new QueueNode<DT>(newDataItem, front);
	
	if (isEmpty())
	{
		rear = newNode;
	}

	front = newNode;

	
}


template<class DT>
DT Queue<DT>::getRear()
{
	if (isEmpty())
	{
		cout << "getRear Failed. The queue is Empty" << endl;
		return NULL;
	}

	DT temp = rear->dataItem;

	if (front->next == NULL)
	{
		front = NULL;
		rear = NULL;
		return temp;
	}

	QueueNode<DT>* tempPtr;
	
	tempPtr = front;
	while (tempPtr->next != rear)
	{
		tempPtr = tempPtr->next;
	}
	tempPtr->next = NULL;
	rear = tempPtr;

	return temp;
}

template<class DT>
int Queue<DT>::getLength() const
{
	if (isEmpty())
		return 0;
	
	QueueNode<DT>* tempPtr = new QueueNode<DT>(0, NULL);

	tempPtr = front;
	int length = 0;

	while (tempPtr != NULL)
	{
		length++;
		tempPtr = tempPtr->next;
	}

	delete tempPtr;
	return length;
}
