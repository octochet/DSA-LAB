#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Define a struct to represent vertical and horizontal lines
struct VerticalLine {
    int x, y1, y2;
};

struct HorizontalLine {
    int y, x1, x2;
};

// Define a struct to represent a node in the AVL tree
struct Node {
    HorizontalLine line;
    int height;
    Node* left;
    Node* right;
};

// Define a function to calculate the height of a node
int height(Node* node) {
    return node == nullptr ? -1 : node->height;
}

// Define a function to calculate the balance factor of a node
int balanceFactor(Node* node) {
    return node == nullptr ? 0 : height(node->left) - height(node->right);
}

// Define a function to rotate a subtree to the left
Node* rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

// Define a function to rotate a subtree to the right
Node* rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    newRoot->height = max(height(newRoot->left), height(newRoot->right)) + 1;
    return newRoot;
}

// Define a function to balance a node
Node* balance(Node* node) {
    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        node = rotateRight(node);
    } else if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
    }
    return node;
}

// Define a function to insert a horizontal line into the AVL tree
Node* insert(Node* root, const HorizontalLine& line) {
    if (root == nullptr) {
        root = new Node{line, 0, nullptr, nullptr};
    } else if (line.y < root->line.y) {
        root->left = insert(root->left, line);
    } else {
        root->right = insert(root->right, line);
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    return balance(root);
}

// Define the AVL tree
Node* activeLines = nullptr;

// Define the line sweep algorithm
set<pair<int, int>> findIntersections(const vector<VerticalLine>& verticalLines,
                                       const vector<HorizontalLine>& horizontalLines) {
    // Process each vertical line in order
    set<pair<int, int>> intersections;
    for (const auto& vl : verticalLines) {
        // Add any intersecting horizontal lines to the AVL tree
        for (const auto& hl : horizontalLines) {
            if (hl.y >= vl.y1 && hl.y <= vl.y2 && hl.x1 <= vl.x) {
                activeLines = insert(activeLines, hl);
            }
        }

        // Remove any non-intersecting horizontal lines from the AVL tree
        for (auto it = activeLines; it != nullptr;) {
            const auto& hl = it->line;
            if (hl.y > vl.y2) {
                break;
            }
            if (hl.y >= vl.y1 && hl.y <= vl.y2 && hl.x2 >= vl.x) {
                intersections.insert({vl.x, hl.y});
            }
            it = it->right;
        }

        // Find any intersections between the active horizontal lines and the vertical line
        for (auto it = activeLines; it != nullptr; it = it->right) {
            const auto& hl = it->line;
            if (hl.y > vl.y2) {
                break;
            }
            if (hl.y >= vl.y1 && hl.y <= vl.y2 && hl.x2 >= vl.x) {
                intersections.insert({vl.x, hl.y});
            }
        }
    }
    return intersections;
}

// Example usage:
int main() {
    vector<VerticalLine> verticalLines = {{1, 1, 5}, {3, 2, 6}, {5, 4, 8}};
    vector<HorizontalLine> horizontalLines = {{2, 0, 4}, {4, 1, 5}, {7, 3, 6}};
    set<pair<int, int>> intersections = findIntersections(verticalLines, horizontalLines);
    for (const auto& p : intersections) {
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    return 0;
}
           
