/*
 Red Black Tree Definition
*/

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    double weight;
    double cf;
    int color;
    Node *left, *right, *parent;

    explicit Node(int, double);
};

class RBTree
{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        void inorderBST(Node *&);
        void preorderBST(Node *&);
        void levelOrderBST(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* insertBST(Node *&, Node *&);
        Node* deleteBST(Node *&, int);
        int getBlackHeight(Node *);
        void alphaQuantileBST(Node *&, double, Node*&);
        void findCF(Node *, float&);
        void insert(Node *&, Node *);
        void fixInsert(Node *&, Node *);
        void updateCF(Node *);
        void rotateLeftx(Node *&, Node*);
        void rotateRightx(Node *&, Node*);
        void fixSuccessorCF(Node *);
        void predecessor(int);
        Node* predecessorBST(Node *&, int);
    public:
        RBTree();
        void insertValue(int, double);
        void deleteValue(int);
        void merge(RBTree);
        void inorder();
        void preorder();
        void levelOrder();
        void alphaQuantile(double);
        void precomputeCF();
};


#endif //RED_BLACK_TREE_RBTREE_H