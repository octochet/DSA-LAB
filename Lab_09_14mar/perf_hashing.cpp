#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int M = 100; // size of the primary hash table
const int MAX_LOAD_FACTOR = 0.75; // maximum load factor before full rehashing
const int INITIAL_MJ = 1; // initial number of slots in each secondary hash table
const int INITIAL_SJ = 2 * (INITIAL_MJ * (INITIAL_MJ - 1)); // initial size of each secondary hash table
const int MAX_TRIES = 100; // maximum number of attempts to find an injective secondary hash function

// function to generate a random hash function
int random_hash_function() {
    // return a random number between 0 and M-1
    return rand() % M;
}

class SecondaryHashTable {
private:
    vector<int> table;
    vector<bool> marked;
    int m; // number of slots in the table
    int b; // number of elements currently in the table
    vector<int> hj; // secondary hash function

public:
    SecondaryHashTable(int m) : table(m, -1), marked(m, false), m(m), b(0) {
        // initialize the secondary hash function
        hj.resize(m);
        for (int i = 0; i < m; i++) {
            hj[i] = random_hash_function();
        }
    }

    // function to insert an element into the secondary hash table
    void insert(int x) {
        int pos = hj[x];
        if (table[pos] == -1) {
            // slot is empty, insert element
            table[pos] = x;
            b++;
        } else if (table[pos] == x) {
            // element is already in the table, no need to insert
            if (marked[pos]) {
                // unmark the element if it was previously marked for deletion
                marked[pos] = false;
            }
        } else {
            // slot is occupied by a different element
            vector<int> L;
            // add all unmarked elements to L
            for (int i = 0; i < m; i++) {
                if (table[i] != -1 && !marked[i]) {
                    L.push_back(table[i]);
                }
            }
            // add the new element to L
            L.push_back(x);
            // clear the table
            table.assign(m, -1);
            // choose a new secondary hash function that is injective on L
            bool injective = false;
            for (int tries = 0; tries < MAX_TRIES; tries++) {
                vector<bool> used(m, false);
                hj.resize(m);
                injective = true;
                for (int i = 0; i < L.size(); i++) {
                    int pos = L[i] % m;
                    int h = random_hash_function();
                    while (used[h]) {
                        h = random_hash_function();
                    }
                    used[h] = true;
                    hj[pos] = h;
                    if (table[hj[L[i]]] != -1) {
                        injective = false;
                        break;
                    }
                }
                if (injective) {
                    break;
                }
            }
            if (!injective) {
                // failed to find an injective secondary hash function, perform full rehashing
                cout << "Failed to find an injective secondary hash function, performing full rehashing" << endl;
                table.assign(m, -1);
                for (int i = 0; i < L.size(); i++) {
                    table[L[i] % m] = L[i];
                }
                hj.resize(m);
                for (int i = 0; i < m; i++) {
                    hj[i] = i;
                }
            } else {
                // insert all elements from L into the new table using
                // the new secondary hash function
                for (int i = 0; i < L.size(); i++) {
                    table[hj[L[i]]] = L[i];
                }
                b = L.size();
            }
        }
    }

    // function to delete an element from the secondary hash table
    void remove(int x) {
        int pos = hj[x];
        if (table[pos] == x) {
            // element is in the table, mark it for deletion
            marked[pos] = true;
            b--;
        }
    }

    // function to check if an element is in the secondary hash table
    bool contains(int x) {
        int pos = hj[x];
        return table[pos] == x && !marked[pos];
    }

    // function to print the secondary hash table
    void print() {
        cout << "Secondary hash table:" << endl;
        for (int i = 0; i < m; i++) {
            cout << i << ": ";
            if (table[i] == -1) {
                cout << "empty";
            } else if (marked[i]) {
                cout << "marked for deletion";
            } else {
                cout << table[i];
            }
            cout << endl;
        }
    }
};

class PrimaryHashTable {
private:
    vector<SecondaryHashTable> table;
    int m; // number of slots in the table
    int b; // number of elements currently in the table

public:
    PrimaryHashTable(int m) : table(m, SecondaryHashTable(INITIAL_SJ)), m(m), b(0) {}

    // function to insert an element into the primary hash table
    void insert(int x) {
        int pos = x % m;
        table[pos].insert(x);
        b++;
        if (b > MAX_LOAD_FACTOR * m) {
            // load factor exceeded, perform full rehashing
            cout << "Load factor exceeded, performing full rehashing" << endl;
            vector<int> L;
            // add all elements from the primary hash table to L
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < m; j++) {
                    if (table[i].contains(j)) {
                        L.push_back(j);
                    }
                }
            }
            // clear the primary hash table
            table.assign(m, SecondaryHashTable(INITIAL_SJ));
            // choose a new primary hash function that is injective on L
            bool injective = false;
            for (int tries = 0; tries < MAX_TRIES; tries++) {
                vector<bool> used(m, false);
                injective = true;
                for (int i = 0; i < L.size(); i++) {
                    int pos = L[i] % m;
                    int h = random_hash_function();
                    while (used[h]) {
                        h = random_hash_function();
                    }
                    used[h] = true;
                    if (table[pos].contains(h)) {
                        injective = false;
                        break;
                    }
                }
                if (injective) {
                    break;
                }
            }
            if (!injective) {
                // failed to find an injective primary hash function, perform full rehashing
                cout << "Failed to find an injective primary hash function, performing full rehashing" << endl;
                table.assign(m, SecondaryHashTable(INITIAL_SJ));
                for (int i = 0; i < L.size(); i++) {
                    table[L[i] % m].insert(L[i]);
                }
            } else {
                // insert all elements from L into the new table using
                // the new primary hash function
                for (int i = 0; i < L.size(); i++) {
                    table[L[i] % m].insert(L[i]);
                }
            }
        }
    }

    // function to delete an element from the primary hash table
    void remove(int x) {
        int pos = x % m;
        table[pos].remove(x);
        b--;
    }

    // function to check if an element is in the primary hash table
    bool contains(int x) {
        int pos = x % m;
        return table[pos].contains(x);
    }

    // function to print the primary hash table
    void print() {
        cout << "Primary hash table:" << endl;
        for (int i = 0; i < m; i++) {
            cout << i << ": ";
            table[i].print();
        }
    }
};

int main() {
    srand(time(NULL));
    PrimaryHashTable table(10);
    table.insert(10);
    table.insert(25);
    table.insert(34);

    table.print();

    table.remove(10);

    table.print();

    return 0;
}