/* Created by 2018112072_Á¶±¤È£
*  21.03.10 Lab1
*  Create account, diposit, withdraw, display account
*/

#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

class bank
{
    char name[20];
    int acno;
    char actype[4];
    float balance;

public:
    void init();
    void deposit();
    void withdraw();
    void disp_det();
};
//member functions of bank class
void bank::init()
{
    cout << "New Account" << endl;

    cout << "Enter the Name of the depositor : ";
    cin >> name;
    //cin.ignore();

    cout << "Enter the Account Number : ";
    cin >> acno;
    //cin.ignore();

    cout << "Enter the Account Type : (CURR / SAVG / FD / RD / DMAT) ";
    cin >> actype;
    //cin.ignore();

    cout << "Enter the Amount to Deposit : ";
    cin >> balance;
    //cin.ignore();
}
void bank::deposit()
{
    cout << "Depositing" << endl;

    int deposit_money = 0;
    cout << "Enter the amount to deposit: ";
    cin >> deposit_money;

    this->balance += deposit_money;
}
void bank::withdraw()
{
    cout << "WithDrwal" << endl;

    int withdraw_money = 0;
    cout << "Enter the amount to deposit: ";
    cin >> withdraw_money;

    this->balance -= withdraw_money;
}
void bank::disp_det()
{
    cout << "Account Details" << endl;

    cout << "Name of the depositor : " << name << endl;
    cout << "Account Number        : " << acno << endl;
    cout << "Account Type          : " << actype << endl;
    cout << "Balance               : " << "$" << balance << endl;
}
// main function , exectution starts here
void main(void)
{
    // clrscr();
    bank obj;
    int choice = 1;
    while (choice != 0)
    {
        cout << "Enter 0 to exit\n1. Initialize a new acc.\n2. Deposit\n3. Withdraw\n4. See A / c Status\n";
        cin >> choice;
        cin.ignore();
        cout << endl;
        switch (choice)
        {
        case 0:
            obj.disp_det();
            cout << "EXITING PROGRAM.";
            break;
        case 1:
            obj.init();
            break;
        case 2:
            obj.deposit();
            break;
        case 3:
            obj.withdraw();
            break;
        case 4:
            obj.disp_det();
            break;
        default:
            cout << "Illegal Option" << endl;
        }
    }
    _getch();
}