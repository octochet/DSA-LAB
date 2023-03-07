#include<iostream>

using namespace std;

void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;           //size of left subarray
    int n2 = right - mid;              //size of right subarray 
    int L[n1], R[n2];                  //temp arrays

    //copying data to temp arrays
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];          
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;        //initial index of first, second and merged subarray
    
    while (i < n1 && j < n2)           //merging temp arrays to main array
    {
        if (L[i] <= R[j])              //if left element is smaller than right element
        {
            arr[k] = L[i];             //copy left element to main array
            i++;
        }
        else
        {
            arr[k] = R[j];             //copy right element to main array
            j++;
        }
        k++;
    }

    //copying remaining elements of left subarray
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    //copying remaining elements of right subarray
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void bottomUp_merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;      //finding mid point
        bottomUp_merge_sort(arr, left, mid);               //sorting left subarray
        bottomUp_merge_sort(arr, mid + 1, right);          //sorting right subarray
        merge(arr, left, mid, right);             //merging left and right subarrays
    }
}

int main()
{
    int arr[] = { 12, 11, 13, 5, 6, 7, 8, 0, 24, 73, 64, 18, 17, 73, 62 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    bottomUp_merge_sort(arr, 0, arr_size - 1);
    for (int i = 0; i < arr_size; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}