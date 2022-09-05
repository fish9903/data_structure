#include <iostream>
#include <string>

using namespace std;

class List;
class ListNode               
{
private:

    // Constructor
    ListNode(const string& data,
        ListNode* priorPtr, ListNode* nextPtr);
    ListNode(ListNode& a)
    {
        this->ch = a.ch;
        this->coefficient = a.coefficient;
        this->exponent = a.exponent;
        this->next = a.next;
        this->prior = a.prior;
    }
    friend void swap(ListNode& a, ListNode& b);

    // Data members      
    char ch; // 부호
    int coefficient; // 계수
    int exponent; // 지수
    ListNode* prior,   
        * next;     

    friend class List;
};

//--------------------------------------------------------------------

class List
{
public:

    // Constructor
    List();

    // Destructor
    ~List();

    void insert(const string& newDataItem);    
    void clear();                                
    bool isEmpty()const;

    void showStructure() const;
    
    void sort();

private:
    // Data members
    ListNode* head,
        * cursor; 
};

ListNode::ListNode(const string& data, ListNode* priorPtr, ListNode* nextPtr)
{
	prior = priorPtr;
	next = nextPtr;
    ch = data[0];

    int i = 0;
    while (data[i + 1] != ' ')
        i++;
    string temp = data.substr(1, i);
    exponent = stoi(temp);

    temp = data.substr(i + 2);
    coefficient = stoi(temp);
    if (ch == '-')
        coefficient = (-1) * coefficient;
}

List::List() {
    head = NULL;
    cursor = NULL;
}

List::~List() {
    clear();
    head = NULL;
    cursor = NULL;
}

void swap(ListNode& a, ListNode& b)
{
    ListNode temp = a;
    a.ch = b.ch;
    a.coefficient = b.coefficient;
    a.exponent = b.exponent;

    b.ch = temp.ch;
    b.coefficient = temp.coefficient;
    b.exponent = temp.exponent;
}

void List::insert(const string& newDataItem) {

    ListNode* nNode = new ListNode(newDataItem, NULL, NULL);

    if (nNode->coefficient == 0)
        return;

    if (isEmpty())
    {
        head = nNode;
        cursor = nNode;
        
        if (nNode->coefficient < 0)
        {
            nNode->coefficient = (-1) * (nNode->coefficient);
        }
    }
    else
    {
        if (cursor->next == NULL)
        {
            nNode->prior = cursor;
            cursor->next = nNode;
            cursor = nNode;
            
        }
        else if (cursor->prior == NULL)
        {
            nNode->next = head;
            head->prior = nNode;
            head = nNode;
            cursor = nNode;
        }
        else
        {
            nNode->next = cursor->next;
            nNode->prior = cursor;
            cursor->next->prior = nNode;
            cursor->next = nNode;
            cursor = nNode;
        }
    }

    //sort();
}

void List::clear() {
    if (isEmpty())
    {
        cout << "The Polynomial is already Empty" << endl;
        return;
    }
    else
    {
        ListNode* del_Node = head;
        ListNode* del_NextNode = head->next;

        while (del_NextNode != NULL)
        {
            //cout << del_Node->dataItem << " deleted" << endl;
            delete del_Node;

            del_Node = del_NextNode;
            del_NextNode = del_NextNode->next;
        }
        //cout << del_Node->dataItem << " deleted" << endl;
        delete del_Node;
        head = NULL;
        cursor = NULL;
       // cout << "The Polynomial is already Empty" << endl;
        return;
    }
}

bool List::isEmpty() const {
    if (head == NULL)
        return true;
    else
        return false;
}

void List::showStructure() const {
    if (isEmpty())
    {
        cout << "Emty Polynomial" << endl;
        return;
    }
    else
    {
        ListNode* temp = head;
        while (temp != NULL)
        {
            if (temp->coefficient == 0)
            {
                temp = temp->next;
                continue;
            }
            else if (temp == head)
            {
                if (temp->exponent == 0)
                    cout << temp->coefficient << " ";
                else if (temp->coefficient == 1)
                {
                    cout<< "x^" << temp->exponent << " ";
                }
                else if(temp->coefficient == -1)
                {
                    cout << "- " << "x^" << temp->exponent << " ";
                }
                else if(temp->coefficient < 0)
                    cout << "- " << (-1) * temp->coefficient << "x^" << temp->exponent << " ";
                else
                    cout << temp->coefficient << "x^" << temp->exponent << " ";
            }
            else if(temp->coefficient > 0)
            {
                if (temp->exponent == 0)
                    cout << "+ " << temp->coefficient << " ";
                else if (temp->coefficient == 1)
                {
                    cout << "+ " <<"x^" << temp->exponent << " ";
                }
                else
                    cout << "+ " << temp->coefficient << "x^" << temp->exponent << " ";
            }
            else if(temp->coefficient < 0)
            {
                if (temp->exponent == 0)
                    cout << "- " << (-1) * temp->coefficient << " ";
                else if (temp->coefficient == -1)
                {
                    cout << "- " << "x^" << temp->exponent << " ";
                }
                else 
                    cout << "- " << (-1) * temp->coefficient << "x^" << temp->exponent << " ";
            }

            temp = temp->next;
        }
        cout << endl;
    }
}

void List::sort()
{
    if (isEmpty())
    {
        return;
    }
    //정렬
    ListNode* t_cursor = cursor;
    for (ListNode* temp_i = head->next; temp_i != cursor->next; cursor = cursor->prior)
    {
        for (ListNode* temp_j = head->next; temp_j != NULL; temp_j = temp_j->next)
        {
            if (temp_j->prior->exponent < temp_j->exponent)
            {
                swap(*(temp_j->prior), *temp_j);
            }
        }
    }

    // 지수 같으면 더함
    for (ListNode* temp_i = head->next; temp_i != NULL; temp_i = temp_i->next)
    {
        if (temp_i->exponent == temp_i->prior->exponent)
        {
            ListNode* temp = temp_i;

            temp_i->prior->coefficient += temp_i->coefficient;

            if (temp_i->next == NULL)
            {
                /*if (temp_i->prior == NULL)
                {
                    head = NULL;
                    temp_i = NULL;
                    return;
                }*/
                temp_i->prior->next = NULL;
            }
            /*else if (temp_i->prior == NULL)
            {
                temp_i->next->prior = NULL;
                temp_i = temp_i->next;
                head = cursor;
            }*/
            else {
                temp_i->prior->next = temp_i->next;
                temp_i->next->prior = temp_i->prior;
            }
        }
    }

    cursor = t_cursor;
}

int main()
{
    List list;
    string polynomial;

    while (true)
    {
        list.showStructure();

        getline(cin, polynomial);

        if (polynomial == "C" || polynomial == "c")
        {
            list.clear();
            continue;
        }
        else if (polynomial == "q" || polynomial == "Q")
            break;
        else
        {
            list.insert(polynomial);
            list.sort();
        }

    }

    return 0;
}