/*
---Chetan Moturi----
a-quantile using rb tree:
algorithm:
1. insert the <element,weight> pairs in rb tree
2. do in order traversal
3. simulataneously calc cummulative frequency
4. if cf > alpha 
5. return the ans.
*/

#include <iostream>
#include "RBTree.h"

using namespace std;

int main() {
    int data;
    double prob;
    cout<<"Enter n:\n";
    int n;
    cin>>n;
    cout<< "Enter the data & probabilities:\n";
    RBTree tree;
    for(int i=0; i<n; i++) {
        cin>> data >> prob;
        tree.insertValue(data);
    }
    return 0;
}