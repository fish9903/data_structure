
#include "listlnk.h"
#include <iostream>

using namespace std;

template<class DT>
ListNode<DT>::ListNode(const DT& nodeData, ListNode* nextPtr)
{
    dataItem = nodeData;
    next = nextPtr;
}


template<class DT>
List<DT>::List(int ignored)
{
    head = NULL;
    cursor = NULL;
}

//------------------------------------------------

template<class DT>
List<DT>::~List()
{
    clear();
    delete head;
    delete cursor;
}

//------------------------------------------------


template<class DT>
void List<DT>::insert(const DT& newData)
{
    if (isFull())
    {
        cout << "The List is Full" << endl;
        return;
    }
    else if (isEmpty())
    {
        ListNode<DT>* n_Node = new ListNode<DT>(newData, NULL);
        head = n_Node;
        cursor = head;
    }
    else
    {
        ListNode<DT>* n_Node = new ListNode<DT>(newData, cursor->next);
        cursor->next = n_Node;
        cursor = n_Node;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::remove()
{
    if (isEmpty())
    {
        cout << "Remove Failed. The List is Empty" << endl;
        return;
    }
    else
    {
        ListNode<DT>* del_Node = cursor;
        ListNode<DT>* del_before = head;

        while (del_before->next != cursor)
        {
            if (cursor == head)
            {
                head = cursor->next;
                cursor = cursor->next;
                delete del_Node;
                return;
            }
            else
            {
                del_before = del_before->next;
            }
        }
        del_before->next = del_Node->next;

        if (cursor->next == NULL)
            cursor = head;
        else
            cursor = cursor->next;

        delete del_Node;
    }
}


//------------------------------------------------


template<class DT>
void List<DT>::replace(const DT& newData)
{
    if (isEmpty())
    {
        cout << "Replace Failed. The List is Empty" << endl;
        return;
    }
    else
    {
        cursor->dataItem = newData;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::clear()
{
    if (isEmpty())
    {
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

//------------------------------------------------


template<class DT>
bool List<DT>::isEmpty() const
{
    if (head == NULL)
        return true;
    else
        return false;
}

//------------------------------------------------


template<class DT>
bool List<DT>::isFull() const
{
    ListNode<DT>* n_Node;
    DT t;
    n_Node = new ListNode<DT>(t, NULL);
    if (n_Node == NULL)
        return true;
    else {
        delete n_Node;
        return false;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoBeginning()
{
    if (isEmpty())
    {
        cout << "Go to Beginning Failed. The List is Empty" << endl;
        return;
    }
    else
    {
        cursor = head;
    }
}

//------------------------------------------------


template<class DT>
void List<DT>::gotoEnd()
{
    if (isEmpty())
    {
        cout << "Go to End Failed. The List is Empty" << endl;
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

//------------------------------------------------


template<class DT>
bool List<DT>::gotoNext()
{
    if (isEmpty() || cursor->next == NULL)
    {
        return false;
    }
    else
    {
        cursor = cursor->next;
    }
}

//------------------------------------------------


template<class DT>
bool List<DT>::gotoPrior()
{
    if (isEmpty() || cursor == head)
    {
        return false;
    }
    else
    {
        ListNode<DT>* temp = head;
        while (temp->next != cursor)
        {
            temp = temp->next;
        }
        cursor = temp;
    }
}

//------------------------------------------------


template<class DT>
DT List<DT>::getCursor() const
{
    if (!isEmpty())
        return cursor->dataItem;
}

template<class DT>
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