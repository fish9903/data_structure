//--------------------------------------------------------------------
//
//  Laboratory 5                                        stackarr.cpp
//
//  SOLUTION: Array implementation of the Stack ADT
//
//--------------------------------------------------------------------
//2018112072_Á¶±¤È£
#include "stackarr.h"

//--------------------------------------------------------------------

template <class DT>
Stack<DT>::Stack(int maxNumber)
{
	maxSize = maxNumber;
	top = -1;
	element = new DT[maxSize];
}

//--------------------------------------------------------------------

template <class DT>
Stack<DT>:: ~Stack()
{
	if (element != nullptr)
		delete[] element;
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::push(const DT& newElement)
{
	if (isFull())
	{
		cout << "Push Fail. The stack is Full" << endl;
		return;
	}

	element[++top] = newElement;
}

//--------------------------------------------------------------------

template <class DT>
DT Stack<DT>::pop()
{
	if (isEmpty())
	{
		cout << "Pop Failed. The stack is Empty" << endl;
		return NULL;
	}
	return element[top--];
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::clear()
{
	top = -1;
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isEmpty() const
{
	if (top == -1)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

template <class DT>
bool Stack<DT>::isFull() const
{
	if (top == maxSize - 1)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------

template <class DT>
void Stack<DT>::showStructure() const
{
	if (top == -1)
	{
		cout << "The stack is Empty" << endl;
		return;
	}


	for (int i = 0; i < top + 1; i++)
		cout << "| " << element[i] << " |";
	for (int i = top + 1; i < maxSize; i++)
		cout << "| Empty |";
	cout << endl;
}