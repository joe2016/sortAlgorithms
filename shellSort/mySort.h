
#pragma once


void swap(int &a, int &b);
void showArray(int num[], int len);
//²åÈëÅÅĞò
int shellSort(int num[], int start, int end);
int insertSort(int num[], int start, int end);
//¹é²¢ÅÅĞò
void merge(int num[], int start,int med,  int end);
void mergeSort1(int num[], int start, int end);
void mergeSort2(int num[], int start, int end);
void mergeSort3(int num[], int len);//×Ô¶¥ÏòÏÂµÄ¹é²¢ÅÅĞò
bool mergeSortInside(int num[], int numTmp[], int start, int end);
void merge2(int num[],int numTmp[], int start, int med, int end);

//¿ìËÙÅÅĞò
int patitionForQuickSort(int num[], int start, int end);
void quickSort(int num[], int start, int end);
void  quickSort2(int num[], int start, int end);


//¶ÑÅÅĞò
void heapSort(int num[], int start, int end);
void sinkForHeapSort(int num[], int pos, int start, int end);