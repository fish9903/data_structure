#include <iostream>

using namespace std;

class Queue {
	int* order;

	int maxSize;
	int size;
	int front;
	int rear;

public:
	Queue(int maxsize = 10) {
		this->maxSize = maxsize + 1;
		size = 0;
		front = maxsize;
		rear = maxsize;

		order = new int[maxSize];
	}
	~Queue() {
		delete[] order;
	}

	void add(int newdata) {
		if (front == (rear + 1) % maxSize) {
			cout << " Queue is Full" << endl;
			return;
		}
		
		if (size == 0)
			front = 0;
		size++;
		rear = (rear + 1) % maxSize;
		order[rear] = newdata;
	}
	
	int pop() {
		int temp = order[0];
		for (int i = 0; i < rear; i++) {
			order[i] = order[i + 1];
		}
		size--;
		rear--;
		return temp;
	}
	void show() {
		for (int i = 0; i < maxSize - 1; i++) {
			cout << order[i] << " ";
		}
		cout << endl;
	}

	int getSize() {
		return size;
	}
};


int main()
{
	int rep;

	cout << "T : ";
	cin >> rep;

	while (rep--) {
		int num, count;
		cin >> num >> count;

		Queue Q1(num);
		for (int i = 0; i < num; i++) {
			Q1.add(i + 1);
		}

		Queue temp(num);
		int size = Q1.getSize();
		for (int i = 0; i < size; i++) {
			if (i != count - 1)
				Q1.pop();
			else
				temp.add(Q1.pop());
		}

		//Q1 = temp;
		temp.show();
		Q1.show();
	}

	return 0;
}