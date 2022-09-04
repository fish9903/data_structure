#include <iostream>
#include <string>

using namespace std;


class List {
	string* person_name;
	int maxSize;
	int head;
	int tail;
public:
	List(int maxsize = 5) {
		person_name = new string[maxsize];
		person_name[0] = "Hong Gildong";
		person_name[1] = "Kim Dongguk";
		person_name[2] = "Lee Hangook";
		person_name[3] = "Park Hanbyul";
		person_name[4] = "Choi Jiyoung";

		this->maxSize = maxsize;
		head = 0;
		tail = maxsize;
	}
	~List() {
		delete[] person_name;
	}

	void delete_name(string& name) {
		bool flag = false;

		for (int i = head; i < tail; i++) {
			if (person_name[i] == name) {
				for (int j = i; j < tail - 1; j++) {
					person_name[j] = person_name[j + 1];
				}
				flag = true;
			}
		}

		if (flag)
			tail--;
		else {
			cout << "There is no such person\n" << endl;
		}
	}

	void show() {
		cout << "There are " << tail << " employees: " << endl;
		for (int i = head; i < tail; i++) {
			cout << person_name[i] << endl;
		}
	}
};


int main() {
	List l1(5);

	while (true)
	{
		l1.show();
		string name;

		cout << "Enter an employee name to remove: ";
		getline(cin, name);
		cout << endl;

		l1.delete_name(name);
	}
	

	return 0;
}