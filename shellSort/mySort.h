
#pragma once


void swap(int &a, int &b);
void showArray(int num[], int len);
//插入排序
int shellSort(int num[], int start, int end);
int insertSort(int num[], int start, int end);
//归并排序
void merge(int num[], int start,int med,  int end);
void mergeSort1(int num[], int start, int end);
void mergeSort2(int num[], int start, int end);
void mergeSort3(int num[], int len);//自顶向下的归并排序
bool mergeSortInside(int num[], int numTmp[], int start, int end);
void merge2(int num[],int numTmp[], int start, int med, int end);

//快速排序
int patitionForQuickSort(int num[], int start, int end);
void quickSort(int num[], int start, int end);
void  quickSort2(int num[], int start, int end);