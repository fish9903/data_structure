//--------------------------------------------------------------------
//
//  Laboratory B                                         testb.cpp
//
//  Test program for the operations in the Heap ADT
//
//--------------------------------------------------------------------

#include <iostream>
#include <string>

#include "heap.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the heap data item class
//

class Person
{
  public:
	  Person() {
	  }
      bool operator==(Person& p) {
          if (name == p.getName())
              return true;
          else
              return false;
      }

    void setPty ( int newPty ) { priority = newPty; }   // Set the priority
    void setName(string newName) { name = newName; }
    void setLevel(int l) { level = l; }
    void setSuperior_index(int index) { superior_index = index; }
    void setSub_index(int index) { sub_index = index; }

    int pty () const { return priority; }     // Returns the priority
    string getName() const { return name;  }
    int getLevel() const{ return level; }
    int getSuperior_index() { 
        if (level != 0)
            return superior_index;
        else
            return 0;
    }
    int getSub_index() { return sub_index; }
    std::vector<string>* getArray() { return &subArray; }

  private:
    string name;
    int priority;                // Priority for the data item
    int level;                   // 0:CEO, ... ,
    int superior_index;          // superior가 있는 위치
    int sub_index;                // subordinate가 시작되는 위치   
    std::vector<string> subArray;
};

//--------------------------------------------------------------------

void main()
{
    Heap<Person> testHeap(100);  // Test heap

    Person p;       // Heap data item
    string BossName;                    // 
    string targetName;
    string cmd;                        // Input command

    bool isFirst = true;

    do
    {
        cout << endl << "input: ";

        if (isFirst) {
            cin >> BossName;
            isFirst = false;

            p.setName(BossName);
            p.setLevel(0);
            testHeap.insert(p);
        }
        else {      
            cin >> cmd;

            if (cmd == "fire") {
                cin >> targetName;
                testHeap.fire(targetName);
            }
            else if (cmd == "print") {
                testHeap.print();
            }
            else { // hire
                BossName = cmd;
                cin >> cmd >> targetName;

                p.setName(targetName);
                testHeap.hire(BossName, p);
            }
        }
    }
    while (true);

}

