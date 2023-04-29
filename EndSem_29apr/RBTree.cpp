//
// Red Black Tree Implementation
//
#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

Node::Node(int data, double weight) {
    this->data = data;
    this->weight = weight;
    this->cf = 0;
    color = RED;
    left = right = parent = nullptr;
}

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

//update the cummulative frequencies also
Node* RBTree::insertBST(Node *&root, Node *&ptr) {
    if (root == nullptr)
        return ptr;

    if (ptr->data < root->data) {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    } else if (ptr->data > root->data) {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }

    return root;
}

void RBTree::rotateLeftx(Node*& root, Node* node) {
    Node* right = node->right;
    node->right = right->left;
    if (node->right != nullptr) {
        node->right->parent = node;
    }
    right->parent = node->parent;
    if (node->parent == nullptr) {
        root = right;
    } else if (node == node->parent->left) {
        node->parent->left = right;
    } else {
        node->parent->right = right;
    }
    right->left = node;
    node->parent = right;
}

void RBTree::rotateRightx(Node*& root, Node* node) {
    Node* left = node->left;
    node->left = left->right;
    if (node->left != nullptr) {
        node->left->parent = node;
    }
    left->parent = node->parent;
    if (node->parent == nullptr) {
        root = left;
    } else if (node == node->parent->left) {
        node->parent->left = left;
    } else {
        node->parent->right = left;
    }
    left->right = node;
    node->parent = left;
}

void RBTree::insert(Node*& root, Node* node) {
    Node* y = nullptr;
    Node* x = root;
    while (x != nullptr) {
        y = x;
        if (node->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == nullptr) {
        root = node;
    } else if (node->data < y->data) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->left = nullptr;
    node->right = nullptr;
    node->color = RED;
    fixInsert(root, node);
}

void RBTree::fixInsert(Node*& root, Node* node) {
    while (node->parent != nullptr && node->parent->color == RED) {
        if (node->parent == node->parent->parent->left) {
            Node* y = node->parent->parent->right;
            if (y != nullptr && y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeftx(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRightx(root, node->parent->parent);
            }
        } else {
            Node* y = node->parent->parent->left;
            if (y != nullptr && y->color == RED) {
                node->parent->color = BLACK;
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRightx(root, node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeftx(root, node->parent->parent);
            }
        }
    }
    root->color = BLACK;
    updateCF(node);
}

//fixes the cummulative frequencies from the node to the root
void RBTree::updateCF(Node* node) {
    node->cf = node->weight;
    Node* current = node;
    while (current->parent != nullptr) {
        if (current == current->parent->right) {
            current = current->parent;
            node->cf += current->weight;
            if (current->left != nullptr) {
                node->cf += current->left->cf;
            }
        } else {
            current = current->parent;
        }
    }
    fixSuccessorCF(node->right);
}

//fix all successor cummulative frequencies
void RBTree::fixSuccessorCF(Node* node) {
    if (node == nullptr) {
        return;
    }
    node->cf = node->weight;
    if (node->left != nullptr) {
        node->cf += node->left->cf;
    }
    if (node->right != nullptr) {
        node->cf += node->right->cf;
    }
    fixSuccessorCF(node->left);
    fixSuccessorCF(node->right);
}

void RBTree::insertValue(int n, double w) {
    Node *node = new Node(n, w);
    root = insertBST(root, node);
    fixInsertRBTree(node);
    precomputeCF();
}

void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }

    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

Node* RBTree::deleteBST(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    root->weight = temp->weight;
    return deleteBST(root->right, temp->data);
}

void RBTree::deleteValue(int data) {
    Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}

void RBTree::inorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    inorderBST(ptr->left);
    printf("(val:%d,weight:%f,color:%d,cf:%f) ",ptr->data, ptr->weight,ptr->color,ptr->cf);
    //cout << ptr->data << " " << ptr->color << endl;
    inorderBST(ptr->right);
}

void RBTree::inorder() {
    inorderBST(root);
}

void RBTree::preorderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    cout << ptr->data << " " << ptr->color << endl;
    preorderBST(ptr->left);
    preorderBST(ptr->right);
}

void RBTree::preorder() {
    preorderBST(root);
    //cout << "-------" << endl;
}

void RBTree::levelOrder() {
    levelOrderBST(root);
    //cout << "-------" << endl;
}

void RBTree::alphaQuantile(double alpha) {
    Node* prev = root;
    alphaQuantileBST(root, alpha, prev);
    //cout << "-------" << endl;
}

//do bst search
void RBTree::alphaQuantileBST(Node *&ptr, double alpha, Node* &prev) {
    if(ptr==nullptr) {
        return;
    }
    else if(alpha < ptr->cf) {
        if(ptr->left==nullptr || prev->left==nullptr) {
            printf("The %f quantile is (val:%d,weight:%f,cf:%f)\n",alpha, prev->data, prev->weight, prev->cf);
            return;
        }
        alphaQuantileBST(ptr->left, alpha, prev);
    }
    else if(alpha > ptr->cf) {
        prev = ptr;
        if(ptr->right==nullptr || prev->right==nullptr) {
            printf("The %f quantile is (val:%d,weight:%f,cf:%f)\n",alpha, prev->data, prev->weight, prev->cf);
            return;
        }
        alphaQuantileBST(ptr->right, alpha, prev);
    }
    else if(alpha == ptr->cf) {
        printf("The %f quantile is (val:%d,weight:%f,cf:%f)\n",alpha, ptr->data, ptr->weight, ptr->cf);
        return;
    }
}

void RBTree::predecessor(int data) {
    Node *predecessor = predecessorBST(root, data);
    if (predecessor == nullptr) {
        printf("Predecessor of %d doesn't exist\n", data);
        return;
    }
    printf("(val:%d, weight:%f)\n",predecessor->data, predecessor->weight);
}

Node* RBTree::predecessorBST(Node *&ptr, int data) {
    if (ptr == nullptr)
        return ptr;

    if (ptr->data == data) {
        if (ptr->left != nullptr) {
            Node *temp = ptr->left;
            while (temp->right != nullptr)
                temp = temp->right;
            return temp;
        }
    } else if (data < ptr->data) {
        return predecessorBST(ptr->left, data);
    } else {
        return predecessorBST(ptr->right, data);
    }
}

void RBTree::levelOrderBST(Node *&ptr) {
    if (ptr == nullptr)
        return;

    queue<Node *> q;
    q.push(ptr);

    while (!q.empty()) {
        Node *temp = q.front();
        printf("(%d,%f,%d) ",temp->data, temp->weight, temp->color);
        //cout << temp->data << " " << temp->color << endl;
        q.pop();

        if (temp->left != nullptr)
            q.push(temp->left);

        if (temp->right != nullptr)
            q.push(temp->right);
    }
}

Node *RBTree::minValueNode(Node *&node) {

    Node *ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;

    while (ptr->right != nullptr)
        ptr = ptr->right;

    return ptr;
}

void RBTree::precomputeCF() {
    float sum=0;
    findCF(root, sum);
}



//cumulative frequency function
//cf of node is sum of weights of all nodes in its left subtree + its own weight
//do inorder traversal and keep adding weights of nodes
void RBTree::findCF(Node *node, float& sum) {
    if (node == nullptr)
        return;
    findCF(node->left, sum);
    sum = sum + node->weight;
    node->cf = sum;
    findCF(node->right, sum);
}

int RBTree::getBlackHeight(Node *node) {
    int blackheight = 0;
    while (node != nullptr) {
        if (getColor(node) == BLACK)
            blackheight++;
        node = node->left;
    }
    return blackheight;
}

// Test case 1 : 5 2 9 1 6 8 0 20 30 35 40 50 0
// Test case 2 : 3 0 5 0
// Test case 3 : 2 1 3 0 8 9 4 5 0

void RBTree::merge(RBTree rbTree2) {
    int temp;
    Node *c, *temp_ptr;
    Node *root1 = root;
    Node *root2 = rbTree2.root;
    int initialblackheight1 = getBlackHeight(root1);
    int initialblackheight2 = getBlackHeight(root2);
    if (initialblackheight1 > initialblackheight2) {
        c = maxValueNode(root1);
        temp = c->data;
        deleteValue(c->data);
        root1 = root;
    }
    else if (initialblackheight2 > initialblackheight1) {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
    }
    else {
        c = minValueNode(root2);
        temp = c->data;
        rbTree2.deleteValue(c->data);
        root2 = rbTree2.root;
        if (initialblackheight1 != getBlackHeight(root2)) {
            rbTree2.insertValue(c->data, c->weight);
            root2 = rbTree2.root;
            c = maxValueNode(root1);
            temp = c->data;
            deleteValue(c->data);
            root1 = root;
        }
    }
    setColor(c,RED);
    int finalblackheight1 = getBlackHeight(root1);
    int finalblackheight2 = getBlackHeight(root2);
    if (finalblackheight1 == finalblackheight2) {
        c->left = root1;
        root1->parent = c;
        c->right = root2;
        root2->parent = c;
        setColor(c,BLACK);
        c->data = temp;
        root = c;
    }
    else if (finalblackheight2 > finalblackheight1) {
        Node *ptr = root2;
        while (finalblackheight1 != getBlackHeight(ptr)) {
            temp_ptr = ptr;
            ptr = ptr->left;
        }
        Node *ptr_parent;
        if (ptr == nullptr)
            ptr_parent = temp_ptr;
        else
            ptr_parent = ptr->parent;
        c->left = root1;
        if (root1 != nullptr)
            root1->parent = c;
        c->right = ptr;
        if (ptr != nullptr)
            ptr->parent = c;
        ptr_parent->left = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED){
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root2;
    }
    else {
        Node *ptr = root1;
        while (finalblackheight2 != getBlackHeight(ptr)) {
            ptr = ptr->right;
        }
        Node *ptr_parent = ptr->parent;
        c->right = root2;
        root2->parent = c;
        c->left = ptr;
        ptr->parent = c;
        ptr_parent->right = c;
        c->parent = ptr_parent;
        if (getColor(ptr_parent) == RED) {
            fixInsertRBTree(c);
        }
        else if (getColor(ptr) == RED) {
            fixInsertRBTree(ptr);
        }
        c->data = temp;
        root = root1;
    }
    return;
}

