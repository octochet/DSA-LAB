#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

//create a node class
class node {
public:
    //create a character variable
    char ch;
    //create an integer variable
    int freq;
    //create a node pointer
    node *left;
    //create a node pointer
    node *right;
    //create a node pointer
    node *parent;
    //create a constructor
    node(char ch, int freq) {
        //set the character variable equal to the character parameter
        this->ch = ch;
        //set the integer variable equal to the integer parameter
        this->freq = freq;
        //set the left node pointer equal to NULL
        left = NULL;
        //set the right node pointer equal to NULL
        right = NULL;
        //set the parent node pointer equal to NULL
        parent = NULL;
    }
    //create a constructor
    node(int freq, node *left, node *right) {
        //set the character variable equal to NULL
        ch = '\0';
        //set the integer variable equal to the integer parameter
        this->freq = freq;
        //set the left node pointer equal to the left node parameter
        this->left = left;
        //set the right node pointer equal to the right node parameter
        this->right = right;
        //set the parent node pointer equal to NULL
        parent = NULL;
    }
};

//create a compare class
class compare {
public:
    //create a boolean function
    bool operator()(node *left, node *right) {
        //return true if the frequency of the left node is greater than the frequency of the right node
        return left->freq > right->freq;
    }
};

int main() {
    //open input.txt
    ifstream input("input.txt");
    string line;
    //create a map to store the frequency of each character
    map<char, int> freq;
    //read input.txt line by line
    while (getline(input, line)) {
        for (char ch : line) {
            //if the character is not in the map
            if (freq.find(ch) == freq.end()) {
                //add the character to the map
                freq[ch] = 1;
            }
            //if the character is in the map
            else {
                //increment the frequency of the character
                freq[ch]++;
            }
        }
    }
    //create a priority queue
    priority_queue<node *, vector<node *>, compare> pq;
    //iterate through the map
    for (auto it = freq.begin(); it != freq.end(); it++) {
        //create a new node
        node *n = new node(it->first, it->second);
        //push the node into the priority queue
        pq.push(n);
    }
    //create a node pointer
    node *root;
    //while the priority queue is not empty
    while (pq.size() != 1) {
        //create a new node
        node *left = pq.top();
        //pop the node from the priority queue
        pq.pop();
        //create a new node
        node *right = pq.top();
        //pop the node from the priority queue
        pq.pop();
        //create a new node
        node *parent = new node(left->freq + right->freq, left, right);
        //set the parent node pointer of the left node equal to the parent node
        left->parent = parent;
        //set the parent node pointer of the right node equal to the parent node
        right->parent = parent;
        //push the parent node into the priority queue
        pq.push(parent);
        //set the root node equal to the parent node
        root = parent;
    }

    //create a map to store the binary code of each character
    map<char, string> code;
    //iterate through the map
    for (auto it = freq.begin(); it != freq.end(); it++) {
        //create a string variable
        cout<<it->first<<it->second<<endl;
        string s = "";
        //create a node pointer
        node *n = root;
        //while the node pointer is not equal to NULL
        while (n != NULL) {
            //if the character of the node is equal to the character of the map
            if (n->ch == it->first) {
                //reverse the string
                reverse(s.begin(), s.end());
                //add the string to the map
                code[it->first] = s;
                //break out of the loop
                break;
            }
            //if the character of the node is not equal to the character of the map
            else {
                //if the parent node pointer of the node is not equal to NULL
                if (n->parent != NULL) {
                    //if the left node pointer of the parent node is equal to the node
                    if (n->parent->left == n) {
                        //add a 0 to the string
                        s += "0";
                    }
                    //if the right node pointer of the parent node is equal to the node
                    else {
                        //add a 1 to the string
                        s += "1";
                    }
                }
                //set the node equal to the parent node
                n = n->parent;
            }
        }
    }

    //create a string variable
    string encoded = "";
    //read input.txt line by line
    while (getline(input, line)) {
        //iterate through the line
        for (char ch : line) {
            //add the binary code of the character to the string
            encoded += code[ch];
        }
        cout<<encoded<<endl;
    }

    //create a string variable
    string decoded = "";
    //create a node pointer
    node *n = root;
    //iterate through the string
    for (char ch : encoded) {
        //if the character is a 0
        if (ch == '0') {
            //set the node equal to the left node
            n = n->left;
        }
        //if the character is a 1
        else {
            //set the node equal to the right node
            n = n->right;
        }
        //if the node is a leaf node
        if (n->left == NULL && n->right == NULL) {
            //add the character of the node to the string
            decoded += n->ch;
            //set the node equal to the root node
            n = root;
        }
    }

    //open output.txt
    ofstream output("output.txt");
    //write the decoded string to output.txt
    output << decoded;
    //close output.txt
    output.close();
    //close input.txt
    input.close();
    return 0;
}



