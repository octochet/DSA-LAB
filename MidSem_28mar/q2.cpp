
#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;

/*
generalised search tree of order m
every node has m children
every node has m-1 keys
*/

class mSearchTree
{
public:
    //constructor
    mSearchTree(int m) {
        root = NULL;
        this->m = m;
    }

    //insert function
    void insert(int key) {
        insert(key, root);
    }

    //inorder
    void inorder() {
        inorder(root);
    }

    //preorder
    void preorder() {
        preorder(root);
    }

    //levelorder
    void levelorder() {
        levelorder(root);
    }

private:
    struct node
    {
        int key;
        vector<node*> children;
        node(int key, vector<node*> children)
            :key(key), children(children) { }
    };

    node *root;
    int m;

    //insert function
    void insert(int key, node *&t) {
        if (t == NULL) {
            t = new node(key, vector<node*>(m, NULL));
        }
        else {
            int i = 0;
            while (i < m - 1 && key > t->key) {
                i++;
            }
            insert(key, t->children[i]);
        }
    }

    //inorder
    void inorder(node *t) {
        if (t != NULL) {
            for (int i = 0; i < m - 1; i++) {
                inorder(t->children[i]);
                cout << t->key << " ";
            }
            inorder(t->children[m - 1]);
        }
    }

    //preorder
    void preorder(node *t) {
        if (t != NULL) {
            cout << t->key << " ";
            for (int i = 0; i < m; i++) {
                preorder(t->children[i]);
            }
        }
    }

    //levelorder
    void levelorder(node *t) {
        queue<node*> q;
        q.push(t);
        while (!q.empty()) {
            node *temp = q.front();
            q.pop();
            cout << temp->key << " ";
            for (int i = 0; i < m; i++) {
                if (temp->children[i] != NULL) {
                    q.push(temp->children[i]);
                }
            }
        }
    }
};
