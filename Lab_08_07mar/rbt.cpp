#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>

using namespace std;

struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
};

enum Color {
    RED, BLACK
};

struct node {
    point pt;
    Color color;
    node *left, *right, *parent;
    node(point pt) : pt(pt), left(NULL), right(NULL), parent(NULL), color(RED) {}

};

class RBTree {
public:
    node *root;
    node *q;

    RBTree() {
        q = NULL;
        root = NULL;
    }
    
    void insert(node** root, point pt) {
        node *newNode = new node(pt);

        node *y = NULL;
        node *x = *root;

        while(x != NULL) {
            y = x;
            if(newNode->pt.x < x->pt.x) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        newNode->parent = y;

        if(y == NULL) {
            *root = newNode;
        } else if(newNode->pt.x < y->pt.x) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        insertionFixup(root, newNode);
    }

    void insertionFixup(node** root, node* newNode) {
        node *parent = NULL;
        node *grandParent = NULL;

        while((newNode != *root) && (newNode->color != BLACK) && (newNode->parent->color == RED)) {
            parent = newNode->parent;
            grandParent = newNode->parent->parent;

            if(parent == grandParent->left) {
                node *uncle = grandParent->right;

                if(uncle != NULL && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    newNode = grandParent;
                } else {
                    if(newNode == parent->right) {
                        leftRotate(root, parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    rightRotate(root, grandParent);
                    swap(parent->color, grandParent->color);
                    newNode = parent;
                }
            } else {
                node *uncle = grandParent->left;

                if(uncle != NULL && uncle->color == RED) {
                    grandParent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    newNode = grandParent;
                } else {
                    if(newNode == parent->left) {
                        rightRotate(root, parent);
                        newNode = parent;
                        parent = newNode->parent;
                    }

                    leftRotate(root, grandParent);
                    swap(parent->color, grandParent->color);
                    newNode = parent;
                }
            }
        }

        (*root)->color = BLACK;
    }

    void leftRotate(node** root, node* x) {
        node *y = x->right;

        x->right = y->left;

        if(y->left != NULL) {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if(x->parent == NULL) {
            *root = y;
        } else if(x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(node** root, node* y) {
        node *x = y->left;

        y->left = x->right;

        if(x->right != NULL) {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if(y->parent == NULL) {
            *root = x;
        } else if(y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        x->right = y;
        y->parent = x;
    }

    node* search(node* root, point pt) {
        if(root == NULL || (root->pt.x == pt.x && root->pt.y == pt.y)) {
            return root;
        }

        if(root->pt.x < pt.x) {
            return search(root->right, pt);
        }

        return search(root->left, pt);
    }

    void Delete(node** root, point pt) {
        node *z = search(*root, pt);

        if(z == NULL) {
            cout << "Point not found" << endl;
            return;
        }

        node *x, *y;

        if(z->left == NULL || z->right == NULL) {
            y = z;
        } else {
            y = successor(z);
        }

        if(y->left != NULL) {
            x = y->left;
        } else {
            x = y->right;
        }

        if(x != NULL) {
            x->parent = y->parent;
        }

        if(y->parent == NULL) {
            *root = x;
        } else if(y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }

        if(y != z) {
            z->pt = y->pt;
        }

        if(y->color == BLACK) {
            deletionFixup(root, x);
        }

        delete y;
    }

    void deletionFixup(node** root, node* x) {
        node *sibling;

        while(x != *root && x->color == BLACK) {
            if(x == x->parent->left) {
                sibling = x->parent->right;

                if(sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(root, x->parent);
                    sibling = x->parent->right;
                }

                if(sibling->left->color == BLACK && sibling->right->color == BLACK) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if(sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(root, sibling);
                        sibling = x->parent->right;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    sibling->right->color = BLACK;
                    leftRotate(root, x->parent);
                    x = *root;
                }
            } else {
                sibling = x->parent->left;

                if(sibling->color == RED) {
                    sibling->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(root, x->parent);
                    sibling = x->parent->left;
                }

                if(sibling->right->color == BLACK && sibling->left->color == BLACK) {
                    sibling->color = RED;
                    x = x->parent;
                } else {
                    if(sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        leftRotate(root, sibling);
                        sibling = x->parent->left;
                    }

                    sibling->color = x->parent->color;
                    x->parent->color = BLACK;
                    sibling->left->color = BLACK;
                    rightRotate(root, x->parent);
                    x = *root;
                }
            }
        }

        x->color = BLACK;
    }

    node* successor(node* x) {
        if(x->right != NULL) {
            return minimum(x->right);
        }

        node *y = x->parent;

        while(y != NULL && x == y->right) {
            x = y;
            y = y->parent;
        }

        return y;
    }

    node* minimum(node* x) {
        while(x->left != NULL) {
            x = x->left;
        }

        return x;
    }

    node** getRoot() {
        return &root;
    }

    void inorder(node* root) {
        if(root == NULL) {
            return;
        }
        inorder(root->left);
        cout << root->pt.x << " " << root->pt.y << " " << root->color << endl;
        inorder(root->right);
    }

    void levelOrder(node* root) {
        if(root == NULL) {
            return;
        }

        queue<node*> q;
        q.push(root);

        while(!q.empty()) {
            node* temp = q.front();
            cout << temp->pt.x << " " << temp->pt.y << " " << temp->color << endl;
            q.pop();

            if(temp->left != NULL) {
                q.push(temp->left);
            }

            if(temp->right != NULL) {
                q.push(temp->right);
            }
        }
    }
};

//red black tree test
int main() {
    RBTree tree;

    tree.insert(&tree.root, point(1, 2));
    tree.insert(&tree.root, point(2, 3));
    tree.insert(&tree.root, point(3, 4));
    tree.insert(&tree.root, point(4, 5));
    tree.insert(&tree.root, point(9, 9));

    tree.levelOrder(tree.root);cout<<endl;

    tree.Delete(&tree.root, point(2, 3));

    tree.levelOrder(tree.root);
    return 0;
}

