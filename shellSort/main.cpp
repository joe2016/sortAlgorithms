#include "stdafx.h"
#include <iostream>
#include "mySort.h"
#include "sortForList.h"
#include <time.h>
#include <Windows.h>
#include "myHeap.h"
#include "myTree.h"


using namespace std;
inline unsigned __int64 GetCycleCount()
{
 __asm _emit 0x0F
 __asm _emit 0x31
}

  
//test github
//test 2
//new branch
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
#define myLen 5
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

	//////////////////////////////////////
	cout<<endl<<"mergeSort1:";
	copyArray(origNum2, origNum, myLen);

	QueryPerformanceCounter((LARGE_INTEGER *)&begin_time);
	mergeSort1(origNum,0,myLen-1);

	QueryPerformanceCounter((LARGE_INTEGER *)&end_time);
	time_elapsed = (end_time - begin_time) / time_fre;
	cout.precision(20);
	cout<<"time elapsed:"<<time_elapsed<<endl;

/////////////////////////////////////////////////
	
	copyArray(origNum2, origNum, myLen);
	cout<<"BST test:"<<endl;
	showArray(origNum2, myLen);

	auto myBST=new BST();
	for(int i=0;i<myLen;i++)
	{
		myBST->put(origNum2[i], i);
	}

	myBST->deleteNode(origNum2[2]);
	myBST->put(origNum2[2],2);


	myBST->inorder();

	cout<<"get() test"<<endl;
	for(int i=0; i<myLen;i++)
		cout<<myBST->get(origNum2[i])->_val<<" ";
	cout<<endl;

	cout<<"select() test"<<endl;
	for(int i=0; i<myLen;i++)
		cout<<myBST->select(i+1)->_key<<" ";
	cout<<endl;

	cout<<"rank() test"<<endl;
	for(int i=0; i<myLen;i++)
		cout<<myBST->rank(origNum2[i])<<" ";
	cout<<endl;

	cout<<"floor() test"<<endl;
	cout<<myBST->floor(20)<<" ";
	cout<<endl;


	char end;
	cin>>end;
}
