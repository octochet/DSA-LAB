#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

struct point {
    int x, y;
};

enum Color {
    RED, BLACK
};

struct node {
    point pt;
    Color color;
    node *left, *right, *parent;
};

class RBTree {
    node *root;
    node *q;
public:
    RBTree() {
        q = NULL;
        root = NULL;
    }
    
    void insert(node** root, point pt) {
        node *newNode = new node;
        newNode->pt = pt;
        newNode->color = RED;
        newNode->left = NULL;
        newNode->right = NULL;

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
};

//k means clustering using red black tree
int main() {
    int n, k;
    cin >> n >> k;
    vector<point> points(n);
    for(int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    RBTree tree;
    for(int i = 0; i < n; i++) {
        tree.insert(tree.getRoot(), points[i]);
    }

    vector<point> centroids(k);
    for(int i = 0; i < k; i++) {
        cin >> centroids[i].x >> centroids[i].y;
    }

    vector<point> newCentroids(k);
    vector<vector<point>> clusters(k);
    vector<int> clusterSize(k, 0);

    while(true) {
        for(int i = 0; i < k; i++) {
            clusterSize[i] = 0;
            clusters[i].clear();
        }

        for(int i = 0; i < n; i++) {
            int minDist = INT32_MAX;
            int cluster = -1;

            for(int j = 0; j < k; j++) {
                int dist = (points[i].x - centroids[j].x) * (points[i].x - centroids[j].x) + (points[i].y - centroids[j].y) * (points[i].y - centroids[j].y);

                if(dist < minDist) {
                    minDist = dist;
                    cluster = j;
                }
            }

            newCentroids[cluster].x += points[i].x;
            newCentroids[cluster].y += points[i].y;
            clusterSize[cluster]++;
            clusters[cluster].push_back(points[i]);
        }

        for(int i = 0; i < k; i++) {
            newCentroids[i].x /= clusterSize[i];
            newCentroids[i].y /= clusterSize[i];
        }

        bool flag = true;
        for(int i = 0; i < k; i++) {
            if(newCentroids[i].x != centroids[i].x || newCentroids[i].y != centroids[i].y) {
                flag = false;
                break;
            }
        }

        if(flag) {
            break;
        }

        for(int i = 0; i < k; i++) {
            centroids[i] = newCentroids[i];
            newCentroids[i].x = 0;
            newCentroids[i].y = 0;
        }
    }

    for(int i = 0; i < k; i++) {
        cout << "Cluster " << i + 1 << " : " << endl;
        for(int j = 0; j < clusters[i].size(); j++) {
            cout << "(" << clusters[i][j].x << "," << clusters[i][j].y << ")" << endl;
        }
    }

    return 0;
}
