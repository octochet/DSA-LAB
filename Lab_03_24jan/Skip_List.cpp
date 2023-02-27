#include<iostream>

using namespace std;

//skip list node
struct node {
    int data;   //data
    node *next; //pointer to next node
    node *down; //pointer to down node
};

//skip list class
class skip_list {
    node *head; //head pointer
    node *tail; //tail pointer
    int size;   //size of skip list
    int level;  //level of skip list
public:
    skip_list();       //constructor
    void insert(int);  //insert function
    void display();   //display function
    void search(int); //search function
    void remove(int); //remove function
};

//constructor
skip_list::skip_list() {
    head = new node;    //create head node
    tail = new node;    //create tail node
    head->data = -1;    //assign -1 to head node
    tail->data = -1;    //assign -1 to tail node
    head->next = tail;  //link head and tail
    head->down = NULL;  //assign NULL to head down pointer
    tail->next = NULL;  //assign NULL to tail next pointer
    tail->down = NULL;  //assign NULL to tail down pointer
    size = 0;        //assign 0 to size
    level = 0;      //assign 0 to level
}

//insert function
void skip_list::insert(int x) {
    node *temp = head;  //create a temporary node
    node *prev = NULL;  //create a previous node
    node *new_node = new node;  //create a new node
    new_node->data = x; //assign x to new node
    new_node->next = NULL;  //assign NULL to new node next pointer
    new_node->down = NULL;  //assign NULL to new node down pointer
    while (temp != NULL) {  //traverse the skip list
        if (temp->data == x) {  //if element already exists
            cout << "Element already exists" << endl;   //print message
            return; //return
        }   
        if (temp->data < x) {   //if element is less than x
            prev = temp;    //assign temp to prev
            temp = temp->next;  //assign temp next to temp
        }
        else {  //if element is greater than x
            if (temp->down == NULL) {   //if temp down is NULL
                prev->next = new_node;  //link new node to prev
                new_node->next = temp;  //link temp to new node
                size++; //increment size
                break;  //break
            }
            else {  //if temp down is not NULL
                prev = temp;    //assign temp to prev
                temp = temp->down;  //assign temp down to temp
            }
        }
    }
    int r = rand() % 2; //generate random number
    if (r == 1) {   //if random number is 1
        node *new_head = new node;  //create a new head node
        new_head->data = -1;    //assign -1 to new head node
        new_head->next = new_node;  //link new node to new head
        new_head->down = head;  //link head to new head
        head = new_head;    //assign new head to head
        level++;    //increment level
    }
}

//display function
void skip_list::display() {
    node *temp = head;  //create a temporary node
    while (temp != NULL) {  //traverse the skip list
        node *temp1 = temp; //create a temporary node
        while (temp1 != NULL) { //traverse the skip list
            cout << temp1->data << " "; //print data
            temp1 = temp1->next;    //assign temp1 next to temp1
        }   
        cout << endl;   
        temp = temp->down;  //assign temp down to temp
    }
}

//search function
void skip_list::search(int x) {
    node *temp = head;  //create a temporary node
    while (temp != NULL) {  //traverse the skip list
        if (temp->data == x) {  //if element is found
            cout << "Element found" << endl;    //print message
            return;
        }
        if (temp->data < x) {       //if element is less than x
            temp = temp->next;  //assign temp next to temp
        }   
        else {  //if element is greater than x
            temp = temp->down;  //assign temp down to temp
        }
    }
    cout << "Element not found" << endl;    //print message
}

//remove function
void skip_list::remove(int x) {
    node *temp = head;  //create a temporary node
    node *prev = NULL;  //create a previous node
    while (temp != NULL) {  //traverse the skip list
        if (temp->data == x) {  //if element is found
            prev->next = temp->next;    //link temp next to prev
            delete temp;    //delete temp
            size--; //decrement size
            return; 
        }
        if (temp->data < x) {   //if element is less than x
            prev = temp;    //assign temp to prev
            temp = temp->next;  //assign temp next to temp
        }   
        else {  //if element is greater than x
            temp = temp->down;  //assign temp down to temp
        }
    }
    cout << "Element not found" << endl;    //print message
}

//main function
int main() {
    skip_list s;
    int choice, x;
    //menu driven program
    while (1) { 
        cout << "1. Insert" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search" << endl;
        cout << "4. Remove" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Enter the element to be inserted: ";
            cin >> x;
            s.insert(x);
            break;
        case 2:
            s.display();
            break;
        case 3:
            cout << "Enter the element to be searched: ";
            cin >> x;
            s.search(x);
            break;
        case 4:
            cout << "Enter the element to be removed: ";
            cin >> x;
            s.remove(x);
            break;
        case 5:
            exit(0);
        default:
            cout << "Invalid choice" << endl;
        }
    }
    return 0;
}