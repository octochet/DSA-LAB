#include<iostream>

using namespace std;
    

//α-Quantile select
/*
give an algorithm to find the α-quantile of a set of n numbers in O(n) time
given that the numbers are stored in an array A[1..n]
their respective probabilitiy weights are stored in an array W[1..n]
and the sum of the weights is 1
alpha is the quantile to be found
solve the problem by modifying SELECT algorithm
*/

//select function
int select(int A[], int W[], int p, int r, int alpha) {
    if (p == r) {   //if p is equal to r
        return A[p];    //return A[p]
    }
    int q = partition(A, W, p, r);   //call partition function
    int k = q - p + 1;  //calculate k
    if (alpha == k) {   //if alpha is equal to k
        return A[q];    //return A[q]
    }
    else if (alpha < k) {   //if alpha is less than k
        return select(A, W, p, q - 1, alpha);    //return select function
    }
    else {  //if alpha is greater than k
        return select(A, W, q + 1, r, alpha - k);   //return select function
    }
}

//partition function
int partition(int A[], int W[], int p, int r) {
    int x = A[r];   //assign A[r] to x
    int i = p - 1;  //assign p - 1 to i
    for (int j = p; j <= r - 1; j++) {  //traverse the array
        if (A[j] <= x) {    //if A[j] is less than or equal to x
            i++;    //increment i
            swap(A[i], A[j]);   //swap A[i] and A[j]
            swap(W[i], W[j]);   //swap W[i] and W[j]
        }
    }
    swap(A[i + 1], A[r]);   //swap A[i + 1] and A[r]
    swap(W[i + 1], W[r]);   //swap W[i + 1] and W[r]
    return i + 1;   //return i + 1
}

//main function
int main() {
    int n;  //declare n
    cout << "Enter the number of elements: ";    //print message
    cin >> n;   //input n
    int A[n];   //declare array A
    int W[n];   //declare array W
    cout << "Enter the elements: "; //print message
    for (int i = 0; i < n; i++) {   //traverse the array
        cin >> A[i];    //input A[i]
    }
    cout << "Enter the weights: ";  //print message
    for (int i = 0; i < n; i++) {   //traverse the array
        cin >> W[i];    //input W[i]
    }
    int alpha;  //declare alpha
    cout << "Enter the quantile: "; //print message
    cin >> alpha;   //input alpha
    cout << "The " << alpha << "-quantile is: " << select(A, W, 0, n - 1, alpha) << endl; //print message
    return 0;   //return 0
}

