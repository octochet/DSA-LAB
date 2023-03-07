#include <iostream>
#include <vector>

using namespace std;

//dual pivot stable quicksort

void dual_pivot_quicksort(int *arr, int left, int right)
{
    if (left < right)
    {
        int pivot1 = arr[left];
        int pivot2 = arr[right];
        if (pivot1 > pivot2)
        {
            int temp = pivot1;
            pivot1 = pivot2;
            pivot2 = temp;
        }
        int i = left + 1;
        int j = right - 1;
        int k = i;
        while (k <= j)
        {
            if (arr[k] < pivot1)
            {
                int temp = arr[i];
                arr[i] = arr[k];
                arr[k] = temp;
                i++;
                k++;
            }
            else if (arr[k] >= pivot1 && arr[k] <= pivot2)
            {
                k++;
            }
            else
            {
                int temp = arr[j];
                arr[j] = arr[k];
                arr[k] = temp;
                j--;
            }
        }
        i--;
        j++;
        arr[left] = arr[i];
        arr[i] = pivot1;
        arr[right] = arr[j];
        arr[j] = pivot2;
        dual_pivot_quicksort(arr, left, i - 1);
        dual_pivot_quicksort(arr, i + 1, j - 1);
        dual_pivot_quicksort(arr, j + 1, right);
    }
}

void vector_sort(vector<pair<int,int>>& v, int left, int right)
{
    if (left < right)
    {
        int pivot1 = v[left].first;
        int pivot2 = v[right].first;
        if (pivot1 > pivot2)
        {
            int temp = pivot1;
            pivot1 = pivot2;
            pivot2 = temp;
        }
        int i = left + 1;
        int j = right - 1;
        int k = i;
        while (k <= j)
        {
            if (v[k].first < pivot1)
            {
                pair<int,int> temp = v[i];
                v[i] = v[k];
                v[k] = temp;
                i++;
                k++;
            }
            else if (v[k].first >= pivot1 && v[k].first <= pivot2)
            {
                k++;
            }
            else
            {
                pair<int,int> temp = v[j];
                v[j] = v[k];
                v[k] = temp;
                j--;
            }
        }
        i--;
        j++;
        v[left] = v[i];
        v[i].first = pivot1;
        v[right] = v[j];
        v[j].first = pivot2;
        vector_sort(v, left, i - 1);
        vector_sort(v, i + 1, j - 1);
        vector_sort(v, j + 1, right);
    }
}

int main()
{
    int arr[] = { 5, 3, 8, 4, 2, 7, 1, 10, 5 };
    int n = sizeof(arr) / sizeof(arr[0]);
    dual_pivot_quicksort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout<<endl;
    vector<pair<int, int>> v = { {6, 1}, {5, 5}, {3, 1}, {5, 2}, {7, 1}, {10, 9}, {5, 7} };
    vector_sort(v, 0, v.size() - 1);
    for (int i = 0; i < v.size(); i++)
    {
        cout <<"{" <<v[i].first << "," << v[i].second<<"} ";
    }
    return 0;
}
