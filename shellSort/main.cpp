#include "stdafx.h"
#include <iostream>
#include "mySort.h"
#include "sortForList.h"
#include <time.h>
#include <Windows.h>
using namespace std;
inline unsigned __int64 GetCycleCount()
{
 __asm _emit 0x0F
 __asm _emit 0x31
}

  
//test github
//test 2

void generateNumbers(int a[], int len)
{
	//srand((int)clock());
	for(int i=0;i<len;i++)
	{
		a[i]=rand()%100;
	}
}

void copyArray(int in[], int out[], int len)
{
		for(int i=0;i<len;i++)
	{
		out[i]=in[i];
	}
}
#define myLen 10
int _tmain(int argc, _TCHAR* argv[])
{

	srand((int)clock());
	unsigned long dwStartTime, dwEndTime,dwRunTime  = 0;
	long i=100000;
	int j=6000;
//	int origNum[]={14,36,2,4,1,6,7,9,8,13,68,45,33,76,98,24,31,90};
	int origNum[myLen];
	int origNum2[myLen];
//	generateNumbers(origNum,len);
/*
	int origNum2[1]={0};
	int len2=sizeof(origNum2)/sizeof(int);
//	showArray(origNum, len);
	cout<<endl<<"insertSort:";
	dwStartTime = GetCycleCount(  );
	insertSort(origNum,0,len-1);
	dwEndTime = GetCycleCount(  );
	dwRunTime = (dwEndTime - dwStartTime)/1000 ; 
	cout<<dwRunTime<<endl;
*/
	

	LONGLONG begin_time;
	LONGLONG end_time;
	double time_fre;
	double time_elapsed;
	LARGE_INTEGER litmp;

	QueryPerformanceFrequency(&litmp);
	time_fre = (double)litmp.QuadPart;
	

	generateNumbers(origNum2,myLen);
	//////////////////////
	copyArray(origNum2, origNum, myLen);
	cout<<endl<<"shellSort:";
//	showArray(origNum, myLen);
	QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	shellSort(origNum,2, myLen-1);
//	showArray(origNum, myLen);

	QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
	time_elapsed = (end_time - begin_time) / time_fre;
	cout.precision(20);
	cout<<"time elapsed:"<<time_elapsed<<endl;

	//////////////////////////////////////
	cout<<endl<<"mergeSort1:";
	copyArray(origNum2, origNum, myLen);

	QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	mergeSort1(origNum,0,myLen-1);

	QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
	time_elapsed = (end_time - begin_time) / time_fre;
	cout.precision(20);
	cout<<"time elapsed:"<<time_elapsed<<endl;


	//////////////////////
	copyArray(origNum2, origNum, myLen);
	cout<<endl<<"mergeSort3:";

	QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	mergeSort3(origNum, myLen);

	QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
	time_elapsed = (end_time - begin_time) / time_fre;
	cout.precision(20);
	cout<<"time elapsed:"<<time_elapsed<<endl;
	////////////////////////
	copyArray(origNum2, origNum, myLen);
	cout<<endl<<"quickSort:";

	QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	quickSort(origNum,0,myLen-1);

	QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
	time_elapsed = (end_time - begin_time) / time_fre;
	cout.precision(20);
	cout<<"time elapsed:"<<time_elapsed<<endl;

	//////////////////////

	copyArray(origNum2, origNum, myLen);
	
	cout<<"quickSort2:";
	QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	quickSort2(origNum, 0, myLen-1);
	QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
	time_elapsed = (end_time - begin_time) / time_fre;
	cout.precision(20);
	cout<<"time elapsed:"<<time_elapsed<<endl;


	copyArray(origNum2, origNum, myLen);
	myNode* res = makeListByArray(origNum,myLen);
	showList(res);
	quickSortForList(res);
	cout<<"afte sort:"<<endl;
	showList(res);
	deleteList(res);

	char end;
	cin>>end;
	return 0;
}
