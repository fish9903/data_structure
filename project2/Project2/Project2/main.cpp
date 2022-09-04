#include <iostream>
#include <string>
#include "listlnk.cpp"

class Person {
public:
    string name;
    List<string> friends;
public:
    Person(string name_in="") {
        //cout << "Person constructor" << endl;
        name = name_in; 
    }
    ~Person() { 
        friends.clear(); 
    }
    string& getName() { return name; }
    void add_friend(Person& p) {
        friends.insert(p.name);
    }
    void delete_freind(Person& p) {
        friends.find(p.name);
        friends.remove();
    }
    bool isFriend(Person& p) {
        if (friends.contains(p.name))
            return true;
        else
            return false;
    }
    void show() {
        friends.showStructure();
    }

    friend std::ostream& operator<<(std::ostream& out, const Person& p) {
        out << p.name;
        return out;
    }
};

void print_help()
{
    cout << endl << "Commands:" << endl;
    cout << "P<name> - Create a person record of the specified name." << endl;
    cout << "F<name1><name2> - Record that the two specified people are friends." << endl;
    cout << "U<name1><name2> - Record that two specified people are no longer friends." << endl;
    cout << "L<name> - Print out the friends of the specified person." << endl;
    cout << "O<name1><name2> - Check whether the two people are friends." << endl;
    cout << "X - terminate the program." << endl;

    cout << endl;
}

int main() {
    char cmd;
    string name1, name2;
    
    Person* person[100]; // person array
    Person* person1 = NULL;
    Person* person2 = NULL;
    int num = 0;

    print_help();

    do
    {
        cout << endl << "Command: ";                  // Read command
        cin >> cmd;
        if (cmd == 'P' || cmd == 'L' || cmd == 'p' || cmd == 'l')
            cin >> name1;
        else if (cmd == 'F' || cmd == 'U' || cmd == 'f' || cmd == 'u' || cmd == 'Q' || cmd == 'q') {
            cin >> name1 >> name2;
        }

        switch (cmd)
        {
        case 'P': case 'p': // add person
            num++;
            person[num - 1] = new Person(name1);
            break;

        case 'F': case 'f': // add friend
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name1) {
                    person1 = person[i];
                    break;
                }
            }
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name2) {
                    person2 = person[i];
                    break;
                }
            }

            if (person1 == NULL || person2 == NULL) {
                cout << "There is no such person" << endl;
                break;
            }

            person1->add_friend(*person2);
            person2->add_friend(*person1);
            break;

        case 'U': case 'u': // delete friend
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name1) {
                    person1 = person[i];
                    break;
                }
            }
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name2) {
                    person2 = person[i];
                    break;
                }
            }

            person1->delete_freind(*person2);
            person2->delete_freind(*person1);
            break;

        case 'L': case 'l': // print friends
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name1)
                    person1 = person[i];
            }
            person1->show();
            break;

        case 'Q': case 'q': // isfriend?
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name1) {
                    person1 = person[i];
                    break;
                }
            }
            for (int i = 0; i < num; i++) {
                if (person[i]->getName() == name2) {
                    person2 = person[i];
                    break;
                }
            }
            
            if (person1 == NULL || person2 == NULL) {
                cout << "There is no such person" << endl;
                break;
            }

            if (person1->isFriend(*person2))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
            break;

        case 'X': case 'x':
            cout << "x" << endl;
            break;

        default:
            cout << "Inactive or invalid command" << endl;
        }
    } while (cmd != 'X' && cmd != 'x');

    for (int i = 0; i < num; i++) {
        if(person[i] != NULL)
            delete person[i];
    }
}