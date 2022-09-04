//--------------------------------------------------------------------
//	
//                                                       listarr.cpp
//
//  SOLUTION: Array implementation of the List ADT
//
//--------------------------------------------------------------------
// 2018112072_Á¶±¤È£
#include "listarr.h"

using namespace std;

//--------------------------------------------------------------------

List::List(int maxNumber)

// Creates an empty list. Allocates enough memory for maxNumber
// data items (defaults to defMaxListSize).

	: maxSize(maxNumber),
	size(0),
	cursor(-1)
{
	// pre-lab
	dataItems = new DataType[maxSize];
}

//--------------------------------------------------------------------

List:: ~List()
// Frees the memory used by a list.

{
	// pre-lab
	if(dataItems != nullptr)
		delete[] dataItems;
}

//--------------------------------------------------------------------

void List::insert(const DataType& newDataItem)
throw (logic_error)

// Inserts newDataItem after the cursor. If the list is empty, then
// newDataItem is inserted as the first (and only) data items in the
// list. In either case, moves the cursor to newDataItem.

{
	// pre-lab
	if (isFull()) {
		cout << "List is Full" << endl;
		return;
	}
	else if (isEmpty()) {
		dataItems[0] = newDataItem;

		size++;
		cursor = 0;
		return;
	}
	else if(size < maxSize) {
		// if cursor is last index
		if (cursor + 1 == size) {
			dataItems[cursor + 1] = newDataItem;

			size++;
			cursor = size - 1;
			return;
		}
		
		for (int i = size - 1; i > cursor; i--) {
			dataItems[i + 1] = dataItems[i];
		}
		dataItems[cursor + 1] = newDataItem;

		size++;
		cursor++;
		return;
	}
}

//--------------------------------------------------------------------

void List::remove() throw (logic_error)

// Removes the data items  marked by the cursor from a list. Moves the
// cursor to the next data item item in the list. Assumes that the
// first list data items "follows" the last list data item.
{
	// pre-lab
	if (isEmpty()) {
		cout << "List is Empty" << endl;
		return;
	}
	else if (size <= maxSize) {
		for (int i = cursor; i < size; i++) {
			dataItems[i] = dataItems[i + 1];
		}
		size--;
	}

	if (cursor == size)
		cursor = 0;

}

//--------------------------------------------------------------------

void List::replace(const DataType& newDataItem)
throw (logic_error)

// Replaces the item marked by the cursor with newDataItem and
// leaves the cursor at newDataItem.
{
	// Requires that the list is not empty
	// pre-lab
	if (isEmpty())
		return;
	else {
		dataItems[cursor] = newDataItem;
	}
}
//--------------------------------------------------------------------

void List::clear()
// Removes all the data items from a list.
{
	// pre-lab
	size = 0;
	cursor = -1;
}

//--------------------------------------------------------------------

bool List::isEmpty() const
// Returns 1 if a list is empty. Otherwise, returns 0.
{
	// pre-lab
	if (size == 0)
		return true;
	else 
		return false;
}

//--------------------------------------------------------------------

bool List::isFull() const
// Returns 1 if a list is full. Otherwise, returns 0.
{
	// pre-lab
	if (size == maxSize)
		return true;
	else if (size < maxSize)
		return false;
}

//--------------------------------------------------------------------

bool List::gotoBeginning() throw (logic_error)
// Moves the cursor to the beginning of the list.
{
	// pre-lab
	if (isEmpty()) return false;
	else {
		cursor = 0;
		return true;
	}
}

//--------------------------------------------------------------------

bool List::gotoEnd() throw (logic_error)

// Moves the cursor to the end of the list.

{
	// pre-lab
	if (isEmpty()) return false;
	else {
		cursor = size - 1; 
		return true;
	}
}

//--------------------------------------------------------------------

bool List::gotoNext() throw (logic_error)

// If the cursor is not at the end of a list, then moves the
// cursor to the next item in the list and returns true. Otherwise,
// returns false.
{
	// pre-lab
	if (cursor == size - 1)
		return false;
	else { 
		cursor++; 
		return true;
	}
}

//--------------------------------------------------------------------

bool List::gotoPrior() throw (logic_error)

// If the cursor is not at the beginning of a list, then moves the
// cursor to the preceeding item in the list and returns true.
// Otherwise, returns false.

{
	// pre-lab
	if (cursor == 0)
		return false;
	else {
		cursor--;
		return true;
	}
}

//--------------------------------------------------------------------

DataType List::getCursor() const throw (logic_error)
// Returns the item marked by the cursor.

{
	// pre-lab
	return dataItems[cursor];
}

//--------------------------------------------------------------------

void List::showStructure() const
// Outputs the data items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing/debugging
// purposes only.

{
     // pre-lab

	cout << "size = " << size << "\tcursor = " << cursor << endl;
	for (int i = 0; i < maxSize; i++) {
		cout << "[ " << i << " ]\t";
	}
	cout << endl;


	if (size != 0) {
		for (int i = 0; i < size; i++)
			cout << "  " << dataItems[i] << "\t";
	}
	cout << endl;
}

//--------------------------------------------------------------------

//in-lab
void List::moveToNth(int n) throw (logic_error)
{
	// in-lab 2
	int temp;
	temp = dataItems[cursor];

	if (cursor < n){
		for (int i = 0; i < n; i++) {
			dataItems[i] = dataItems[i + 1];
		}
	}
	else {
		for (int i = cursor; i > n; i--) {
			dataItems[i] = dataItems[i - 1];
		}
	}

	dataItems[n] = temp;
	cursor = n;
}

bool List::find(const DataType& searchDataItem) throw(logic_error)
{
	// in-lab 3
	for (int i = cursor; i < size; i++) {
		if (dataItems[i] == searchDataItem)
		{
			cursor = i;
			return true;
		}
	}

	cursor = size - 1;
	return false;
}