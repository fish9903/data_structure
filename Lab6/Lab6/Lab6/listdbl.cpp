// 2018112072 Á¶±¤È£
#include <iostream>
#include "listdbl.h"

using namespace std;

template < class DT >
ListNode<DT>::ListNode(const DT& data, ListNode* priorPtr, ListNode* nextPtr)
{
    dataItem = data;
    prior = priorPtr;
    next = nextPtr;
}

// Constructor
template < class DT >
List<DT>::List(int ignored)
{
    head = NULL;
    cursor = NULL;
}

// Destructor
template < class DT >
List<DT>::~List()
{
    clear();
    head = NULL;
    cursor = NULL;
}


//------------ List manipulation operations ------------------

// Insert after cursor
template < class DT >
void List<DT>::insert(const DT& newDataItem)
{
    if (isFull())
    {
        cout << "Insert Failed. The List is Full" << endl;
        return;
    }
    else if (isEmpty())
    {
        ListNode<DT>* n_Node = new ListNode<DT>(newDataItem, NULL, NULL);
        head = n_Node;
        cursor = head;
    }
    else
    {
        ListNode<DT>* n_Node = new ListNode<DT>(newDataItem, NULL, NULL);

        if (cursor->next == NULL)
        {
            n_Node->prior = cursor;
            cursor->next = n_Node;
            cursor = n_Node;
        }
        else if (cursor->prior == NULL)
        {
            n_Node->next = cursor;
            cursor->prior = n_Node;
            cursor = n_Node;
            head = n_Node;
        }
        else {
            n_Node->next = cursor->next;
            n_Node->prior = cursor;
            cursor->next->prior = n_Node;
            cursor->next = n_Node;
            cursor = n_Node;
        }
    }
}

// Remove data item
template < class DT >
void List<DT>::remove()
{
    if (isEmpty())
    {
        cout << "Remove Failed. The list is Empty" << endl;
        return;
    }
    else {
        ListNode<DT>* temp = cursor;

        if (cursor->next == NULL)
        {
            if (cursor->prior == NULL)
            {
                head = NULL;
                cursor = NULL;
                return;
            }
            cursor->prior->next = NULL;
            cursor = head;
        }
        else if (cursor->prior == NULL)
        {
            cursor->next->prior = NULL;
            cursor = cursor->next;
            head = cursor;
        }
        else {
            cursor->prior->next = cursor->next;
            cursor->next->prior = cursor->prior;
            cursor = cursor->next;
        }
        delete temp;
    }
}

// Replace data item
template < class DT >
void List<DT>::replace(const DT& newElement)
{
    if (isEmpty())
    {
        cout << "Replace Failed. The list is Empty" << endl;
        return;
    }
    else {
        cursor->dataItem = newElement;
    }
}

// Clear list
template < class DT >
void List<DT>::clear()
{
    if (isEmpty())
    {
        cout << "The List is already Empty" << endl;
        return;
    }
    else
    {
        ListNode<DT>* del_Node = head;
        ListNode<DT>* del_NextNode = head->next;

        while (del_NextNode != NULL)
        {
            //cout << del_Node->dataItem << " deleted" << endl;
            delete del_Node;

            del_Node = del_NextNode;
            del_NextNode = del_NextNode->next;
        }
        //cout << del_Node->dataItem << " deleted" << endl;
        delete del_Node;
        head = NULL;
        cursor = NULL;
        return;
    }
}


//------------ List status operations ------------------

// List is empty
template < class DT >
bool List<DT>::isEmpty() const
{
    if (head == NULL)
        return true;
    else
        return false;
}

// List is full
template < class DT >
bool List<DT>::isFull() const
{
    ListNode<DT>* n_Node;
    n_Node = new ListNode<DT>(0, NULL, NULL);
    if (n_Node == NULL)
        return true;
    else {
        delete n_Node;
        return false;
    }
}


//------------ List manipulation operations ------------------

// Go to beginning
template < class DT >
void List<DT>::gotoBeginning()
{
    if (isEmpty())
    {
        cout << "gotoBeginning Failed. The list is Empty" << endl;
        return;
    }
    else
    {
        cursor = head;
    }
}

// Go to end
template < class DT >
void List<DT>::gotoEnd()
{
    if (isEmpty())
    {
        cout << "gotoEnd Failed. The list is Empty" << endl;
        return;
    }
    else
    {
        while (cursor->next != NULL)
        {
            cursor = cursor->next;
        }
    }
}

// Go to next data item
template < class DT >
bool List<DT>::gotoNext()
{
    if (isEmpty())
    {
        cout << "gotoNext Failed. The list is Empty" << endl;
        return false;
    }
    else if (cursor->next == NULL)
    {
        cout << "gotoNext Failed. Cursor is End of list" << endl;
        return false;
    }
    else {
        cursor = cursor->next;
        return true;
    }
}

// Go to prior data item
template < class DT >
bool List<DT>::gotoPrior()
{
    if (isEmpty())
    {
        cout << "gotoNext Failed. The list is Empty" << endl;
        return false;
    }
    else if (cursor->prior == NULL)
    {
        cout << "gotoNext Failed. Cursor is first of list" << endl;
        return false;
    }
    else {
        cursor = cursor->prior;
        return true;
    }
}


template < class DT >
DT List<DT>::getCursor() const
{
    if (isEmpty())
    {
        cout << "Get Cursor Failed. The List is empty" << endl;
        return NULL;
    }
    return cursor->dataItem;
}


//-----------------------------------------------------------

template < class DT >
void List<DT>::showStructure() const
{
    if (isEmpty())
    {
        cout << "The List is empty" << endl;
        return;
    }

    ListNode<DT>* temp = head;
    while (temp != NULL)
    {
        if (temp == cursor)
        {
            cout << "[" << temp->dataItem << "] ";
        }
        else
        {
            cout << temp->dataItem << " ";
        }
        temp = temp->next;
    }
    cout << endl;
}