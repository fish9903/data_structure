#include "phonebook.h"
using namespace std;

void print_help()
{
	cout << endl << "Commands:" << endl;
	cout << "  R   : read a file" << endl;
	cout << "  +   : add a new entry" << endl;
	cout << "  -   : remove an entry" << endl;
	cout << "  W   : wirte to a file" << endl;
	cout << "  M   : select a month" << endl;
	cout << "  Q   : quit the program" << endl;
	cout << endl;
}

void main()
{
	List phonebook(100);		  // Phonebook list
	char cmd;                 // Input command

	ifstream fin; // 颇老 按眉 积己
	string fname;

	do
	{
		print_help();
		//phonebook.Read();                     // read

		cout << endl << "Command: ";                  // Read command
		cin >> cmd;

		switch (cmd)
		{

		case '+':                                  // insert
			phonebook.add(fin);
			break;

		case '-':                                  // remove
			phonebook.Remove(fin);
			break;

		case 'R': case 'r':                       // read
			phonebook.Read(fin);
			break;

		case 'W': case 'w':                       // write(update)
			phonebook.Write();
			break;

		case 'M': case 'm':                       // month(search month)
			phonebook.Month(fin);
			break;

		case 'Q': case 'q':                   // Quit test program
			break;

		default:                               // Invalid command
			cout << "Inactive or invalid command" << endl;
			while (getchar() != '\n');
		}
	} while (cmd != 'Q' && cmd != 'q');


	if(fin.is_open())
		fin.close();
}