#pragma once
//--------------------------------------------------------------------
//
//                                                         phonebook.h
//													  2018112072_Á¶±¤È£
//
//--------------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int defMaxListSize = 100;   // Default maximum list size

class Person
{
private:
	string name;
	string tel;
	string birth;
	int birth_month;
	static string Month_Arr[12];
	
public:
	Person(string name = "", string tel = "", string birth = "", int birth_month = 0)
		:name(name), tel(tel), birth(birth), birth_month(birth_month)
	{}

	friend class List;
};

class List
{
public:

	// Constructor
	List(int maxNumber = defMaxListSize);

	// Destructor
	~List();

	void Read(ifstream& fin);
	void add(ifstream& fin);
	void Remove(ifstream& fin);
	void Write();
	void Month(ifstream& fin);
	void Show(ifstream& fin);
	bool isEmpty();
	bool isFull();
	
private:
	// Data members
	int maxSize,
		size,             // Actual number of data item in the list
		cursor;           // Cursor array index
	Person* dataItems;  // Array containing the list data item
};

