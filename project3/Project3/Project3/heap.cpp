//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.cpp
//
//  Actual implementation of class in the Heap ADT
//--------------------------------------------------------------------

#include "heap.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//--------------------------------------------------------------------


template<class DT>
Heap<DT>::Heap(int maxNumber)
{
    maxSize = maxNumber;
    size = 0;
    dataItems = new DT[maxNumber];
}

template < class DT >
Heap<DT>::~Heap()
{
    delete[] dataItems;
}

//--------------------------------------------------------------------

template < class DT >
void Heap<DT>::insert(const DT& newElement)
{
    if (isFull())
    {
        cout << "Heap is Full" << endl;
        return;
    }
    
    dataItems[size] = newElement;
    size++;
    
    int child = size - 1;
    int parent = (size - 2) / 2;

    while (child > 0) {
        if (dataItems[parent].pty() < dataItems[child].pty()) {
            DT temp = dataItems[parent];
            dataItems[parent] = dataItems[child];
            dataItems[child] = temp;
        }
        child = parent;
        parent = (parent - 1) / 2;
    }
}

template<class DT>
void Heap<DT>::hire(string boss, DT& subordinate)
{
    if (isFull()) {
        cout << "Tree is Full" << endl;
        return;
    }

    bool flag = false;

    for (int i = 0; i < size; i++) {
        if (dataItems[i].getName() == boss) {
            flag = true;

            subordinate.setLevel(dataItems[i].getLevel() + 1);
            dataItems[i].getArray()->push_back(subordinate.getName()); // 넣기

            if (i == 0) {
                int index = dataItems[0].getArray()->size();

                size++;
                for (int j = size - 1; j > index; j--) {
                    dataItems[j] = dataItems[j - 1];
                }
                dataItems[index] = subordinate;
            }
            else {
                size++;

                // 추가하려는 원소의 같은 레벨 원소 개수 구해서 추가할 index 구하지
                int count = 0;
                int start = -1;
                for (int j = 0; j < size - 1; j++) {
                    if (dataItems[j].getLevel() == dataItems[i].getLevel() + 1) {
                        count++;
                        if (start == -1)
                            start = j;
                    }
                }
                // 처음 추가하는 원소일 때
                if (start == -1) {
                    start = size - 1;
                }

                int index = start + count;

                for (int j = size - 1; j > index; j--) {
                    dataItems[j] = dataItems[j - 1];
                }
                dataItems[index] = subordinate;
            }
        }
    }

    setPty();

    if(!flag)
        cout << "There is no such person" << endl;
}

template<class DT>
void Heap<DT>::fire(string target)
{
    for (int i = 0; i < size; i++) {
        if (dataItems[i].getName() == target) {
            // i 찾아서 삭제
            int del_parent = -1;
            for (int j = i - 1; j >= 0; j--) {
                for (std::vector<string>::iterator iter = dataItems[j].getArray()->begin(); iter < dataItems[j].getArray()->end(); iter++) {
                    if (*iter == target) {
                        dataItems[j].getArray()->erase(iter);
                        del_parent = j;
                        break;
                    }
                }
            }

            // sub = 0 일 때
            if (dataItems[i].getArray()->size() == 0) {
                for (int j = i; j < size - 1; j++) {
                    dataItems[j] = dataItems[j + 1];
                }
                size--;
            }
            else {
                // i의 가장 먼저 들어온 sub인덱스 구하기
                int index = firstSub(i);
                int temp_i;
                // 트리 모양, level 바꾸기
                while (dataItems[index].getArray()->size() != 0) {
                    dataItems[i].setName(dataItems[index].getName());
                    dataItems[i].getArray()->erase(dataItems[i].getArray()->begin());
                    
                    temp_i = i;
                    i = index;
                    index = firstSub(index);

                    dataItems[temp_i].getArray()->insert(dataItems[temp_i].getArray()->begin(), dataItems[index].getName());
                }
                dataItems[i].setName(dataItems[index].getName());
                dataItems[i].getArray()->erase(dataItems[i].getArray()->begin());

                if(del_parent != -1)
                    dataItems[del_parent].getArray()->insert(dataItems[del_parent].getArray()->begin(), dataItems[firstSub(del_parent)].getName());

                for (int j = index; j < size - 1; j++) {
                    dataItems[j] = dataItems[j + 1];
                }

                size--;
            }
            break;
        }
    }
    setPty();
}

template<class DT>
void Heap<DT>::setPty()
{
    for (int i = 0; i < size; i++) {
        dataItems[i].setPty(100 - i - 1);
    }
}

template < class DT >
void Heap<DT>::clear()
{
    size = 0;
}

//--------------------------------------------------------------------

template < class DT >
bool Heap<DT>::isEmpty() const
{
    if (size == 0)
        return true;
    else
        return false;
}

template < class DT >
bool Heap<DT>::isFull() const
{
    if (size == maxSize)
        return true;
    else
        return false;
}

template<class DT>
int Heap<DT>::firstSub(int start) const
{
    int temp = 0;
    int start1 = 0;
    int start2 = 0;
    for (int j = 0; j < size; j++) {
        if (dataItems[j].getLevel() == dataItems[start].getLevel()) {
            start1 = j;
            break;
        }
    }
    for (int j = 0; j < size; j++) {
        if (dataItems[j].getLevel() == dataItems[start].getLevel() + 1) {
            start2 = j;
            break;
        }
    }

    for (int j = start1; j < start; j++) {
        temp += dataItems[j].getArray()->size();
    }
    temp += start2;

    if (temp == 0)
        return -1;
    else
        return temp;
}

//--------------------------------------------------------------------

template<class DT>
void Heap<DT>::print() const
{
    if (isEmpty()) {
        cout << "Empty" << endl;
        return;
    }
    for (int j = 0; j < size; j++)
        cout << dataItems[j].getName() << "(" << dataItems[j].pty() << ")\t";
    cout << endl;

    cout << dataItems[0].getName() << endl;
    for (int i = 0; i < dataItems[0].getArray()->size(); i++)
        printSub(i + 1);

    for (int i = 0; i < 60; i++)
        cout << "-";
    cout << endl;
}

template<class DT>
void Heap<DT>::printSub(int start) const
{
    for (int j = 0; j < dataItems[start].getLevel(); j++)
        cout << "+";
    cout << dataItems[start].getName() << endl;
    
    if (dataItems[start].getArray()->size() != 0) {
        int temp = firstSub(start);

        
        int s = dataItems[start].getArray()->size();
        for (int i = 0; i < s; i++) {
            printSub(temp++);
        }
    }
}