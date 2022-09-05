//--------------------------------------------------------------------
//
//  Laboratory 14                                          wtgraph.cpp
//
//  Implementation of the Weighted Graph ADT
//
//--------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include "wtgraph.h"
#include <iostream>
#include <string>

//--------------------------------------------------------------------

WtGraph::WtGraph(int maxNumber)
{
	maxSize = maxNumber;
	size = 0;
	vertexList = new Vertex[maxSize];

	adjMatrix = new int[maxSize * maxSize];
	pathMatrix = new int[maxSize * maxSize];

	for (int i = 0; i < maxSize * maxSize; i++) {
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt;
	}
}

WtGraph::~WtGraph()
{
	delete[] vertexList;
	delete[] adjMatrix;
}

//--------------------------------------------------------------------

int WtGraph::getIndex(char* v)
{
	for (int i = 0; i < maxSize; i++) {
		if (strcmp(vertexList[i].label, v) == 0)
			return i;
	}
		
	return -1;
}

int WtGraph::getEdge(int row, int col)
{
	return adjMatrix[row * size + col];
}

void WtGraph::setEdge(int row, int col, int wt) 
{
	adjMatrix[row * size + col] = wt;
}

//--------------------------------------------------------------------

void WtGraph::insertVertex(Vertex newVertex)
{
	if (isFull()) {
		cout << "Graph is Full" << endl;
		return;
	}

	vertexList[size] = newVertex;
	
	size++;

	// 2차원 배열로 조작 후 1차원 배열(adjMatrix)에 할당
	int** temp;
	temp = new int* [size];
	for (int i = 0; i < size; i++)
		temp[i] = new int[size];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == size - 1 || j == size - 1)
				temp[i][j] = infiniteEdgeWt;
			else
				temp[i][j] = adjMatrix[i * (size - 1) + j];
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			adjMatrix[i * size + j] = temp[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		delete[] temp[i];
	}
	delete[] temp;

	for (int i = 0; i < maxSize * maxSize; i++)
		pathMatrix[i] = adjMatrix[i];
	computePaths();
}

void WtGraph::insertEdge(char* v1, char* v2, int wt)
{
	Vertex temp;
	if (retrieveVertex(v1, temp) && retrieveVertex(v2, temp)) {
		int row;
		int col;

		row = getIndex(v1);
		col = getIndex(v2);
		adjMatrix[row * size + col] = wt;

		row = getIndex(v2);
		col = getIndex(v1);
		adjMatrix[row * size + col] = wt;

		for (int i = 0; i < maxSize * maxSize; i++)
			pathMatrix[i] = adjMatrix[i];
		computePaths();
	}	
	else {
		cout << "There is no such vertex" << endl;
	}
}

//--------------------------------------------------------------------

bool WtGraph::retrieveVertex(char* v, Vertex& vData)
{
	for (int i = 0; i < maxSize; i++) {
		if (strcmp(vertexList[i].label, v) == 0) {
			strcpy(vData.label, v);
			return true;
		}			
	}

	return false;
}

bool WtGraph::getEdgeWeight(char* v1, char* v2, int& wt)
{
	Vertex temp;
	if (retrieveVertex(v1, temp) && retrieveVertex(v2, temp)) {
		int row;
		int col;

		row = getIndex(v1);
		col = getIndex(v2);
		
		if (adjMatrix[row * size + col] == 0)
			return false;
		else {
			wt = adjMatrix[row * size + col];
			return true;
		}		
	}
	else {
		cout << "There is no such vertex" << endl;
		return false;
	}
}

//--------------------------------------------------------------------

void WtGraph::removeVertex(char* v)
{
	int del;

	Vertex temp;
	if (retrieveVertex(v, temp)) {
		for (int i = 0; i < size; i++) {
			if (strcmp(vertexList[i].label, v) == 0) {
				del = i;
			}				
		}

		// 2차원 배열로 조작 후 1차원 배열(adjMatrix)에 할당
		int** temp;
		temp = new int* [size];
		for (int i = 0; i < size; i++)
			temp[i] = new int[size];

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				temp[i][j] = adjMatrix[i * (size) + j];
			}
		}
	
		size--;

		int index = 0;
		for (int i = 0; i < size + 1; i++) {
			for (int j = 0; j < size + 1; j++) {
				if(i != del && j != del)
					adjMatrix[index++] = temp[i][j];
			}
		}

		for (int i = 0; i < size + 1; i++) {
			delete[] temp[i];
		}
		delete[] temp;

		for (int i = 0; i < maxSize * maxSize; i++)
			pathMatrix[i] = adjMatrix[i];
		computePaths();
	}
	else {
		cout << "There is no such vertex" << endl;
		return;
	}
}

void WtGraph::removeEdge(char* v1, char* v2)
{
	Vertex temp;
	if (retrieveVertex(v1, temp) && retrieveVertex(v2, temp)) {
		int row;
		int col;

		row = getIndex(v1);
		col = getIndex(v2);

		adjMatrix[row * size + col] = infiniteEdgeWt;

		row = getIndex(v2);
		col = getIndex(v1);

		adjMatrix[row * size + col] = infiniteEdgeWt;

		for (int i = 0; i < maxSize * maxSize; i++)
			pathMatrix[i] = adjMatrix[i];
		computePaths();
	}
	else {
		cout << "There is no such vertex" << endl;
		return;
	}
}

//--------------------------------------------------------------------

void WtGraph::clear()
{
	for (int i = 0; i < maxSize * maxSize; i++) {
		adjMatrix[i] = infiniteEdgeWt;
		pathMatrix[i] = infiniteEdgeWt;
	}

	size = 0;
}

bool WtGraph::isEmpty() const
{
	if (size == 0)
		return true;
	else
		return false;
}

bool WtGraph::isFull() const
{
	if (size == maxSize)
		return true;
	else 
		return false;
}

//--------------------------------------------------------------------

void WtGraph::showStructure()

// Outputs a graph's vertex list (w/ color) and adjacency matrix.
// This operation is intended for testing/debugging purposes only.

{
	int wt,         // Edge weight
		row, col;   // Loop counters

	if (size == 0)
		cout << "Empty graph" << endl;
	else
	{
		cout << endl << "Vertex list : " << endl;
		for (row = 0; row < size; row++)
			cout << row << '\t' << vertexList[row].label << endl;

		cout << endl << "Edge matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = getEdge(row, col);
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}

		cout << endl << "Path matrix : " << endl << '\t';
		for (col = 0; col < size; col++)
			cout << col << '\t';
		cout << endl;
		for (row = 0; row < size; row++)
		{
			cout << row << '\t';
			for (col = 0; col < size; col++)
			{
				wt = getPath(row, col);
				if (wt == infiniteEdgeWt)
					cout << "- \t";
				else
					cout << wt << '\t';
			}
			cout << endl;
		}
	}
}

//--------------------------------------------------------------------


 int WtGraph::getPath(int row, int col)
 {
	 return pathMatrix[row * size + col];
 }

 void WtGraph::setPath(int row, int col, int wt) {
	 pathMatrix[row * size + col] = wt;
 }

 void WtGraph::computePaths() 
 {
	 for (int m = 0; m < size; m++) {
		 for (int j = 0; j < size; j++) {
			 for (int k = 0; k < size; k++) {
				 if (getPath(j, m) != infiniteEdgeWt && getPath(m, k) != infiniteEdgeWt && j != k) {
					 if (getPath(j, k) > getPath(j, m) + getPath(m, k)) {
						 setPath(j, k, getPath(j, m) + getPath(m, k));
					 }
				 }
			 }
		 }
	 }		 
 }