#include "phonebook.h"

//--------------------------------------------------------------------
//
//                                                       phonebook.cpp
//													  2018112072_����ȣ
//
//--------------------------------------------------------------------

string Person::Month_Arr[12] =
{
	"January",	 "February",	"March",	"April",
	"May",		 "June",		"July",		"August",
	"September", "October",		"November",	"December"
};

List::List(int maxNumber)
	:maxSize(maxNumber), size(0), cursor(-1)
{
	dataItems = new Person[maxSize];
}

List::~List()
{
	if(dataItems != NULL)
		delete[] dataItems;
}

void List::Read(ifstream& fin)
{
	cout << "Enter the name of the file: ";
	//ifstream fin; // ���� ��� ��ü ����
	string fname;
	cin >> fname;
	//while (getchar() != '\n');

	fin.open(fname + ".txt");
	if (!fin)
	{
		cout << "File Open Failed" << endl;
		return;
	}
	
	int count = 0; // ������� ��
	string line;
	int num_line = 0; // ���� ���� ��
	while (!fin.eof())
	{
		//cout << fin.tellg() << endl;
		getline(fin, line);
		switch (num_line % 4)
		{
		case 0:
			dataItems[count].name = line;
			break;
		case 1:
			dataItems[count].tel = line;
			break;
		case 2:
			dataItems[count].birth = line;
		case 3:
			break;
		}
		num_line++;

		// �� ����� ���� ���� ��
		if(line == "")
			count++;		
	}
	
	// ���� ũ��
	size = count;
	cursor = count - 1;

	Show(fin);
}

void List::add(ifstream& fin)
{
	cout << "Add an entry: " << endl;

	if (!fin.is_open())
	{
		cout << "Read File First" << endl;
		return;
	}
	if (isFull())
	{
		cout << "Add Failed. The Phonebook is Full" << endl;
		return;
	}

	size++;
	cursor++;

	// �߰��ϴ� ��� ���� ����
	while (getchar() != '\n');
	cout << "Name : ";
	getline(cin, dataItems[cursor].name);
	
	cout << "Phone : ";
	getline(cin, dataItems[cursor].tel);
	
	cout << "Birthday : ";
	getline(cin, dataItems[cursor].birth);
	

	Show(fin);
}

void List::Remove(ifstream& fin)
{
	cout << "Remove an entry: " << endl;

	if (!fin.is_open())
	{
		cout << "Read File First" << endl;
		return;
	}
	if (isEmpty())
	{
		cout << "Remove Failed. The Phonebook is Empty" << endl;
		return;
	}

	// ������ ��� �̸�
	string target_name;
	while (getchar() != '\n');
	cout << "Name : ";
	getline(cin, target_name);

	int flag = 0;
	for (int i = 0; i < size; i++)
	{
		if (dataItems[i].name == target_name)
		{
			for (int j = i; j < size - 1; j++)
			{
				dataItems[j].name = dataItems[j + 1].name;
				dataItems[j].tel = dataItems[j + 1].tel;
				dataItems[j].birth = dataItems[j + 1].birth;
				dataItems[j].birth_month = dataItems[j+ 1].birth_month;
				
			}
			flag = 1;
			size--;
			cursor--;
			break;
		}
	}
	if (!flag)
	{
		cout << "There's no such person" << endl;
		return;
	}

	Show(fin);
}

void List::Write()
{
	if (isEmpty())
	{
		cout << "Write Failed. The phonebook is Empty." << endl;
		return;
	}

	ofstream fw;
	string f_name;
	cout << "Enter the name of the file: ";
	cin >> f_name;

	fw.open(f_name + ".txt");
	for (int i = 0; i < size; i++)
	{
		fw.write(dataItems[i].name.c_str(), dataItems[i].name.size());
		fw.write("\n", 1);
		fw.write(dataItems[i].tel.c_str(), dataItems[i].tel.size());
		fw.write("\n", 1);
		fw.write(dataItems[i].birth.c_str(), dataItems[i].birth.size());
		fw.write("\n", 1);
		if(i != size - 1)
			fw.write("\n", 1);
	}

	cout << "The list is written into " << f_name << endl;

	fw.close();
}

void List::Month(ifstream& fin)
{
	cout << "Enter the selected month: ";

	if (!fin.is_open())
	{
		cout << "Read File First" << endl;
		return;
	}

	// ã�� month
	string month_name;
	cin >> month_name;
	cout << endl;

	int month_find = 0;

	for (int i = 0; i < 12; i++)
	{
		// ã�����ϴ� ���� ������ ��ȯ
		if (Person::Month_Arr[i] == month_name)
		{
			month_find = i + 1;
			break;
		}
	}

	// month_name�� �߸� �Է����� ���
	if (month_find == 0)
	{
		cout << "Wrong Month Input" << endl;
		return;
	}

	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (dataItems[i].birth_month == month_find)
		{
			count++;
		}
	}
	cout << "Total number of birthdays in" << month_name << " : " << count << endl;

	for (int i = 0; i < size; i++)
	{
		if (dataItems[i].birth_month == month_find)
		{
			cout << dataItems[i].name << endl;
			cout << dataItems[i].tel << endl;
			cout << dataItems[i].birth << endl;
			cout << endl;
		}
	}
}

void List::Show(ifstream& fin)
{
	cout << "Total number of entries in the list: " << size << endl;
	// ã�� ���� �����ϱ� ����
	int month_num[12] = { 0, };

	for (int i = 0; i < size; i++)
	{
		// string birth �� ���� ���ڰ� �¾ �޿� �ش��ϹǷ� '/' ������ ������ ������ �ٲ�
		dataItems[i].birth_month = stoi(dataItems[i].birth);

		int temp = dataItems[i].birth_month;
		// n���� month_num[n - 1]�� �ش��ϹǷ�
		month_num[temp - 1]++;
	}

	cout << "Number of birthdays in" << endl;
	for (int i = 0; i < 12; i++)
	{
		if (month_num[i] != 0)
		{
			cout << "\t" << Person::Month_Arr[i] << ": " << month_num[i] << endl;
		}
	}
}

bool List::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
}

bool List::isFull()
{
	if (size == maxSize)
		return true;
	else
		return false;
}
