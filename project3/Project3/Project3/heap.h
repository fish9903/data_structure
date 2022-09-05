//--------------------------------------------------------------------
//
//  Laboratory 13                                             heap.h
//
//  Class declaration for the array implementation of the Heap ADT
//
//--------------------------------------------------------------------
#include <string>
using namespace std;

const int defMaxHeapSize = 10;    // Default maximum heap size

template < class DT >
class Heap
{
  public:

    // Constructor
    Heap ( int maxNumber = defMaxHeapSize );

    // Destructor
    ~Heap ();

    // Heap manipulation operations
    void insert(const DT& newElement);    // Insert element

    void hire(string boss, DT& subordinate);
    void fire(string target);
    void setPty();                          // priority 정리(설정)

    void clear ();                          // Clear heap

    // Heap status operations
    bool isEmpty () const;                  // Heap is empty
    bool isFull () const;                   // Heap is full
    int firstSub(int start) const ;                    // i 기준 가장 먼저 들어온 sub index반환

    // Output the heap structure -- used in testing/debugging
    void print() const;

  private:

    // Recursive partner of the showStructure() function
    void printSub(int start) const; // jump: parent's number of subordinate

    // Data members
    int maxSize,   // Maximum number of elements in the heap
        size;      // Actual number of elements in the heap
    DT* dataItems; // Array containing the heap elements
};
