//--------------------------------------------------------------------
//
//  Laboratory C, In-lab Exercise 2                        sort.cpp
//
//  Implementation of a set of sorting routines
//
//--------------------------------------------------------------------

template < class DT >
void selectionSort(DT keyList[], int numKeys)

// Selection sort routine. Sorts the first numKeys keys in keyList
// into ascending order.

{
    int min;
    for (int i = 0; i < numKeys - 1; i++) {
        min = i;

        for (int j = i + 1; j < numKeys; j++) {
            if (keyList[j] < keyList[min])
                min = j;
        }

        if (i != min) {
            int temp = keyList[i];
            keyList[i] = keyList[min];
            keyList[min] = temp;
        }
    }
}

//--------------------------------------------------------------------

template < class DT >
void quickPartition(DT keyList[], int numKeys, int left, int right);

template < class DT >
void quickSort(DT keyList[], int numKeys)

// Quicksort routine. Sorts the first numKeys keys in keyList into
// ascending order.

{
    quickPartition(keyList, numKeys, 0, numKeys - 1);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template < class DT >
void quickPartition(DT keyList[], int numKeys,
    int left, int right)

    // Recursive partner of the quickSort routine. Partitions the array
    // entries between left and right into two subarrays. One subarray
    // contains the keys that are less than or equal to splitValue, and
    // the other contains the keys that are greater than splitValue.
    // Recursively sorts each of these subarrays.

{
    if (left >= right)
        return;

    int pivot;
    int low, high;

    pivot = keyList[left];
    low = left + 1;
    high = right;

    while (low <= high) {
        while (low <= right && keyList[low] <= pivot) {
            low++;
        }

        while (high > left && keyList[high] >= pivot) {
            high--;
        }

        if (low < high) {
            int temp = keyList[low];
            keyList[low] = keyList[high];
            keyList[high] = temp;
        }
        else {
            int temp = keyList[left];
            keyList[left] = keyList[high];
            keyList[high] = temp;
        }
    }

    quickPartition(keyList, 0, left, high - 1);
    quickPartition(keyList, 0, high + 1, right);
}

//--------------------------------------------------------------------

template < class DT >
void bubbleSort(DT keyList[], int numKeys)

{
    for (int i = numKeys - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (keyList[j] > keyList[j + 1]) {
                int temp = keyList[j];
                keyList[j] = keyList[j + 1];
                keyList[j + 1] = temp;
            }
        }
    }
}
