#include <iostream>
#include <queue>

using namespace std;

template <typename Comparable>
class BinarySearchTree
{
public:
    // Constructor
    BinarySearchTree() {
        root = NULL;
    }

    // Copy constructor
    BinarySearchTree(const BinarySearchTree & rhs) {
        root = NULL;
        *this = rhs;
    }

    // Destructor
    ~BinarySearchTree(){
        makeEmpty();
    }

    // Public methods
    void makeEmpty(){
        makeEmpty(root);
    }

    // Insert x into the tree; duplicates are ignored.
    void insert(const Comparable & x){
        insert(x, root);
    }

    // Insert elements from an inorder and postorder sequence.
    void insertFromInPost(const Comparable in[], const Comparable post[], int n){
        insertFromInPost(in, post, n, root);
    }

    // Remove x from the tree. Nothing is done if x is not found.
    void remove(const Comparable & x){
        remove(x, root);
    }

    // Search for x.
    bool search(const Comparable & x) const{
        return search(x, root);
    }

    // Return the number of nodes in the tree.
    int size(){
        return size(root);
    }

    // Print the tree contents in preorder.
    void preOrder(){
        preOrder(root);
    }

    // Print the tree contents in inorder.
    void inOrder(){
        inOrder(root);
    }

    void inOrder2(){
        inOrder2(root);
    }

    // Print the tree contents in postorder.
    void postOrder(){
        postOrder(root);
    }
    
    // Print the tree contents in level order.
    void levelOrder(){
        levelOrder(root);
    }

    // Return the minimum item in the tree.
    Comparable findMin() const{
        return findMin(root)->element;
    }

    // Return the maximum item in the tree.
    Comparable findMax() const{
        return findMax(root)->element;
    }

    // check if the tree is a BST
    bool isBST(){
        return isBST(root);
    }

    // find the predecessor of x
    Comparable predecessor(const Comparable & x){
        return predecessor(x, root);
    }

    // find the successor of x
    Comparable successor(const Comparable & x){
        return successor(x, root);
    }

    // find the kth smallest element
    Comparable select(int k){
        return select(k, root);
    }

    // find diameter of the tree; max number of nodes on a path between two leaves
    int diameter(){
        return diameter(root);
    }

    // find height of the tree; max number of nodes on a path from root to a leaf
    int height(){
        return height(root);
    }

    // find the lowest common ancestor of x and y
    Comparable lca(const Comparable & x, const Comparable & y){
        return lca(x, y, root);
    }

    // find the maximum path sum
    int maxPathSum(){
        return maxPathSum(root);
    }

    // operator overloading
    const BinarySearchTree & operator=(const BinarySearchTree & rhs){
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

private:
    // node structure
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
            : element(theElement), left(lt), right(rt) { }
    };

    // root of the tree
    BinaryNode *root;

    // insert definition
    void insert(const Comparable & x, BinaryNode * & t){
        if (t == NULL)
            t = new BinaryNode(x, NULL, NULL);
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ;  // Duplicate; do nothing
    }

    // insert from inorder and postorder sequence definition
    void insertFromInPost(const Comparable in[], const Comparable post[], int n, BinaryNode * & t){
        if (n == 0)
            return;
        t = new BinaryNode(post[n - 1], NULL, NULL);
        int i = 0;
        while (in[i] != post[n - 1])
            i++;
        insertFromInPost(in, post, i, t->left);
        insertFromInPost(in + i + 1, post + i, n - i - 1, t->right);
    }

    // remove definition
    void remove(const Comparable & x, BinaryNode * & t){
        if (t == NULL)
            return;   // Item not found; do nothing
        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != NULL && t->right != NULL) // Two children
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode *oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
        }
    }

    // search definition
    bool search(const Comparable & x, BinaryNode *t) const{
        if (t == NULL)
            return false;
        else if (x < t->element)
            return search(x, t->left);
        else if (x > t->element)
            return search(x, t->right);
        else
            return true;    // Match
    }

    // preorder definition
    void preOrder(BinaryNode *t){
        if (t == NULL)
            return;
        cout << t->element << " ";
        preOrder(t->left);
        preOrder(t->right);
    }

    // inorder definition
    void inOrder(BinaryNode *t){
        if (t == NULL)
            return;
        inOrder(t->left);
        cout << t->element << " ";
        inOrder(t->right);
    }

    //inorder without recursion/stack and using constant space
    void inOrder2(BinaryNode *t){
        BinaryNode *p = t; // p is the current node
        while (p != NULL) // while p is not NULL
        {
            if (p->left == NULL)   // if p has no left child
            {
                cout << p->element << " "; // print p
                p = p->right; // move to p's right child
            }
            else
            {
                BinaryNode *q = p->left;  // q is p's left child
                while (q->right != NULL && q->right != p) // find p's inorder predecessor
                    q = q->right;   // q is p's inorder predecessor
                if (q->right == NULL)   // if q's right child is NULL
                {
                    q->right = p;   // make q's right child point to p
                    p = p->left;    // move to p's left child
                }
                else
                {
                    q->right = NULL;    // restore q's right child
                    cout << p->element << " ";  // print p
                    p = p->right;   // move to p's right child
                }
            }
        }
    }

    // postorder definition
    void postOrder(BinaryNode *t){
        if (t == NULL)
            return;
        postOrder(t->left);
        postOrder(t->right);
        cout << t->element << " ";
    }

    // level order definition
    void levelOrder(BinaryNode *t){
        if (t == NULL)
            return;
        queue<BinaryNode *> q;
        q.push(t);
        while (!q.empty())
        {
            BinaryNode *p = q.front();
            q.pop();
            cout << p->element << " ";
            if (p->left != NULL)
                q.push(p->left);
            if (p->right != NULL)
                q.push(p->right);
        }
    }

    // find minimum definition
    BinaryNode * findMin(BinaryNode *t) const{
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);
    }

    // find maximum definition
    BinaryNode * findMax(BinaryNode *t) const{
        if (t != NULL)
            while (t->right != NULL)
                t = t->right;
        return t;
    }

    // isBST optimized recursive solution  
    bool isBST(BinaryNode *t){
        if(t == nullptr) {
            return true;
        } 
    }

    // predecessor definition
    Comparable predecessor(const Comparable & x, BinaryNode *t){
        if (t == NULL)
            return -1;
        if (x <= t->element)
            return predecessor(x, t->left);
        else
        {
            Comparable p = predecessor(x, t->right);
            if (p == -1)
                return t->element;
            else
                return p;
        }
    }

    // successor definition
    Comparable successor(const Comparable & x, BinaryNode *t){
        if (t == NULL)
            return -1;
        if (x >= t->element)
            return successor(x, t->right);
        else
        {
            Comparable s = successor(x, t->left);
            if (s == -1)
                return t->element;
            else
                return s;
        }
    }

    // size definition    
    int size(BinaryNode *t){
        if (t == NULL)
            return 0;
        return 1 + size(t->left) + size(t->right);
    }

    // select definition
    Comparable select(int k, BinaryNode *t){
        if (t == NULL)
            return -1;
        int leftSize = size(t->left);
        if (leftSize == k - 1)
            return t->element;
        else if (leftSize > k - 1)
            return select(k, t->left);
        else
            return select(k - leftSize - 1, t->right);
    }

    // height definition
    int height(BinaryNode *t){
        if (t == NULL)
            return 0;
        return 1 + max(height(t->left), height(t->right));
    }

    // diameter definition
    int diameter(BinaryNode *t){
        if (t == NULL)
            return 0;
        int leftHeight = height(t->left);
        int rightHeight = height(t->right);
        int leftDiameter = diameter(t->left);
        int rightDiameter = diameter(t->right);
        return max(leftHeight + rightHeight + 1, max(leftDiameter, rightDiameter));
    }

    // lca definition
    Comparable lca(const Comparable & x, const Comparable & y, BinaryNode *t){
        if (t == NULL)
            return -1;
        if (x < t->element && y < t->element)
            return lca(x, y, t->left);
        else if (x > t->element && y > t->element)
            return lca(x, y, t->right);
        else
            return t->element;
    }

    // maxPath definition
    int maxPath(BinaryNode *t){
        if (t == NULL)
            return 0;
        return t->element + max(0, max(maxPath(t->left), maxPath(t->right)));
    }

    // maxPathSum definition
    int maxPathSum(BinaryNode *t){
        if (t == NULL)
            return 0;
        int leftMax = maxPathSum(t->left);
        int rightMax = maxPathSum(t->right);
        int leftMaxPath = maxPath(t->left);
        int rightMaxPath = maxPath(t->right);
        return max(leftMax, max(rightMax, leftMaxPath + rightMaxPath + t->element));
    }


    BinaryNode * clone(BinaryNode *t) const{
        if (t == NULL)
            return NULL;
        else
            return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }


    void makeEmpty(BinaryNode * & t){
        if (t != NULL)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = NULL;
    }
};

int main()
{
    BinarySearchTree<int> t;

    //q1
    int in[] = { 1, 2, 3, 4, 5, 6, 7 };
    int post[] = {1, 3, 2, 5, 7, 6, 4};
    t.insertFromInPost(in, post, 7);
    t.levelOrder();cout<<endl;

    //q2
    t.remove(4);
    t.levelOrder();cout<<endl;

    //q3
    cout<<"Search 4:"<<t.search(4)<<endl;
    cout<<"Search 5:"<<t.search(5)<<endl;

    //q4
    cout<<"inorder: ";t.inOrder();cout<<endl;
    cout<<"inorder2: ";t.inOrder2();cout<<endl;
    cout<<"postorder: ";t.postOrder();cout<<endl;
    cout<<"preorder: ";t.preOrder();cout<<endl;

    //q5
    cout<<"levelorder: ";t.levelOrder();cout<<endl;

    //q6
    cout<<"is t a BST? "<<t.isBST()<<endl;

    //q7
    cout<<"predecessor of 5: "<<t.predecessor(5)<<endl;

    //q8
    cout<<"successor of 3: "<<t.successor(3)<<endl;

    //q9
    cout<<"4th smallest element: "<<t.select(4)<<endl;

    //q10
    cout<<"diameter of t2: "<<t.diameter()<<endl;

    //q11
    cout<<"height of t2: "<<t.height()<<endl;

    //q12
    cout<<"lca of 1 and 3: "<<t.lca(1, 3)<<endl;

    //q13
    cout<<"max path sum of t2: "<<t.maxPathSum()<<endl;
    return 0;
}
