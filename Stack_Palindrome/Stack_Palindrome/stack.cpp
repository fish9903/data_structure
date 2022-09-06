#include "stack.h"

template <class DT>
Stack<DT>::Stack(int maxNumber) {
	maxSize = maxNumber;
	top = -1;
	element = new DT[maxSize];
}

template <class DT>
Stack<DT>::~Stack() {
	if (element != nullptr)
		delete[] element;
}

template <class DT>
void Stack<DT>::push(const DT& newElement) {
	if (isFull()) {
		cout << "The stack is full" << endl;
		return;
	}

	top++;
	element[top] = newElement;
}

template <class DT>
DT Stack<DT>::pop() {
	if (isEmpty()) {
		cout << "The stack is empty" << endl;
		return NULL;
	}

	top--;
	return element[top];
}

template <class DT>
void Stack<DT>::clear() {
	top = -1;
	return;
}

template <class DT>
bool Stack<DT>::isEmpty() const {
	if (top == -1)
		return true;
	else
		return false;
}

template <class DT>
bool Stack<DT>::isFull() const {
	if (top == maxSize - 1)
		return true;
	else
		return false;
}

template <class DT>
void Stack<DT>::showStack() const {
	if (isEmpty()) {
		cout << "The stack is empty" << endl;
	}
	else {
		for (int i = 0; i < top + 1; i++) {
			cout << element[i] << " ";
		}
		cout << endl;
	}

	return;
}