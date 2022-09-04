//--------------------------------------------------------------------
//
//  Laboratory 10                                         listrec.cs
//
//  (Shell) Partial linked list implementation of the List ADT with
//  additional recursive linked list functions
//
//--------------------------------------------------------------------

#include <iostream>
#include "listrec.h"

using namespace std;

//--------------------------------------------------------------------
//
// Insert your singly linked list implementations (from Laboratory 7)
// of the following functions:
//
//   - The ListNode class constructor
//
//   - The List class constructor, destructor, insert(), clear(), and
//     showstructure() functions. You may also need to add empty()
//     full(), and others.
//
//--------------------------------------------------------------------
// 2018112072 ¡∂±§»£
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

template<class DT>
List<DT>::~List()
{
    clear();
    delete head;
    delete cursor;
}

//--------------------------------------------------------------------

template<class DT>
bool isEmpty(const List<DT>& list)
{
    if (list.getLength() == 0)
        return true;
    else
        return false;
}

template<class DT>
void List<DT>::insert(const DT& newData)
{
    // full »Æ¿Œ
    ListNode<DT>* n_Node;
    n_Node = new ListNode<DT>(0, NULL);
    if (n_Node == NULL) {
        cout << "The List is Full" << endl;
        return;
    }        
    else {
        delete n_Node;
    }
    /*if (isFull())
    {
        cout << "The List is Full" << endl;
        return;
    }
    else */if (isEmpty(*this))
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

template<class DT>
void List<DT>::clear()
{
    if (isEmpty(*this))
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

template<class DT>
void List<DT>::showStructure() const
{
    if (isEmpty(*this))
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

//--------------------------------------------------------------------
//
// Recursively implemented linked list functions used in the Prelab
// Exercise
//
//--------------------------------------------------------------------

template < class DT >
void List<DT>:: write () const

// Outputs the data in a list from beginning to end. Assumes that
// objects of type DT can be output to the cout stream.

{
    cout << "List : ";
    writeSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: writeSub ( ListNode<DT> *p ) const

// Recursive partner of the write() function. Processes the sublist
// that begins with the node pointed to by p.

{
    if ( p != 0 )
    {
       cout << p->dataItem;      // Output data
       writeSub(p->next);    // Continue with next node
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: insertEnd ( const DT &newDataItem )

// Inserts newDataItem at the end of a list. Moves the cursor to
// newDataItem.

{
    insertEndSub(head,newDataItem);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: insertEndSub ( ListNode<DT> *&p,
                               const DT &newDataItem )

// Recursive partner of the insertEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if ( p != 0 )
       insertEndSub(p->next,newDataItem);    // Continue searching for
    else                                     // end of list
    {
       p = new ListNode<DT>(newDataItem,0);  // Insert new node
       cursor = p;                           // Move cursor
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: writeMirror () const

// Outputs the data in a list from beginning to end and back
// again. Assumes that objects of type DT can be output to the cout
// stream.

{
    cout << "Mirror : ";
    writeMirrorSub(head);
    cout << endl;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: writeMirrorSub ( ListNode<DT> *p ) const

// Recursive partner of the writeMirror() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if ( p != 0 )
    {
       cout << p->dataItem;           // Output data (forward)
       writeMirrorSub(p->next);   // Continue with next node
       cout << p->dataItem;           // Output data (backward)
    }
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: reverse ()

// Reverses the order of the data items in a list.

{
    reverseSub(0,head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: reverseSub ( ListNode<DT> *p, ListNode<DT> *nextP )

// Recursive partner of the reverse() function. Processes the sublist
// that begins with the node pointed to by nextP.

{
    if ( nextP != 0 )
    {
       reverseSub(nextP,nextP->next);   // Continue with next node
       nextP->next = p;                 // Reverse link
    }
    else
       head = p;                        // Move head to end of list
}

//--------------------------------------------------------------------

template < class DT >
void List<DT>:: deleteEnd ()

// Deletes the data at the end of a list. Moves the cursor to the
// beginning of the list.

{
    deleteEndSub(head);
    cursor = head;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void List<DT>:: deleteEndSub ( ListNode<DT> *&p )

// Recursive partner of the deleteEnd() function. Processes the
// sublist that begins with the node pointed to by p.

{
    if ( p->next != 0 )
       deleteEndSub(p->next);   // Continue looking for the last node
    else
    {
       delete p;                // Delete node
       p = 0;                   // Set p (link or head) to null
    }
}

//--------------------------------------------------------------------

template < class DT >
int List<DT>:: getLength () const

// Returns the number of data items in a list.

{
    return getLengthSub(head);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
int List<DT>:: getLengthSub ( ListNode<DT> *p ) const

// Recursive partner of the length() function. Processes the sublist
// that begins with the node pointed to by p.

{
    int result;   // Result returned

    if ( p == 0 )
       result = 0;                            // End of list reached
    else
       result = (getLengthSub(p->next) + 1 );   // Number of nodes after
                                              // this one + 1
    return result;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT >
void List<DT>::cRemove()
{
    if (getLength() == 0) {
        cout << "The List is Empty" << endl;
        return;
    }
    cRemoveSub(head);
    cursor = head;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
template < class DT >
void List<DT>::cRemoveSub(ListNode<DT> *p)
{
    if (p == NULL) {
        return;
    }
   else if ('c' == p->dataItem) {
        ListNode<DT>* del_Node = p;
        if (p == head) {
            head = p->next;
            p = head;
            delete del_Node;
            cRemoveSub(p);
        }
        else {
            ListNode<DT>* del_before = head;
            while (del_before->next != p) {
                del_before = del_before->next;

            }
            del_before->next = p->next;
            p = del_before;
            //p->dataItem = 'x';
            delete del_Node;
            cRemoveSub(p);
        }
   }
   else {
	   cRemoveSub(p->next);
   }
}