
#include <algorithm>  /// for std::max
#include <iostream>   /// for std::cout
#include <queue>      /// for std::queue

using namespace std;

struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
};

node *createNode(int data) {
    node *nn = new node();
    nn->data = data;
    nn->height = 0;
    nn->left = nullptr;
    nn->right = nullptr;
    return nn;
}

int height(node *root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

int getBalance(node *root) { return height(root->left) - height(root->right); }

node *rightRotate(node *root) {
    node *t = root->left;
    node *u = t->right;
    t->right = root;
    root->left = u;
    return t;
}

node *leftRotate(node *root) {
    node *t = root->right;
    node *u = t->left;
    t->left = root;
    root->right = u;
    return t;
}

node *minValue(node *root) {
    if (root->left == nullptr) {
        return root;
    }
    return minValue(root->left);
}

node *insert(node *root, int item) {
    if (root == nullptr) {
        return createNode(item);
    }
    if (item < root->data) {
        root->left = insert(root->left, item);
    } else {
        root->right = insert(root->right, item);
    }
    int b = getBalance(root);
    if (b > 1) {
        if (getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);  // Left-Right Case
        }
        return rightRotate(root);  // Left-Left Case
    } else if (b < -1) {
        if (getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);  // Right-Left Case
        }
        return leftRotate(root);  // Right-Right Case
    }
    return root;
}

node *deleteNode(node *root, int element) {
    if (root == nullptr) {
        return root;
    }
    if (element < root->data) {
        root->left = deleteNode(root->left, element);
    } else if (element > root->data) {
        root->right = deleteNode(root->right, element);

    } else {
        // Node to be deleted is leaf node or have only one Child
        if (!root->right || !root->left) {
            node *temp = !root->right ? root->left : root->right;
            delete root;
            return temp;
        }
        // Node to be deleted have both left and right subtrees
        node *temp = minValue(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    // Balancing Tree after deletion
    return root;
}

void deleteAllNodes(const node *const root) {
    if (root) {
        deleteAllNodes(root->left);
        deleteAllNodes(root->right);
        delete root;
    }
}

void levelOrder(node *root) {
    queue<node *> q;
    q.push(root);
    while (!q.empty()) {
        root = q.front();
        std::cout << root->data << " ";
        q.pop();
        if (root->left) {
            q.push(root->left);
        }
        if (root->right) {
            q.push(root->right);
        }
    }
}



int main() {
    // Testing AVL Tree
    node *root = nullptr;
    int i = 0;
    for (i = 1; i <= 7; i++) root = insert(root, i);
    cout << "LevelOrder: ";
    levelOrder(root);
    root = deleteNode(root, 1);  // Deleting key with value 1
    cout << "\nLevelOrder: ";
    levelOrder(root);
    root = deleteNode(root, 4);  // Deletin key with value 4
    cout << "\nLevelOrder: ";
    levelOrder(root);
    deleteAllNodes(root);
    cout<<"\n";
    return 0;
}