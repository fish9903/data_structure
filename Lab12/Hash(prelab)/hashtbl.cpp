#include <iostream>
#include "hashtbl.h"

template < class DT, class KF >
HashTbl<DT, KF>::HashTbl(int initTableSize)
{
    tableSize = initTableSize;
    dataTable = new List<DT>[tableSize];
}

template < class DT, class KF >
HashTbl<DT, KF>::~HashTbl()
{
    delete[] dataTable;
}

template < class DT, class KF >
void HashTbl<DT, KF>::insert(const DT& newDataItem)
{
    if (isFull())
        return;

    int hash = newDataItem.hash(newDataItem.getKey());
    int index = hash % tableSize;

    if (dataTable[index].isFull())
        return;
    else
        dataTable[index].insert(newDataItem);
}

template < class DT, class KF >
bool HashTbl<DT, KF>::remove(KF searchKey)
{
    if (isEmpty())
        return false;

    for (int i = 0; i < tableSize; i++) {
        do {
            if (!dataTable[i].isEmpty()) {
                if (dataTable[i].getCursor().getKey() == searchKey) {
                    dataTable[i].remove();
                    return true;
                }
            }
        } while (dataTable[i].gotoPrior());
    }

    return false;
}

template < class DT, class KF >
bool HashTbl<DT, KF>::retrieve(KF searchKey, DT& dataItem)
{
    if (isEmpty())
        return false;

    for (int i = 0; i < tableSize; i++) {
        do {
            if (!dataTable[i].isEmpty()) {
                if (dataTable[i].getCursor().getKey() == searchKey) {
                    dataItem = dataTable[i].getCursor();
                    return true;
                }                    
            }            
        } while (dataTable[i].gotoPrior());
    }

    return false;
}

template < class DT, class KF >
void HashTbl<DT, KF>::clear()
{
    for (int i = 0; i < tableSize; i++)
        dataTable[i].clear();
}

template < class DT, class KF >
bool HashTbl<DT, KF>::isEmpty() const
{
    for (int i = 0; i < tableSize; i++) {
        if (!dataTable[i].isEmpty())
            return false;
    }

    return true;
}

template < class DT, class KF >
bool HashTbl<DT, KF>::isFull() const
{
    for (int i = 0; i < tableSize; i++) {
        if (!dataTable[i].isFull())
            return false;
    }

    return true;
}

template < class DT, class KF >
void HashTbl<DT, KF>::showStructure() const
{
    for (int i = 0; i < tableSize; i++)
    {
        cout << i << ": ";
        if (dataTable[i].isEmpty())
            cout << "_";
        else
        {
            dataTable[i].gotoBeginning();
            do
            {
                cout << dataTable[i].getCursor().getKey() << " ";
            } while (dataTable[i].gotoNext());
        }
        cout << endl << endl;
    }
}
