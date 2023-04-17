#include <bits/stdc++.h>

using namespace std;

struct node {
    char ch;
    int freq;
    node *left;
    node *right;
    node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = NULL;
        right = NULL;
    }

    node(int cummulative_freq, node *left, node *right) {
        ch = '\0';
        this->freq = cummulative_freq;
        this->left = left;
        this->right = right;
    }
};

class compare {
public:
    bool operator()(node *left, node *right) {
        return left->freq > right->freq; // min heap
    }
};

void print(priority_queue<node*, vector<node*>, compare> pq) {
    while(!pq.empty()) {
        cout<<pq.top()->ch<<" "<<pq.top()->freq<<endl;
        pq.pop();
    }
}

//print the tree
void print_tree(node *root, string code) {
    cout<<"hello"<<endl;
    if (root == NULL) {
        return;
    }
    if (root->ch != '\0') {
        cout << root->ch << " " << code << endl;
    }
    print_tree(root->left, code + "0");
    print_tree(root->right, code + "1");
}

void delete_tree(node* root) {
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

int main() {
    ifstream input("input.txt");
    string line;
    map<char, int> freq;
    while (getline(input, line)) {
        for (char ch : line) {
            freq[ch]++;
        }
    }

    // //print the frequency of each character
    // for (auto it = freq.begin(); it != freq.end(); it++) {
    //     cout << it->first << " " << it->second << endl;
    // }

    priority_queue<node*, vector<node*>, compare> pq;
    for(auto it = freq.begin(); it != freq.end(); it++) {
        node *n = new node(it->first, it->second);
        pq.push(n);
    }

    //print(pq);cout<<endl;

    while(pq.size()>1) {
        int freq=0;
        node *one = new node(pq.top()->ch, pq.top()->freq);
        freq += pq.top()->freq;
        pq.pop();
        node *two = new node(pq.top()->ch, pq.top()->freq);
        freq += pq.top()->freq;
        pq.pop();

        node *cummulative = new node(freq, one, two);
        pq.push(cummulative);
        //print(pq);
        //cout<<endl;
    }

    node *root = pq.top();
    print_tree(root, "");
    return 0;
}