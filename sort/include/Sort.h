#pragma once
#include <iostream>
#include <assert.h>
#include <string.h>

using namespace std;


//插入排序
void InsertSort(int *a, int n);
//希尔排序
void ShellSort(int *a, int n);
//选择排序
void SelectSort(int *a, int n);
//选择排序改进
void SelectSort_1(int *a, int n);
//堆排序
void AdjustDown(int *a, int n, int root);
void HeapSort(int *a, int n);
//冒泡排序
void BubbleSort(int *a, int n);
//快速排序
int PartSort1(int *a, int left, int right); //hoare版本
int PartSort2(int *a, int left, int right); //挖坑法
int PartSort3(int *a, int left, int right); //前后指针法
void QuickSort(int *a, int left, int right);
//快速排序非递归实现
void QuickSortNonR(int *a, int left, int right);
//归并排序递归实现
void MergeSort(int *a, int n);
//归并排序非递归实现
void MergeSortNonR(int *a, int n);

//文件排序自己有空记得学习

//计数排序
void CountSort(int *a, int n);