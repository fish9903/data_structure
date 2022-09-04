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

    srand(500);
    int max_0 = 1;
    int max_1 = 1;
    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        cout << "Current minute = " << minute << endl;
        // Dequeue the first task in the queue (if any).
        if (!taskPQ.isEmpty()) {
            task = taskPQ.dequeue();
            cout << "Task Dequeued" << endl;
            cout << "This task's priority: " << task.priority << endl;
            cout << "This task was arrived at " << task.arrived;
            cout << ", and waited for " << minute - task.arrived << " minutes." << endl;
            
            if (task.priority == 1) {
                if (max_1 < (minute - task.arrived))
                    max_1 = minute - task.arrived;
            }
            else if (task.priority == 0) {
                if (max_0 < (minute - task.arrived))
                    max_0 = minute - task.arrived;
            }
        }

        // Determine the number of new tasks and add them to
        // the queue.
        int k = rand() % 4;
        if (k == 1) {
            int n = rand() % 2;
            task.priority = n;
            task.arrived = minute;
            taskPQ.enqueue(task);

            cout << "Adding 1 task\n" << endl;
            taskPQ.showStructure();
            cout << endl;
        }
        else if (k == 2) {
            int n = rand() % 2;
            task.priority = n;
            task.arrived = minute;
            taskPQ.enqueue(task);

            n = rand() % 2;
            task.priority = n;
            task.arrived = minute;
            taskPQ.enqueue(task);

            cout << "Adding 2 task\n" << endl;
            taskPQ.showStructure();
            cout << endl;
        }
        else {
            cout << "No task was added this time\n" << endl;
            taskPQ.showStructure();
            cout << endl;
            continue;
        }
    }

    cout << "Longest wait for any low-priority(0) task: " << max_0 << endl;
    cout << "Longest wait for any high-priority(1) task: " << max_1 << endl;

    system("pause");
}
