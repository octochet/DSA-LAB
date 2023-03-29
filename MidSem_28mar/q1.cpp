#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

//data structure for tree with node which has key, priority, left and right child.
//new bst class, bst property for key, max heap property for priority

class newBST
{
public:
    //constructor
    newBST() {
        root =NULL;
    }

    //insert function
    void insert(int key, int priority) {
        insert(key, priority, root);
    }

    //extract max priority
    void extractMaxPriority() {
        extractMaxPriority(root);
    }

    //extract max until empty
    void extractMaxUntilEmpty(){
        extractMaxUntilEmpty(root);
    }

    //levelorder
    void levelorder() {
        levelorder(root);
    }

    //get root
    void getRoot() {
        getRoot(root);
    }

private:

    struct node
    {
        int key;  
        int priority;
        node *left;
        node *right;
        node(int key, int priority, node *lt, node *rt)
            :key(key), priority(priority), left(lt), right(rt) { }
    };

    node *root;

    //left rotation
    void rotateWithLeftChild(node *&k2) {
        node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    //right rotation
    void rotateWithRightChild(node *&k1) {
        node *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    //insert function
    void insert(int key, int priority, node *&t) {
        if (t == NULL)
            t = new node(key, priority, NULL, NULL);
        else if (key < t->key) {
            insert(key, priority, t->left);
            if (t->left->priority > t->priority)
                rotateWithLeftChild(t);
        }
        else if (key > t->key) {
            insert(key, priority, t->right);
            if (t->right->priority > t->priority)
                rotateWithRightChild(t);
        }
        else
            ;  // Duplicate; do nothing
    }

    //extract max priority 
    void extractMaxPriority(node *&t) {
        if (t == NULL)
            return;
        else if (t->left == NULL && t->right == NULL) {
            delete t;
            t = NULL;
        }
        else if (t->left == NULL) {
            node *temp = t;
            t = t->right;
            delete temp;
        }
        else if (t->right == NULL) {
            node *temp = t;
            t = t->left;
            delete temp;
        }
        else if (t->left->priority > t->right->priority) {
            rotateWithLeftChild(t);
            extractMaxPriority(t->right);
        }
        else {
            rotateWithRightChild(t);
            extractMaxPriority(t->left);
        }
    }

    bool isEmpty() {
        return root == NULL;
    }

    void extractMaxUntilEmpty(node *root) {
        while(!isEmpty()) {
            cout<<"extracting  ";
            getRoot();
            extractMaxPriority();cout<<endl;
            cout<<"Tree: "<<endl;
            levelorder();cout<<endl;
        }
    }

    int height(node* node) {
        if (node == NULL)
            return 0;
        else {
            /* compute the height of each subtree */
            int lheight = height(node->left);
            int rheight = height(node->right);
 
            /* use the larger one */
            if (lheight > rheight) {
                return (lheight + 1);
            }
            else {
                return (rheight + 1);
            }
        }
    }

    void printGivenLevel(struct node* root, int level) {
        if (root == NULL)
            return;
        if (level == 1)
            printf("(%d,%d) ", root->key, root->priority);
        else if (level > 1) {
            printGivenLevel(root->left, level - 1);
            printGivenLevel(root->right, level - 1);
        }
    }
 
    void levelorder(struct node* root) {
        int h = height(root);
        int i;
        for (i = 1; i <= h; i++) {
            printGivenLevel(root, i);
            printf("\n");
        }
    }

    void getRoot(node *&t) {
        printf("root: (%d,%d)", t->key, t->priority);
    }
};

newBST bst;

void test1() {
    bst.insert(20, 92);
    bst.insert(50, 73);
    bst.insert(30, 48);
    bst.insert(10, 55);
    bst.insert(40, 21);
    bst.insert(70, 50);
    bst.insert(80, 44);

    cout<<"Initial Tree:"<<endl;
    bst.levelorder();cout<<endl;

    bst.extractMaxUntilEmpty();
}

void test2() {
    bst.insert(5, 3);
    bst.insert(1, 24);
    bst.insert(9, 10);
    bst.insert(8, -2);
    bst.insert(6, 1);
    bst.insert(-3, 0);
    bst.insert(2, 2);

    cout<<"Initial Tree:"<<endl;
    bst.levelorder();cout<<endl;

    bst.extractMaxUntilEmpty();
}

void test3() {
    bst.insert(50, 100);
    bst.insert(30, 30);
    bst.insert(70, 80);
    bst.insert(20, 29);
    bst.insert(31, 10);
    bst.insert(60,  5);
    bst.insert(90,  6);

    cout<<"Initial Tree:"<<endl;
    bst.levelorder();cout<<endl;

    bst.extractMaxUntilEmpty();
}


int main() {
    int t=1;
    while(t!=0) {
        cout<<"Enter:\n1 to test1,\n2 to test2,\n3 to test3,\n0 to exit:\n";
        cin>>t;
        if(t==1) {
            test1();
        } else if(t==2) {
            test2();
        } else if(t==3) {
            test3();
        } else if(t==0) {
            cout<<"Exiting..."<<endl;
        } else {
            cout<<"Invalid input. Try again."<<endl;
        }
    }
    return 0;
}