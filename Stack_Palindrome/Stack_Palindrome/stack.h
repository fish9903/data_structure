#pragma once
#include <iostream>

using namespace std;

const int defMaxStackSize = 10; // Default maximum stack size

template < class DT >
class Stack {
public:
	Stack(int maxNumber = defMaxStackSize);
	~Stack();

	void push(const DT& newElement);
	DT pop();
	void clear();

	bool isEmpty() const;
	bool isFull() const;

	void showStack() const;
private:
	int top,		// Index of the top of stack
		maxSize;	// Maximum number of elements in the stack
	DT* element;	// Array containing the stack's elements
};