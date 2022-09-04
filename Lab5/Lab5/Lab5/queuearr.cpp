//2018112072_Á¶±¤È£
#include "queuearr.h"
#include <iostream>

using namespace std;

template<class DT>
Queue<DT>::Queue(int maxNumber)
{
	maxSize = maxNumber + 1;
	front = maxSize - 1;
	rear = maxSize - 1;
	element = new DT[maxSize];
}

template<class DT>
Queue<DT>::~Queue()
{
	if (element != NULL)
		delete[] element;
}

template<class DT>
void Queue<DT>::enqueue(const DT& newData)
{
	if (isFull())
	{
		cout << "Enqueue Failed. The Queue is Full" << endl;
		return;
	}

	rear = (rear + 1) % maxSize;
	element[rear] = newData;
}

template<class DT>
DT Queue<DT>::dequeue()
{
	if (isEmpty())
	{
		cout << "Dequeue Failed. The Queue is Empty" << endl;
		return NULL;
	}

	front = (front + 1) % maxSize;
	return element[front];
}

template<class DT>
void Queue<DT>::clear()
{
	front = maxSize - 1;
	rear = maxSize - 1;
}

template<class DT>
bool Queue<DT>::isEmpty() const
{
	if (front == rear)
		return true;
	else
		return false;
}

template<class DT>
bool Queue<DT>::isFull() const
{
	if ((rear + 1) % maxSize == front)
		return true;
	else
		return false;
}

template<class DT>
void Queue<DT>::showStructure() const
{
	if (isEmpty())
	{
		cout << "The Queue is empty" << endl;
		return;
	}

	cout << "front : " << front << ", rear : " << rear << endl;

	for (int i = 0; i < maxSize; i++)
	{
		cout << i << "\t";
	}
	cout << endl;

	//for (int i = (front + 1) % maxSize; i != (rear + 1) % maxSize; i = (i + 1) % maxSize)
	//{
	//	cout << element[i] << "\t";
	//}
	for (int i = 0; i < maxSize; i++)
	{
		if (front == i)
			cout << "front\t";
		else if (front < rear)
		{
			if (front < i && i <= rear)
				cout << element[i] << "\t";
			else
				cout << "\t";
		}
		else if (rear < front)
		{
			if (front < i || i <= rear)
				cout << element[i] << "\t";
			else
				cout << "\t";
		}
	}
}

template<class DT>
void Queue<DT>::putFront(const DT& newDataItem)
{
	if (isFull())
	{
		cout << "PutFront Failed. The queue is Full" << endl;
		return;
	}

	if (front == 0)
	{
		element[front] = newDataItem;
		front = maxSize - 1;
	}
	else
	{
		element[front] = newDataItem;
		front--;
	}
}


template<class DT>
DT Queue<DT>::getRear()
{
	if (isEmpty())
	{
		cout << "getRear Failed. The queue is Empty" << endl;
		return NULL;
	}

	DT temp = rear;
	rear--;

	return element[temp];
}

template<class DT>
int Queue<DT>::getLength() const
{
	if (isEmpty())
		return 0;
	if (isFull())
		return maxSize - 1;

	if (front < rear)
	{
		return rear - front;
	}
	else
	{
		return rear + maxSize - front;
	}
}
