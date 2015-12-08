
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

int shellSort(int num[], int start, int end)//ϣ������
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

int insertSort(int num[], int start, int end)//��������
{
	if(end<start) return -1;
	int swapCount=0;//��¼��������
	for(int i=start+1;i<=end;i++)
		for(int j=i;j>start&&(num[j]<num[j-1]);j--)
		{
			swap(num[j],num[j-1]);
			swapCount++;
		}
	return swapCount;
}

void merge(int num[], int start, int med, int end)//�ϲ�������������ߣ�medΪ�ұ��������еĿ�ʼ
{
	//����ڶ����������еĵ�һ�����ȵ�һ���������е����һ������Ҫ������Ҫ����
	if(num[med]>=num[med-1]) return;

	//��������
	int leftLen=med-start;
	int *numLeft=new int[leftLen];
	for(int i=0; i<leftLen; i++)
	{
		numLeft[i]=num[start+i];
	}

	int leftIndex=0,rightIndex=med,numIndex=start;
	while(leftIndex<leftLen && rightIndex<=end)
	{//ȡ���������н�С���Ǹ��ŵ�num��
		if(numLeft[leftIndex]<num[rightIndex]) num[numIndex++]=numLeft[leftIndex++];
		else num[numIndex++]=num[rightIndex++];
	}
	while(leftIndex<leftLen)
	{//���������л�ûȡ�꣬����ӵ�num����
		num[numIndex++]=numLeft[leftIndex++];
	}
	while(rightIndex<=end)
	{//����ұ�����ûȡ��
		num[numIndex++]=num[rightIndex++];
	}

	delete[] numLeft;
}

void mergeSort1(int num[], int start, int end)//�Զ����µĹ鲢����
{
	//������г���С��5���ò��뷨
	if((end-start)<5) 
	{
		insertSort(num, start, end);
		return;
	}

	int med=(end+start+1)/2;
	mergeSort1(num, start, med-1);//�������
	mergeSort1(num, med, end);//�����ұ�
	merge(num, start,med, end);//���Һϲ�
}

void mergeSort3(int num[], int len)//�Զ����µĹ鲢����
{
	int *numTmp=new int[len];//������������ڴ�
	bool flag=mergeSortInside(num, numTmp, 0, len-1);
	if(!flag) merge2(numTmp, num, 0, (len+1)/2, len-1);//������һ���Ǵ�����ϲ�������������Ҫ���ƻ�����
	delete[] numTmp;
}
bool mergeSortInside(int num[], int numTmp[], int start, int end)
{
	static bool flag=true;
	//������г���С��5���ò��뷨
	if((end-start)<5) 
	{
		insertSort(num, start, end);
		return true;
	}
	int med=(end+start+1)/2;
	mergeSort1(num, start, med-1);//�������
	mergeSort1(num, med, end);//�����ұ�
	if(flag)
	{
		merge2(num,numTmp, start,med, end);//������ϲ�������
		flag=false;
	}else
	{
		merge2(numTmp,num, start,med, end);//�Ӹ���������
		flag=true;
	}
	return flag;
}

void merge2(int in[],int out[], int start, int med, int end)//�ϲ�������������ߣ�medΪ�ұ��������еĿ�ʼ
{
	//����ڶ����������еĵ�һ�����ȵ�һ���������е����һ������Ҫ��
	if(in[med]>=out[med-1])
	{//ע��������֮ǰ������ͬ������ֱ����������ֱֻ�ӽ����ݸ��Ƶ����
		for(int i=start;i<=end;i++)
			out[i]=in[i];
		return;
	}

	int leftIndex=start,rightIndex=med, outIndex=start;
	while(leftIndex<med && rightIndex<=end)
	{//ȡ���������н�С���Ǹ��ŵ�out��
		if(in[leftIndex]<in[rightIndex]) out[outIndex++]=in[leftIndex++];
		else out[outIndex++]=in[rightIndex++];
	}
	while(leftIndex<med)
	{//���������л�ûȡ�꣬����ӵ�out����
		out[outIndex++]=in[leftIndex++];
	}
	while(rightIndex<=end)
	{//����ұ�����ûȡ��
		out[outIndex++]=in[rightIndex++];
	}


}

void mergeSort2(int num[], int start, int end)//�����򶥵Ĺ鲢����
{
	int tmpEnd=0;
	int len=end-start+1;
	for(int gap=2;gap<len;gap*=2)
		for(int i=0;(tmpEnd=i+gap-1)<len;i+=gap)
		{			
			merge(num,i,(i+tmpEnd+1)/2,tmpEnd);
		}
}

void quickSort(int num[], int start, int end)//��������
{
	if(start+5>=end) //С��5ʱʹ�ò�������
	{
		insertSort(num, start, end);
		return;	
	}
	int med=patitionForQuickSort(num, start, end);//����
	quickSort(num, start, med-1);//���з�Ԫ����߽�������
	quickSort(num, med+1, end);//���з�Ԫ�ص��ұ߽�������
}

//ȡ��ߵĵ�һ����Ϊ�з�Ԫ�أ�Сֵ������ߣ���ֵ�����ұ�
int patitionForQuickSort(int num[], int start, int end)
{
	int v=num[start];//�з�Ԫ��
	int leftN=start, rightN=end+1;
	while(1)
	{
		//����߿�ʼ�Ҵ���v����
		while(num[++leftN]<v)  if(leftN==end)  break;
		//���ұ߿�ʼ��С��v����
		while(num[--rightN]>v) if(rightN==start)   break;
		
		if(leftN>=rightN) break;
		swap(num[leftN], num[rightN]);
	}
	//���з�Ԫ�ط����м�
	swap(num[start], num[rightN]);
	return rightN;//�����з�Ԫ�ص�λ��
}




//�����зֳ�С��v�� ����v�� ����v��������
void  quickSort2(int num[], int start, int end)//�����зֵĿ�������
{
	if(start+6>=end) 
	{
		shellSort(num, start, end);
		return;	
	}

	int v=num[start];//ȡ��һ������Ϊ�з�Ԫ��
	int curIndex=start+1;//��ǰ������λ��
	int eqHead=start;//����v����ĵ�һ����
	int beforeBgHead=end;//����v�����ǰһ��������δ�Ƚ���������һ����
	while(curIndex<=beforeBgHead)
	{
		//�����ǰ������v����������
		if(num[curIndex]==v) curIndex++;		
		else if(num[curIndex]<v) 
		{//�����ǰ��С��v����ѵ�ǰ�������v����ĵ�һ��������λ�ã�����С��v�������ڵ���v�����ǰ��
			num[eqHead]=num[curIndex];
			num[curIndex]=v;
			//����v����ĵ�һ������λ������Ӧ����
			curIndex++;
			eqHead++;
		}
		else
		{//�����ǰ������v����ѵ�ǰ�������v�����ǰһ����������ע���ʱ���ý�curIndex��1
			swap(num[curIndex],num[ beforeBgHead]);
			//curIndex++;
			beforeBgHead--;
		}
	}

	quickSort2(num, start, eqHead-1);//С��v�������������
	quickSort2(num, beforeBgHead+1, end);//����v�������������
}
