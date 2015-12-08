
#include "stdafx.h"
#include "mySort.h"
#include <iostream>
using namespace std;


inline void swap(int &a, int &b)
{
	int tmp=a;
	a=b;
	b=tmp;
}

void showArray(int num[], int len)
{
	
	for(int i=0;i<len;i++)
	{
		cout<<num[i]<<", ";
	}
}

int shellSort(int num[], int start, int end)//希尔排序
{
	int len=end-start+1;
	int swapCount=0;
	for(int gap=len/2;gap>=1;gap/=2)
		for(int i=start+gap;i<=end;i++)
			for(int j=i;(j>=start+gap)&&num[j]<num[j-gap];j=j-gap)
			{
				swap(num[j],num[j-gap]);
				swapCount++;
			}
	return swapCount;		
}

int insertSort(int num[], int start, int end)//插入排序
{
	if(end<start) return -1;
	int swapCount=0;//记录交换次数
	for(int i=start+1;i<=end;i++)
		for(int j=i;j>start&&(num[j]<num[j-1]);j--)
		{
			swap(num[j],num[j-1]);
			swapCount++;
		}
	return swapCount;
}

void merge(int num[], int start, int med, int end)//合并数组的左右两边，med为右边有序序列的开始
{
	//如果第二个有序序列的第一个数比第一个有序序列的最后一个数还要大，则不需要整理
	if(num[med]>=num[med-1]) return;

	//复制左半边
	int leftLen=med-start;
	int *numLeft=new int[leftLen];
	for(int i=0; i<leftLen; i++)
	{
		numLeft[i]=num[start+i];
	}

	int leftIndex=0,rightIndex=med,numIndex=start;
	while(leftIndex<leftLen && rightIndex<=end)
	{//取两个序列中较小的那个放到num中
		if(numLeft[leftIndex]<num[rightIndex]) num[numIndex++]=numLeft[leftIndex++];
		else num[numIndex++]=num[rightIndex++];
	}
	while(leftIndex<leftLen)
	{//如果左边序列还没取完，则添加到num后面
		num[numIndex++]=numLeft[leftIndex++];
	}
	while(rightIndex<=end)
	{//如果右边序列没取完
		num[numIndex++]=num[rightIndex++];
	}

	delete[] numLeft;
}

void mergeSort1(int num[], int start, int end)//自顶向下的归并排序
{
	//如果序列长度小于5则用插入法
	if((end-start)<5) 
	{
		insertSort(num, start, end);
		return;
	}

	int med=(end+start+1)/2;
	mergeSort1(num, start, med-1);//整理左边
	mergeSort1(num, med, end);//整理右边
	merge(num, start,med, end);//左右合并
}

void mergeSort3(int num[], int len)//自顶向下的归并排序
{
	int *numTmp=new int[len];//在外面申请好内存
	bool flag=mergeSortInside(num, numTmp, 0, len-1);
	if(!flag) merge2(numTmp, num, 0, (len+1)/2, len-1);//如果最后一次是从数组合并到副本，还需要复制回数组
	delete[] numTmp;
}
bool mergeSortInside(int num[], int numTmp[], int start, int end)
{
	static bool flag=true;
	//如果序列长度小于5则用插入法
	if((end-start)<5) 
	{
		insertSort(num, start, end);
		return true;
	}
	int med=(end+start+1)/2;
	mergeSort1(num, start, med-1);//整理左边
	mergeSort1(num, med, end);//整理右边
	if(flag)
	{
		merge2(num,numTmp, start,med, end);//从数组合并到副本
		flag=false;
	}else
	{
		merge2(numTmp,num, start,med, end);//从副本到数组
		flag=true;
	}
	return flag;
}

void merge2(int in[],int out[], int start, int med, int end)//合并数组的左右两边，med为右边有序序列的开始
{
	//如果第二个有序序列的第一个数比第一个有序序列的最后一个数还要大
	if(in[med]>=out[med-1])
	{//注意这里与之前有所不同，不能直接跳过，但只直接将数据复制到输出
		for(int i=start;i<=end;i++)
			out[i]=in[i];
		return;
	}

	int leftIndex=start,rightIndex=med, outIndex=start;
	while(leftIndex<med && rightIndex<=end)
	{//取两个序列中较小的那个放到out中
		if(in[leftIndex]<in[rightIndex]) out[outIndex++]=in[leftIndex++];
		else out[outIndex++]=in[rightIndex++];
	}
	while(leftIndex<med)
	{//如果左边序列还没取完，则添加到out后面
		out[outIndex++]=in[leftIndex++];
	}
	while(rightIndex<=end)
	{//如果右边序列没取完
		out[outIndex++]=in[rightIndex++];
	}


}

void mergeSort2(int num[], int start, int end)//自下向顶的归并排序
{
	int tmpEnd=0;
	int len=end-start+1;
	for(int gap=2;gap<len;gap*=2)
		for(int i=0;(tmpEnd=i+gap-1)<len;i+=gap)
		{			
			merge(num,i,(i+tmpEnd+1)/2,tmpEnd);
		}
}

void quickSort(int num[], int start, int end)//快速排序
{
	if(start+5>=end) //小于5时使用插入排序
	{
		insertSort(num, start, end);
		return;	
	}
	int med=patitionForQuickSort(num, start, end);//整理
	quickSort(num, start, med-1);//对切分元素左边进行排序
	quickSort(num, med+1, end);//对切分元素的右边进行排序
}

//取左边的第一个数为切分元素，小值放在左边，大值放在右边
int patitionForQuickSort(int num[], int start, int end)
{
	int v=num[start];//切分元素
	int leftN=start, rightN=end+1;
	while(1)
	{
		//从左边开始找大于v的数
		while(num[++leftN]<v)  if(leftN==end)  break;
		//从右边开始找小于v的数
		while(num[--rightN]>v) if(rightN==start)   break;
		
		if(leftN>=rightN) break;
		swap(num[leftN], num[rightN]);
	}
	//把切分元素放在中间
	swap(num[start], num[rightN]);
	return rightN;//返回切分元素的位置
}




//将序列分成小于v， 等于v， 大于v三个区域
void  quickSort2(int num[], int start, int end)//三向切分的快速排序
{
	if(start+6>=end) 
	{
		shellSort(num, start, end);
		return;	
	}

	int v=num[start];//取第一个数作为切分元素
	int curIndex=start+1;//当前遍历的位置
	int eqHead=start;//等于v区域的第一个数
	int beforeBgHead=end;//大于v区域的前一个数，即未比较区域的最后一个数
	while(curIndex<=beforeBgHead)
	{
		//如果当前数等于v，则不作处理
		if(num[curIndex]==v) curIndex++;		
		else if(num[curIndex]<v) 
		{//如果当前数小于v，则把当前数与等于v区域的第一个数交换位置，即将小于v的数放在等于v区域的前面
			num[eqHead]=num[curIndex];
			num[curIndex]=v;
			//等于v区域的第一个数的位置做相应调整
			curIndex++;
			eqHead++;
		}
		else
		{//如果当前数大于v，则把当前数与大于v区域的前一个数交换，注意此时不用将curIndex加1
			swap(num[curIndex],num[ beforeBgHead]);
			//curIndex++;
			beforeBgHead--;
		}
	}

	quickSort2(num, start, eqHead-1);//小于v的区域进行排序
	quickSort2(num, beforeBgHead+1, end);//大于v的区域进行排序
}
