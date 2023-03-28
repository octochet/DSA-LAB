#include<iostream>
#include<vector>

using namespace std;

//insertion sort function

void insertionSort(vector<int>& a, int left, int right) {
    for(int i = left + 1; i <= right; i++) {
        int tmp = a[i];
        int j = i;
        for(; j > left && tmp < a[j - 1]; j--) {
            a[j] = a[j - 1];
        }
        a[j] = tmp;
    }
}

//select function

int select(vector<int>& a, int left, int right, int k) {
    if(left + 10 <= right) {
        int pivot = medianOfMedians(a, left, right);
        int i = left, j = right - 1;
        for(;;) {
            while(a[++i] < pivot) {}
            while(a[--j] > pivot) {}
            if(i < j) {
                swap(a[i], a[j]);
            }
            else {
                break;
            }
        }
        swap(a[i], a[right - 1]);
        if(k <= i) {
            return select(a, left, i - 1, k);
        }
        else if(k > i + 1) {
            return select(a, i + 1, right, k);
        }
        else {
            return a[i];
        }
    }
    else {
        insertionSort(a, left, right);
        return a[k];
    }
}

//median of medians function

int medianOfMedians(vector<int>& a, int left, int right) {
    int numSublists = (right - left + 1 + 4) / 5;
    vector<int> medians(numSublists);
    for(int i = 0; i < numSublists; i++) {
        int begin = left + i * 5;
        int end = min(begin + 4, right);
        insertionSort(a, begin, end);
        medians[i] = a[begin + (end - begin) / 2];
    }
    return select(medians, 0, numSublists - 1, numSublists / 2);
}

//quickselect function

void quickSelect(vector<int>& a, int left, int right, int k) {
    if(left + 10 <= right) {
        int pivot = medianOfMedians(a, left, right);
        int i = left, j = right - 1;
        for(;;) {
            while(a[++i] < pivot) {}
            while(a[--j] > pivot) {}
            if(i < j) {
                swap(a[i], a[j]);
            }
            else {
                break;
            }
        }
        swap(a[i], a[right - 1]);
        if(k <= i) {
            quickSelect(a, left, i - 1, k);
        }
        else if(k > i + 1) {
            quickSelect(a, i + 1, right, k);
        }
    }
    else {
        insertionSort(a, left, right);
    }
}


//main function

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    quickSelect(a, 0, n - 1, k);
    for(int i = 0; i < k; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}