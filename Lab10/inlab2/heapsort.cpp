//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 2                     heapsort.cs
//
//  (Shell) heapSort() function
//
//--------------------------------------------------------------------

template < class DT >
void moveDown ( DT dataItem [], int root, int size )

// Restores the binary tree that is rooted at root to a heap by moving
// dataItem[root] downward until the tree satisfies the heap property.
// Parameter size is the number of data items in the array.

{
    int maxChild, rightChild, leftChild;

    leftChild = 2 * root + 1;
    rightChild = 2 * root + 2;

    if (leftChild <= (size - 1)) {
        if (leftChild == (size - 1))
            maxChild = leftChild;
        else {
            if (dataItem[leftChild].pty() <= dataItem[rightChild].pty())
                maxChild = rightChild;
            else
                maxChild = leftChild;
        }
        if (dataItem[root].pty() < dataItem[maxChild].pty()) {
            DT temp = dataItem[maxChild];
            dataItem[maxChild] = dataItem[root];
            dataItem[root] = temp;
            moveDown(dataItem, maxChild, size);
        }
    }
}

//--------------------------------------------------------------------

template < class DT >
void heapSort ( DT dataItems [], int size )

// Heap sort routine. Sorts the data items in the array in ascending
// order based on priority.

{
    DT temp;   // Temporary storage
    int j;     // Loop counter

    // Build successively larger heaps within the array until the
    // entire array is a heap.

    for ( j = (size-1)/2 ; j >= 0 ; j-- )
        moveDown(dataItems,j,size);

    // Swap the root data item from each successively smaller heap with
    // the last unsorted data item in the array. Restore the heap after
    // each exchange.

    for ( j = size-1 ; j > 0 ; j-- )
    {
        temp = dataItems[j];
        dataItems[j] = dataItems[0];
        dataItems[0] = temp;
        moveDown(dataItems,0,j);
    }
}

