
#pragma once


void swap(int &a, int &b);
void showArray(int num[], int len);
//��������
int shellSort(int num[], int start, int end);
int insertSort(int num[], int start, int end);
//�鲢����
void merge(int num[], int start,int med,  int end);
void mergeSort1(int num[], int start, int end);
void mergeSort2(int num[], int start, int end);
void mergeSort3(int num[], int len);//�Զ����µĹ鲢����
bool mergeSortInside(int num[], int numTmp[], int start, int end);
void merge2(int num[],int numTmp[], int start, int med, int end);

//��������
int patitionForQuickSort(int num[], int start, int end);
void quickSort(int num[], int start, int end);
void  quickSort2(int num[], int start, int end);