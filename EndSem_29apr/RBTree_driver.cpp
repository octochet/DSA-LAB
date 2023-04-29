/* 
|-----Driver Program for alpha quantile using Red Black Tree-----|
|----------CHETAN MOTURI CS21B017--------|

algo:
1. insert all the values in the tree
2. while inserting, update the cf(cummulative frequency) of each successor node during fixup.
3. do a binary search to get the alpha quantile. Time Complexity: O(lg n).
*/
#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

int main() {
    int data;
    double prob;
    RBTree rbTree1, rbTree2;
/*--------TEST CASE 1----------------*/
    // rbTree1.insertValue(value, probability)
    rbTree1.insertValue(1,0.2);
    rbTree1.insertValue(2,0.08);
    rbTree1.insertValue(3,0.04);
    rbTree1.insertValue(4,0.12);
    rbTree1.insertValue(5,0.24);
    rbTree1.insertValue(7,0.12);
    rbTree1.insertValue(8,0.08);
    rbTree1.insertValue(9,0.12);

    cout<<"\n------IN ORDER------\n";
    rbTree1.inorder();
    cout<<"\n--------------------\n";

    // cout<<"------LEVEL ORDER------\n";
    // rbTree1.levelOrder();
    // cout<<"\n-------------------\n";

    rbTree1.alphaQuantile(0.33);
    rbTree1.alphaQuantile(0.65);
    rbTree1.alphaQuantile(0.50);
    rbTree1.alphaQuantile(0.75);
    rbTree1.alphaQuantile(0.85);
/*--------------TEST CASE 1 ENDS---------------*/

// /*--------------TEST CASE 2-------------------*/
//     rbTree2.insertValue(1,0.034483);
//     rbTree2.insertValue(2,0.241379);
//     rbTree2.insertValue(3,0.275862);
//     rbTree2.insertValue(4,0.137931);
//     rbTree2.insertValue(5,0.310345);

//     cout<<"\n------IN ORDER------\n";
//     rbTree2.inorder();
//     cout<<"\n--------------------\n";

//     /*
//     Sorted array with cf:
//     (1,0.034483)(2,0.275862)(3,0.551724)(4,0.689655)(5,1.000000)
//     */
//     rbTree2.alphaQuantile(1.00);

// /*--------TEST CASE 2 ENDS---------------------*/
    return 0;
}