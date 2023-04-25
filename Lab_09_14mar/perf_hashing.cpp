#include<iostream>

using namespace std;

/*
Dynamic Perfect Hashing
*/

class Node {
public:
    int key;
    Node* next;
    Node(int key) {
        this->key = key;
        this->next = NULL;
    }
};

class List {
public:
    Node* head;
    List() {
        this->head = NULL;
    }
    void insert(int key) {
        Node* newNode = new Node(key);
        if (this->head == NULL) {
            this->head = newNode;
        }
        else {
            newNode->next = this->head;
            this->head = newNode;
        }
    }
    void print() {
        Node* temp = this->head;
        while (temp != NULL) {
            cout << temp->key << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

class HashTable {
public:
    List** table;
    int count;
    int size;
    HashTable(int size) {
        this->size = size;
        this->count = 0;
        this->table = new List * [size];
        for (int i = 0; i < size; i++) {
            this->table[i] = new List();
        }
    }
};
