#include "Sort.h"

void Print(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << ' ';
    }
    cout << endl;
}

int main()
{
    int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    Print(a, sizeof(a) / sizeof(a[0]));
    // InsertSort(a, sizeof(a) / sizeof(a[0]));
    // ShellSort(a, sizeof(a) / sizeof(a[0]));
    // SelectSort(a, sizeof(a) / sizeof(a[0]));
    // SelectSort_1(a, sizeof(a) / sizeof(a[0]));
    // HeapSort(a, sizeof(a) / sizeof(a[0]));
    // BubbleSort(a, sizeof(a) / sizeof(a[0]));
    // QuickSort(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    // QuickSortNonR(a, 0, sizeof(a) / sizeof(a[0]) - 1);
    // MergeSort(a, sizeof(a) / sizeof(a[0]));
    // MergeSortNonR(a, sizeof(a) / sizeof(a[0]));
    CountSort(a, sizeof(a) / sizeof(a[0]));

    Print(a, sizeof(a) / sizeof(a[0]));
    return 0;
}