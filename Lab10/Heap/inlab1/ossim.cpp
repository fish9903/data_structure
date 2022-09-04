//--------------------------------------------------------------------
//
//  Laboratory B, In-lab Exercise 1                       ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <cstdlib>
#include "ptyqueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int priority,              // Task's priority
        arrived;               // Time when task was enqueued

    void setPty(int newPty)
        { priority = newPty; }   // Set the priority

    int pty () const
        { return priority; }   // Returns the priority
};

//--------------------------------------------------------------------

void main ()
{
    PtyQueue<TaskData> taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals;             // Number of new tasks arriving

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        // Dequeue the first task in the queue (if any).



        // Determine the number of new tasks and add them to
        // the queue.



    }

    system("pause");
}
