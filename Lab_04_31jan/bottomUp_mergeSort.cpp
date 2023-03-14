#include <iostream>

using namespace std;

void merge(int *arr, int *temp, int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = left;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= right)
    {
        temp[k++] = arr[j++];
    }
    for (int i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
}

void bottomUp_merge_sort(int *arr, int temp[], int left, int right)
{
    int mid;
    for (int i = 1; i <= right - left; i = 2 * i)
    {
        for (int j = left; j < right; j += 2 * i)
        {
            mid = j + i - 1;
            int end = min(j + 2 * i - 1, right);
            merge(arr, temp, j, mid, end);
        }
    }
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7, 8, 0, 24, 73, 64, 18, 17, 73, 62};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int temp[arr_size];
    bottomUp_merge_sort(arr, temp, 0, arr_size - 1);
    for (int i = 0; i < arr_size; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}