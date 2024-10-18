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
        int data;   // The main data of the node
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
        newNode->prev = temp;       // newNode points back to temp
        if (temp->next)             // If newNode's next element is NOT null, then we need that node to point back at newNode
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
        if (temp->prev)                    // If we're not at the head node
            temp->prev->next = temp->next; // Set previous element to point to the node AFTER the one we're deleting
        else
            head = temp->next; // Otherwise we are at the head, so next node becomes the head

        // Let's make sure the node has a next and isn't the tail
        if (temp->next)                    // Not the tail node
            temp->next->prev = temp->prev; // So the next node will point to the previous node after deletion
        else
            tail = temp->prev; // Otherwise we are at the tail, so the previous node becomes the tail.

        delete temp; // Finally we can clear the memory
    }

    // Delete node at given poistion
    void delete_pos(int pos)
    {
        // Guard statement: there's no head, so list is empty, nothing to delete, just return
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        // I would prefer pos == 0, but it works
        if (pos == 1)
        {
            pop_front(); // Method below: delete first element and reset head. Does not return a value
            return;
        }

        Node *temp = head; // Temp value for iteration like above

        // Iterate until desired position
        for (int i = 1; i < pos; i++)
        {
            if (!temp) // If position out of bounds, exit
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next; // Else move to the following node
        }
        if (!temp) // If position out of bounds, exit
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) // If we're at the index we want, but next node is null, we must be at tail
        {
            pop_back(); // Delete tail node and reassign tail
            return;
        }

        Node *tempPrev = temp->prev; // tempPrev to represent node at previous index
        tempPrev->next = temp->next; // Previous node now pointing to next node in chain past item to delete
        temp->next->prev = tempPrev; // Next node to point back to previous
        delete temp;                 // Finally delete the node at index
    }

    // Push new node into tail
    void push_back(int v)
    {
        Node *newNode = new Node(v); // Node to insert
        if (!tail)                   // Empty list so newNode is head and tail
            head = tail = newNode;
        else
        {
            tail->next = newNode; // Otherwise current tail points to newNode
            newNode->prev = tail; // newNode points back to previous tail
            tail = newNode;       // Reassign tail
        }
    }

    // Same thing as tail but for head
    void push_front(int v)
    {
        Node *newNode = new Node(v); // Node to insert
        if (!head)                   // List is empty, so head and tail = newNode
            head = tail = newNode;
        else
        {
            newNode->next = head; // newNode points to current head
            head->prev = newNode; // head points back to newNode
            head = newNode;       // newNode takes it's rightful place at the head
        }
    }

    // Deletes front element, but doesn't return a value typical of pop
    void pop_front()
    {

        if (!head) // Guard statement: there's no head, so list is empty, nothing to delete, just return
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head; // Same as above, create temp node for iteration

        // If head has a next value, meaning list is greater than just a single node
        if (head->next)
        {
            head = head->next;    // Head equals the following element
            head->prev = nullptr; // New head prev now equal to null
        }
        else
            head = tail = nullptr; // Otherwise there was only one element, so list is empty, set pointers to null
        delete temp;               // Clear value from heap
    }

    // Same as pop_front, except for tail of list
    void pop_back()
    {
        if (!tail) // tail is empty, therefore list is empty
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = tail; // Otherwise create a temp pointing to current tail

        if (tail->prev) // If more than one node in list
        {
            tail = tail->prev;    // Make previous node the new tail
            tail->next = nullptr; // tail points to null
        }
        else
            head = tail = nullptr; // Otherwise only one element in list, pointers are both null
        delete temp;               // Clear memory location
    }

    // Destructor to clean up list nodes when list is to be destroyed. No memory leaks
    ~DoublyLinkedList()
    {
        while (head) // While nodes in list
        {
            Node *temp = head; // Hold onto the node to be deleted
            head = head->next; // Reassign head for the moment
            delete temp;       // Release memory
        }
    }

    // Prints the entire list. I prefer toString personally
    void print()
    {
        Node *current = head; // Start with head
        if (!current)         // If no head, list is empty, just return
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current) // While there are nodes
        {
            cout << current->data << " "; // Print current node item
            current = current->next;      // Go to next element
        }
        cout << endl; // Spacing
    }

    // Same as above, just in reverse
    void print_reverse()
    {
        Node *current = tail; // Start with tail
        if (!current)         // List is empty, so just return
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current) // While nodes in list
        {
            cout << current->data << " "; // Print node data
            current = current->prev;      // Go to previous node
        }
        cout << endl;
    }

    // Additional class method
    void every_other_element()
    {
        Node *current = head; // Start with head
        if (!current)         // If no head, list is empty, just return
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current) // While there are nodes
        {
            cout << current->data << " "; // Print current node item
            // Go to next next element
            if (current->next != nullptr && current->next->next != nullptr)
            {
                current = current->next->next;
            } else {
                current = nullptr;
            }
        }
        cout << endl; // Spacing
    }
};

int main()
{
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    DoublyLinkedList list;

    cout << "List items:" << endl;
    for (int i = 1; i < 30; i++)
    {
        list.push_back(i);
        cout << "Added element: " << i << endl;
    }

    cout << "every_other_element" << endl;
    list.every_other_element();

    return 0;
}