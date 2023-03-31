#include <iostream>
#include <queue>

using namespace std;

/*
generalised Search Tree, of order m :
- each node has m children
- each node has m-1 keys
- keys are in sorted order
- keys[i] < keys[i+1]
- children[i] < keys[i] < children[i+1]
*/

class SearchTree
{
public:
    //constructor
    SearchTree(int m) {
        this->m = m;
        root = NULL;
    }

    //insert
    void insert(int key) {
        insert(key, root);
    }

    //search
    void search(int key) {
        search(key, root);
    }

    //levelorder
    void levelorder() {
        levelorder(root);
    }

    //inorder
    void inorder() {
        inorder(root);
    }

private:
    //node structure
    struct node
    {
        int *keys;
        node **children;
        int n; 
        bool leaf;
        node(int m, bool leaf) {
            keys = new int[m-1];
            children = new node*[m];
            n = 0;
            this->leaf = leaf;
        }
    };

    node *root;
    int m;

    //insert
    void insert(int key, node *&rt) {
        if (rt == NULL) {
            rt = new node(m, true);
            rt->keys[0] = key;
            rt->n = 1;
        } else {
            if (rt->leaf) {
                int i = rt->n - 1;
                while (i >= 0 && key < rt->keys[i]) {
                    rt->keys[i+1] = rt->keys[i];
                    i--;
                }
                rt->keys[i+1] = key;
                rt->n++;
            } else {
                int i = 0;
                while (i < rt->n && key > rt->keys[i]) {
                    i++;
                }
                insert(key, rt->children[i]);
                if (rt->children[i]->n == m-1) {
                    splitChild(rt, i);
                }
            }
        }
    }

    //split child
    void splitChild(node *&rt, int i) {
        node *y = rt->children[i];
        node *z = new node(m, y->leaf);
        z->n = m/2 - 1;
        for (int j = 0; j < m/2 - 1; j++) {
            z->keys[j] = y->keys[j + m/2];
        }
        if (!y->leaf) {
            for (int j = 0; j < m/2; j++) {
                z->children[j] = y->children[j + m/2];
            }
        }
        y->n = m/2 - 1;
        for (int j = rt->n; j >= i+1; j--) {
            rt->children[j+1] = rt->children[j];
        }
        rt->children[i+1] = z;
        for (int j = rt->n-1; j >= i; j--) {
            rt->keys[j+1] = rt->keys[j];
        }
        rt->keys[i] = y->keys[m/2 - 1];
        rt->n++;
    }

    //search
    void search(int key, node *rt) {
        if (rt == NULL) {
            cout << "Key not found" << endl;
            return;
        }
        int i = 0;
        while (i < rt->n && key > rt->keys[i]) {
            i++;
        }
        if (i < rt->n && key == rt->keys[i]) {
            cout << "Key found" << endl;
            return;
        }
        if (rt->leaf) {
            cout << "Key not found" << endl;
            return;
        }
        search(key, rt->children[i]);
    }

    //levelorder
    void levelorder(node *rt) {
        if (rt == NULL) {
            return;
        }
        queue<node*> q;
        q.push(rt);
        while (!q.empty()) {
            node *temp = q.front();
            q.pop();
            for (int i = 0; i < temp->n; i++) {
                cout << temp->keys[i] << " ";
            }
            cout << endl;
            if (!temp->leaf) {
                for (int i = 0; i <= temp->n; i++) {
                    q.push(temp->children[i]);
                }
            }
        }
    }

    //inorder
    void inorder(node *rt) {
        if (rt == NULL) {
            return;
        }
        int i;
        for (i = 0; i < rt->n; i++) {
            inorder(rt->children[i]);
            cout << rt->keys[i] << " ";
        }
        inorder(rt->children[i]);
    }
};

void test1() {
    SearchTree st(3);
    st.insert(8);
    st.insert(9);
    st.insert(10);
    st.insert(11);
    st.insert(15);
    st.insert(20);
    st.insert(17);

    cout<<"levelorder:" <<endl;st.levelorder();cout<<endl;
    // cout<<"inorder:" <<endl;st.inorder();cout<<endl;
}

int main() {
    test1();
    return 0;
}