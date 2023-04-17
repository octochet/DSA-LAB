#include <iostream>
#include <vector>

using namespace std;

//stable quicksort
vector<int> stableDualPivotQuickSort(vector<int> arr, int low, int high)
{
    int n = high - low + 1;
    if(n <= 1)
    {
        return arr;
    }
    vector<int> left;
    vector<int> right;
    vector<int> middle;

    int pivot1 = arr[low];
    int pivot2 = arr[high];

    for(int i=1; i<n-1; i++)
    {
        if(arr[i] < pivot1)
        {
            left.push_back(arr[i]);
        }
        else if(arr[i] > pivot2)
        {
            right.push_back(arr[i]);
        }
        else
        {
            middle.push_back(arr[i]);
        }
    }

    vector<int> sorted;
    left = stableDualPivotQuickSort(left, 0, left.size()-1);
    sorted.insert(sorted.end(), left.begin(), left.end());
    sorted.push_back(pivot1);
    middle = stableDualPivotQuickSort(middle, 0, middle.size()-1);
    sorted.insert(sorted.end(), middle.begin(), middle.end());
    sorted.push_back(pivot2);
    right = stableDualPivotQuickSort(right, 0, right.size()-1);
    sorted.insert(sorted.end(), right.begin(), right.end());

    return sorted;
}


int main()
{
    vector<int> arr = {5, 2, 9, 3, 10, 43, 12, 4, 8};
    int n = arr.size();
    arr = stableDualPivotQuickSort(arr, 0, n-1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}
