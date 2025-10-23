#include "Sort.h"
#include "Stack.h"

//交换两个数
void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
//三数取中
int GetMidIndex(int *a, int left, int right)
{
    int mid = (left + right) / 2;
    if (a[left] < a[mid])
    {
        if (a[mid] < a[right])
            return mid;
        else if (a[right] < a[left])
            return left;
        else
            return right;
    }
    else
    {
        if (a[right] < a[mid])
            return mid;
        else if (a[left] < a[right])
            return left;
        else
            return right;
    }
}

//插入排序
void InsertSort(int *a, int n)
{
    assert(a);
    for (int i = 0; i < n - 1; i++)
    {
        int end = i;
        int tmp = a[end + 1];
        while(end >= 0)
        {
            if (a[end] > tmp)
            {
                a[end + 1] = a[end];
                end--;
            }
            else
            {
                break;
            }
        }
        a[end + 1] = tmp;
    }
}

//希尔排序
void ShellSort(int *a, int n)
{
    int gap = n;
    while(gap > 1)
    {
        gap = gap / 3 + 1;
        for (int end = 0; end <= n - 1 - gap; end++)
        {
            int tmp = a[end + gap];
            while(end >= 0)
            {
                if (a[end] > tmp)
                {
                    a[end + gap] = a[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            a[end + gap] = tmp;
        }
    }
}

//选择排序
void SelectSort(int *a, int n)
{
    assert(a);
    for (int i = 0; i < n - 1; i++)
    {
        int min = a[i];
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < min)
            {
                min = a[j];
                minIndex = j;
            }
        }
        Swap(&a[i], &a[minIndex]);
    }
}
//选择排序改进
void SelectSort_1(int *a, int n)
{
    assert(a);
    int head = 0;
    int tail = n - 1;
    while(head < tail)
    {
        int min = head;
        int max = head;

        for (int i = head + 1; i <= tail; i++)
        {
            if (a[i] < a[min])
            {
                min = i;
            }
            if (a[i] > a[max])
            {
                max = i;
            }
        }
        Swap(&a[head], &a[min]);
        if (max == head)
            max = min;
        Swap(&a[max], &a[tail]);
        head++;
        tail--;
    }
}

//堆排序,建大堆
void AdjustDown(int *a, int n, int root)
{
    int parent = root;
    int child = 2 * parent + 1;
    while(child < n)
    {
        if (child + 1 < n && a[child] < a[child + 1])
        {
            child++;
        }

        if (a[parent] < a[child])
        {
            Swap(&a[parent], &a[child]);
            parent = child;
            child = 2 * parent + 1;
        }
        else
        {
            break;
        }
    }
}
void HeapSort(int *a, int n)
{
    for (int i = (n - 1 - 1) / 2; i >= 0; i--)
    {
        AdjustDown(a, n, i);
    }

    for (int end = n - 1; end > 0; end--)
    {
        Swap(&a[0], &a[end]);
        AdjustDown(a, end, 0);
    }
}

//冒泡排序
void BubbleSort(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int tar = 0;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                Swap(&a[j], &a[j + 1]);
                tar = 1;
            }
        }
        if (tar == 0)
            break;
    }
}

//快速排序
int PartSort1(int *a, int left, int right)
{
    int mid = GetMidIndex(a, left, right);
    Swap(&a[mid], &a[right]);
    int key = a[right];
    int keyIndex = right;
    while(left < right)
    {
        while(left < right && a[left] <= key)
        {
            left++;
        }
        while(left < right && key <= a[right])
        {
            right--;
        }
        Swap(&a[left], &a[right]);
    }
    Swap(&a[left], &a[keyIndex]);
    return left;
}
int PartSort2(int *a, int left, int right)
{
    int mid = GetMidIndex(a, left, right);
    Swap(&a[mid], &a[right]);
    int key = a[right];
    while(left < right)
    {
        while(left < right && a[left] <= key)
        {
            left++;
        }
        a[right] = a[left];
        while(left < right && key <= a[right])
        {
            right--;
        }
        a[left] = a[right];
    }
    a[left] = key;
    return left;
}
int PartSort3(int *a, int left, int right)
{
    int mid = GetMidIndex(a, left, right);
    Swap(&a[mid], &a[right]);
    int key = a[right];

    int cur = left;
    int prev = left - 1;
    while(cur <= right)
    {
        if (a[cur] <= key)
        {
            prev++;
            Swap(&a[prev], &a[cur]);
        }
        cur++;
    }

    return prev;
}
void QuickSort(int *a, int left, int right)
{
    if (left >= right)
        return;
    if (right - left + 1 <= 10)
    {
        InsertSort(a + left, right - left + 1);
        return;
    }
    int div = PartSort3(a, left, right);
    QuickSort(a, left, div - 1);
    QuickSort(a, div + 1, right);
}

//快速排序非递归实现
void QuickSortNonR(int *a, int left, int right)
{
    Stack st;
    StackInit(&st);

    StackPush(&st, right);
    StackPush(&st, left);

    while(!StackEmpty(&st))
    {
        int begin = StackTop(&st);
        StackPop(&st);
        int end = StackTop(&st);
        StackPop(&st);

        int div = PartSort3(a, begin, end);
        if (div + 1 < end)
        {
            StackPush(&st, end);
            StackPush(&st, div + 1);
        }
        if (begin < div - 1)
        {
            StackPush(&st, div - 1);
            StackPush(&st, begin);
        }
    }
    StackDestory(&st);
}


// void QuickSortNonR(int *a, int left, int right)
// {
//     assert(a);
//     Stack st;
//     StackInit(&st);

//     StackPush(&st, right);
//     StackPush(&st, left);

//     while(!StackEmpty(&st))
//     {
//         int begin = StackTop(&st);
//         StackPop(&st);
//         int end = StackTop(&st);
//         StackPop(&st);

//         int div = PartSort3(a, begin, end);
//         if (div + 1 < end)
//         {
//             StackPush(&st, end);
//             StackPush(&st, div + 1);
//         }
//         if (begin < div - 1)
//         {
//             StackPush(&st, div - 1);
//             StackPush(&st, begin);
//         }
//     }
//     StackDestory(&st);
// }

void _MergeSort(int *a, int left, int right, int *tmp)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    _MergeSort(a, left, mid, tmp);
    _MergeSort(a, mid + 1, right, tmp);

    //归并[left, mid] [mid + 1, right]有序
    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;
    int index = begin1;
    while(begin1 <= end1 && begin2 <= end2)
    {
        if (a[begin1] < a[begin2])
        {
            tmp[index++] = a[begin1++];
        }
        else
        {
            tmp[index++] = a[begin2++];
        }
    }
    while(begin1 <= end1)
    {
        tmp[index++] = a[begin1++];
    }
    while(begin2 <= end2)
    {
        tmp[index++] = a[begin2++];
    }
    for (int i = left; i <= right; i++)
    {
        a[i] = tmp[i];
    }
}

//归并排序递归实现
void MergeSort(int *a, int n)
{
    assert(a);
    int *tmp = (int*)malloc(sizeof(int) * n);
    _MergeSort(a, 0, n - 1, tmp);
    free(tmp);
}

void MergeArr(int *a, int begin1, int end1, int begin2, int end2, int *tmp)
{
    int left = begin1, right = end2;
    int index = begin1;
    while(begin1 <= end1 && begin2 <= end2)
    {
        if (a[begin1] < a[begin2])
            tmp[index++] = a[begin1++];
        else
            tmp[index++] = a[begin2++];
    }

    while(begin1 <= end1)
    {
        tmp[index++] = a[begin1++];
    }
    while(begin2 <= end2)
    {
        tmp[index++] = a[begin2++];
    }

    for (int i = left; i <= right; i++)
    {
        a[i] = tmp[i];
    }
}

//归并排序非递归实现
void MergeSortNonR(int *a, int n)
{
    assert(a);
    int *tmp = (int*)malloc(sizeof(int) * n);
    int gap = 1;
    while(gap < n)
    {
        for (int i = 0; i < n; i += 2 * gap)
        {
            int begin1 = i, end1 = i + gap - 1;
            int begin2 = i + gap, end2 = i + 2 * gap - 1;
            if (begin2 >= n)
                break;
            if (end2 >= n)
                end2 = n - 1;
            MergeArr(a, begin1, end1, begin2, end2, tmp);
        }
        gap *= 2;
    }

    free(tmp);
}

//计数排序
void CountSort(int *a, int n)
{
    assert(a);
    int min = a[0];
    int max = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] < min)
            min = a[i];
        if (a[i] > max)
            max = a[i];
    }

    int *tmp = (int*)malloc(sizeof(int) * (max - min + 1));
    memset(tmp, 0, sizeof(int) * (max - min + 1));

    for (int i = 0; i < n; i++)
    {
        (*(tmp + a[i] - min))++;
    }

    int index = 0;
    for (int i = 0; i < max - min + 1; i++)
    {
        for (int j = 0; j < tmp[i]; j++)
        {
            a[index] = i + min;
            index++;
        }
    }

    free(tmp);
}