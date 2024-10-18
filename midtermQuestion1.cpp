/*  Midterm 1: Question 1
    Program requirements:
        1. Fully comment each instruction in the code, explaining what's happening on that particular line.
            I want you to convince me that you understand what's happening with every pointer and line of code.
        2. Additionally, write a class method every_other_element() that will output the data structure starting with the first element,
            skip the second element, output the third, skip fourth, etc. Demo this method in your code.
*/

// Import iostream functionality for console input/output. Std namespace so std:: doesn't clutter all the code
#include <iostream>
using namespace std;

// Global constants
// I personally don't see a reason to place these constants in the global scope, simply because the only usage I see is in main.
// I think in my goat herd program that was based off this template, I actually moved them into main just to make the code "safer".
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

// Doubly linked list class object. Technically the really important part is the node pointers to the head and tail of the linked list,
// but this version has inner-class nodes that it manages internally.
class DoublyLinkedList
{
// Private variables, cannot be accessed outside of this class
private:
    // Node structure to hold data elements of type int with pointers to next and previous linked elements
    struct Node
    {
        int data; // The main data of the node
        Node *prev; // Pointer to previous linked list location in memory
        Node *next; // Pointer to next linked list location in memory
        // Full parameter constructor for Node object that assigns received arguments directly to values. Member list assignment also possible
        Node(int val, Node *p = nullptr, Node *n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node *head; // Pointer to the head element of the linked list
    Node *tail; // Pointer to the tail element of the linked list

public:
    // Class constructor to initialize empty linked list and assign pointers to null until initialized with nodes
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    // Because Node and the list are coupled, this function receives an int value, then creates a node and inserts in given position
    void insert_after(int value, int position)
    {
        // Guard statement: if position given by user is out of bounds, don't waste time, just return with console message
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node *newNode = new Node(value); // Creation of pointer to new node value to insert
        // If the head pointer is null, the list must be empty and this is the first node. Assign head and tail to node and return
        if (!head) 
        {
            head = tail = newNode;
            return;
        }

        // If previous guard statements don't execute, create a temp node to iterate over list and find position to insert newNode
        Node *temp = head; 
        // Iterate over list starting from head node until you reach desired position or go out of bounds 
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) // Iteration has gone out of bounds, so output error message, delete node to clear memory since we can't use it, and return
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        // Otherwise we need to do some reorganizing to insert the newNode
        newNode->next = temp->next; // temp represents the node we want to insert newNode after, so temp.next becomes newNode's.next
        newNode->prev = temp; // newNode points back to temp
        if (temp->next) // If newNode's next element is NOT null, then we need that node to point back at newNode
            temp->next->prev = newNode;
        else // Otherwise we're at the end of the list so newNode is the new tail node and needs to be assigned
            tail = newNode;
        temp->next = newNode; // temp is now in front of newNode and points it's next pointer to it
    }

    // Deletes a given node based on it's integer value
    void delete_val(int value)
    {
        if (!head) // Guard statement: there's no head, so list is empty, nothing to delete, just return
            return;

        Node *temp = head; // Otherwise let's create a temp pointer and start iterating until we find the right node

        // Keep iterating while there are values in the list and the current value != what we're looking for
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) // We've iterated the entire list and found nothing. Just return
            return;

        // We found what we're looking for, so we need to do some house keeping
        if (temp->prev) // If we're not at the head node
            temp->prev->next = temp->next; // Set previous element to point to the node AFTER the one we're deleting
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Node *temp = head;

        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(int v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }
};

// Function declarations
void every_other_element();

int main()
{
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning

    return 0;
}

// Function definitions
void every_other_element() {};