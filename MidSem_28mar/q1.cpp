#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

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
    void empty(){
        extractMaxUntilEmpty();
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
        int priority;
        node *left;
        node *right;
        node(int key, int priority, node *lt, node *rt)
            :key(key), priority(priority), left(lt), right(rt) { }
    };

    node *root;
    int maxPriority = INT32_MIN;
    bool isEmpty=true;
    //right rotate
    node *rightRotate(node *root) {
        node *t = root->left;
        node *u = t->right;
        t->right = root;
        root->left = u;
        return t;
    }

    //left rotate
    node* leftRotate(node *root) {
        node *t = root->right;
        node *u = t->left;
        t->left = root;
        root->right = u;
        return t;
    }

    //insert heap fixup definition
    void insertFix(int key, int priority, node *root) {
        
        if(root->left!=NULL && root->priority < root->left->priority) {
            root = rightRotate(root);
        } else if(root->right!=NULL && root->priority < root->right->priority) {
            root = leftRotate(root);
        } else { }
    }

    //insert definition
    void insert(int key, int priority, node *&root) {
        if(root == NULL) {
            isEmpty=false;
            root = new node(key, priority, NULL, NULL);
            if(priority > maxPriority) {
                maxPriority = priority;
            }
        } else if(key < root->key) {
            insert(key, priority, root->left);
            if(root->priority < root->left->priority) {
                root = rightRotate(root);
            }
        } else if(key > root->key) {
            insert(key, priority, root->right);
            if(root->priority < root->right->priority) {
                root = leftRotate(root);
            }
        } else { }
    }

    // find minimum node definition
    node* findMin(node *t) {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);
    }

    //bst delete/remove node definition
    void remove(int key, int priority, node *&t) {
        if(t==NULL) {
            return;
        }
        if(key < t->key) {
            remove(key, priority, t->left);
        } else if(key > t->key) {
            remove(key, priority, t->right);
        } else if(t->left != NULL && t->right != NULL) {
            node *temp = findMin(t->right);
            t->key = temp->key;
            t->priority = temp->priority;
            remove(t->key, t->priority, t->right); 
        } else {
            node* oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
        }
    }

    //extract max definition
    void extractMaxPriority(node* t) {
        if(root->left==NULL && root->right==NULL) {
            cout<<"max key:"<<root->key<<" max priority: "<<root->priority<<endl;
            remove(t->key, t->priority, root);
            isEmpty=true;
            return;
        }
        cout<<"max key:"<<root->key<<" max priority: "<<root->priority<<endl;
        remove(t->key, t->priority, root);
        if(root->right!=NULL && root->priority < root->right->priority) {
            root = leftRotate(root);
        }
        if(root->left!=NULL && root->priority < root->left->priority) {
            root = rightRotate(root);
        }
    }

    //inorder traversal
    void inorder(node *root) {
        if(root == NULL) {
            return;
        } else {
            inorder(root->left);
            cout << root->key << " " << root->priority << " " << endl;
            inorder(root->right);
        }
    }

    //preorder traversal
    void preorder(node *root) {
        if(root == NULL) {
            return;
        } else {
            cout << root->key << " " << root->priority << " " << endl;
            preorder(root->left);
            preorder(root->right);
        }
    }

    void extractMaxUntilEmpty() {
        while(!isEmpty) {
            extractMaxPriority();
            // cout<<"inorder: "<<endl;
            // inorder();
            // cout<<"preorder: "<<endl;
            // preorder();
            cout<<"level order: "<<endl;
            levelorder();
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
};

void test1() {
    newBST bst;
    bst.insert(20, 92);
    bst.insert(50, 73);
    bst.insert(30, 48);
    bst.insert(60, 55);
    bst.insert(40, 21);
    bst.insert(70, 50);
    bst.insert(80, 44);

    cout<<"Initial Tree:"<<endl;
    cout<<"level order: "<<endl;
    bst.levelorder();
    // cout<<"inorder: "<<endl;
    // bst.inorder();
    // cout<<"preorder: "<<endl;
    // bst.preorder();

    // cout<<"after Max Extraction:"<<endl;
    // bst.extractMaxPriority();
    // cout<<"inorder: "<<endl;
    // bst.inorder();
    // cout<<"preorder: "<<endl;
    // bst.preorder();

    bst.empty();
}

void test2() {
    newBST bst;
    bst.insert(5, 3);
    bst.insert(1, 24);
    bst.insert(9, 10);
    bst.insert(8, -2);
    bst.insert(6, 1);
    bst.insert(-3, 0);
    bst.insert(2, 2);

    cout<<"Initial Tree:"<<endl;
    cout<<"level order: "<<endl;
    bst.levelorder();
    // cout<<"inorder: "<<endl;
    // bst.inorder();
    // cout<<"preorder: "<<endl;
    // bst.preorder();

    // cout<<"after Max Extraction:"<<endl;
    // bst.extractMaxPriority();
    // cout<<"inorder: "<<endl;
    // bst.inorder();
    // cout<<"preorder: "<<endl;
    // bst.preorder();

    bst.empty();
}


int main() {
    newBST bst;
    int t;
    while(t!=0) {
        cout<<"Enter 1 to test1, 2 to test2, 0 to exit: ";
        cin>>t;
        if(t==1) {
            test1();
        } else if(t==2) {
            test2();
        } else if(t==0) {
            cout<<"Exiting..."<<endl;
        } else {
            cout<<"Invalid input. Try again."<<endl;
        }
    }
    return 0;
}