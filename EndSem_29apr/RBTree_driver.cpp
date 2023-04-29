// Driver Program for Red Black Tree

#include <bits/stdc++.h>
#include "RBTree.h"
using namespace std;

int main() {
    int data;
    double prob;
    RBTree rbTree1;

    rbTree1.insertValue(1,0.1);
    rbTree1.insertValue(3,0.2);
    rbTree1.insertValue(4,0.1);
    rbTree1.insertValue(9,0.15);
    rbTree1.insertValue(2,0.05);
    rbTree1.insertValue(7,0.4);

    cout<<"------IN ORDER------\n";
    rbTree1.inorder();
    cout<<"\n-------------------\n";

    rbTree1.alphaQuantile(0.3);
    rbTree1.alphaQuantile(0.1);
    rbTree1.alphaQuantile(0.9);

    return 0;
}