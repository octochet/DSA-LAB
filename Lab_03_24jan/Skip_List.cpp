#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Skip list node structure
struct Node
{
    int key;
    int value;
    Node **forward; // array of pointers to forward nodes
    Node(int level, int key, int value)
    {
        this->key = key;
        this->value = value;
        forward = new Node *[level + 1];
        memset(forward, 0, sizeof(Node *) * (level + 1));
    }
    ~Node()
    {
        delete[] forward;
    }
};

// Skip list class
class SkipList
{
public:
    // Constructor
    SkipList(int max_level, float p)
    {
        this->max_level = max_level;
        this->p = p;
        level = 0;
        head = new Node(max_level, -1, -1);
    }
    // Destructor
    ~SkipList()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *temp = current;
            current = current->forward[0];
            delete temp;
        }
    }
    // Insert a key-value pair into the skip list
    void insert(int key, int value)
    {
        Node *current = head; // start from head node
        Node *update[max_level + 1];  // array of pointers to update nodes
        memset(update, 0, sizeof(Node *) * (max_level + 1)); // initialize update array as 0
        for (int i = level; i >= 0; i--) 
        {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
            {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (current == nullptr || current->key != key)
        {
            int new_level = randomLevel();
            if (new_level > level)
            {
                for (int i = level + 1; i <= new_level; i++)
                {
                    update[i] = head;
                }
                level = new_level;
            }
            Node *n = new Node(new_level, key, value);
            for (int i = 0; i <= new_level; i++)
            {
                n->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = n;
            }
        }
    }

    // Delete a node with a given key from the skip list
    void remove(int key)
    {
        Node *current = head;
        Node *update[max_level + 1];
        memset(update, 0, sizeof(Node *) * (max_level + 1));
        for (int i = level; i >= 0; i--)
        {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
            {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];
        if (current != nullptr && current->key == key)
        {
            for (int i = 0; i <= level; i++)
            {
                if (update[i]->forward[i] != current)
                {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (level > 0 && head->forward[level] == nullptr)
            {
                level--;
            }
        }
    }

    // Search for a node with a given key in the skip list
    bool search(int key)
    {
        Node *current = head;
        for (int i = level; i >= 0; i--)
        {
            while (current->forward[i] != nullptr && current->forward[i]->key < key)
            {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        return current != nullptr && current->key == key;
    }

    // Print the skip list 
    void print()
    {
        cout << "Skip list:" << endl;
        for (int i = level; i >= 0; i--)
        {
            Node *node = head->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr)
            {
                cout << node->key << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }

    // Get the size of the skip list
    int getSize()
    {
        int size = 0;
        Node *node = head->forward[0];
        while (node != nullptr)
        {
            size++;
            node = node->forward[0];
        }
        return size;
    }

    // Get the height of the skip list
    int getHeight()
    {
        return level;
    }

private:
    int max_level; // maximum level of skip list
    float p;       // probability of increasing level
    int level;     // current level of skip list
    Node *head;    // pointer to head node
    // Generate a random level for a new node
    int randomLevel()
    {
        int level = 0;
        while (((float)rand() / RAND_MAX) < p && level < max_level)
        {
            level++;
        }
        return level;
    }
};

void test1()
{
    SkipList list(3, 0.5);
    list.insert(3, 0);
    list.insert(6, 0);
    list.insert(7, 0);
    list.insert(9, 0);
    list.insert(12, 0);
    list.insert(19, 0);
    list.insert(17, 0);
    list.insert(26, 0);
    list.insert(21, 0);
    list.insert(25, 0);
    list.print();
    cout << "Size: " << list.getSize() << endl;
    cout << "Height: " << list.getHeight() << endl;
    cout << "Search for 19: " << list.search(19) << endl;
    cout << "Search for 15: " << list.search(15) << endl;
    list.remove(19);
    list.remove(15);
    list.print();
    cout << "Size: " << list.getSize() << endl;
    cout << "Height: " << list.getHeight() << endl;
}

void test2() {
    cout << "enter the max level of the skip list: ";
    int max_level;
    cin >> max_level;
    cout << "enter the probability of increasing level: ";
    float p;
    cin >> p;
    SkipList list(max_level, p);
    // switch case
    while (true)
    {
        int choice;
        cout << "1. Insert element into the list" << endl;
        cout << "2. Delete element from the list" << endl;
        cout << "3. Search element from the list" << endl;
        cout << "4. Print Skip List" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter element to be inserted: ";
            int x;
            cin >> x;
            list.insert(x, 0);
            break;
        case 2:
            cout << "Enter element to be deleted: ";
            cin >> x;
            list.remove(x);
            break;
        case 3:
            cout << "Enter element to be searched: ";
            cin >> x;
            if (list.search(x))
                cout << "Found" << endl;
            else
                cout << "Not Found" << endl;
            break;
        case 4:
            list.print();
            break;
        case 5:
            exit(1);
        default:
            cout << "Wrong choice" << endl;
        }
    }
}

int main()
{
    srand((unsigned)time(0)); // initialize random seed
    cout << "Skip List Implementation" << endl;

    //predefined test case
    test1();

    // //user defined test case
    // test2();   
    return 0;
}