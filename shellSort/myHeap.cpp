#include "stdafx.h"
#include "myHeap.h"
#include <iostream>

heapBinaryTree::heapBinaryTree(int capacity)
{//����ռ䣬������ʼ������
	len=0;
	cap=capacity;
	elem=new int[capacity];
}
heapBinaryTree::heapBinaryTree(const int num[], int len)
{//ʹ���Ѵ��ڵ��������ݽ��г�ʼ�����������ö�
	cap=len*2;
	elem=new int[cap];
	this->len=0;
	for(int i=0;i<len;i++)
	{
		insert(num[i]);
	}
}

heapBinaryTree::~heapBinaryTree()
{
	delete[] elem;
}

inline void heapBinaryTree::swap(int num[], int pos1, int pos2)
{
	int tmp=num[pos1]; 
	num[pos1]=num[pos2];
	num[pos2]=tmp;
}

void heapBinaryTree::sink(int pos)//�³�posλ�õ�Ԫ�ص����ʵ�λ��
{
	int childPos=pos*2;//�����ӽڵ�����
	while(childPos<len)//����������ӽڵ�
	{
		if(elem[childPos]>elem[childPos+1]) childPos++;//�ҵ��ӽڵ��н�С��
		if(elem[pos]<=elem[childPos]) break;//����������ӽڵ㶼С������Ҫ���³�
		swap(elem, pos, childPos);
		pos=childPos;
		childPos=pos*2;
	}
	if(childPos==len && elem[pos]>elem[childPos]) swap(elem, pos, childPos);//ֻ��һ���ӽڵ�����
}

void heapBinaryTree::swim(int pos)//��posλ�õ�Ԫ�����������ʵ�λ��
{	
	while(pos/2>0)//������ڸ��ڵ�
	{
		if(elem[pos]>=elem[pos/2]) break;//����ȸ��ڵ�󣬲���Ҫ���ϸ�
		swap(elem, pos, pos/2);
		pos=pos/2;
	}
}
bool heapBinaryTree::insert(int e)//����Ԫ�ص��ѵĽ�β�������������ʵ�λ��
{
	if(len>=cap) return false;
	len++;
	elem[len]=e;
	swim(len);

}

int heapBinaryTree::getMin()//ȡ�öѶ���Ԫ�أ�����Сֵ
{
	if(len<1) return -1;
	return elem[1];
}

int heapBinaryTree::deleteMin()//ɾ����������Сֵ
{
	if(len<1) return -1;
	int min=elem[1];
	swap(elem, 1, len);
	len--;
	sink(1);
	return min;
}

void heapBinaryTree::showHeap()
{
	for(int i=1; i<=len;i++)
		std::cout<<elem[i]<<" ,";
}
//////////////////////////////////////

priorityQueueWithIndex::priorityQueueWithIndex(int capacity)
{
	heapLen=0;
	elemNum=0;
	cap=capacity;
	elem=new int[capacity];
	elemIndex=new int[capacity];
	heapIndex=new int[capacity];
}
priorityQueueWithIndex::priorityQueueWithIndex(const int num[], int len)
{//����������ʼ��
	cap=len*2;
	elemNum=0;
	heapLen=0;
	elem=new int[cap];
	elemIndex=new int[cap];
	heapIndex=new int[cap];
	for(int i=0;i<len;i++)
	{
		insert(num[i]);
	}
}

priorityQueueWithIndex::~priorityQueueWithIndex()
{
	delete[] elem;
	delete[] elemIndex;
	delete[] heapIndex;
}

inline void priorityQueueWithIndex::swap(int num[], int pos1, int pos2)
{
	int tmp=num[pos1]; 
	num[pos1]=num[pos2];
	num[pos2]=tmp;
}

void priorityQueueWithIndex::sink(int pos)
{
	int childPos=pos*2;
	while(childPos<heapLen)
	{//ͨ���Ƚ�elem���飨Ԫ�ص�ֵ���Ĵ�С������elemIndex��˳��
		if(elem[elemIndex[childPos]]>elem[elemIndex[childPos+1]]) childPos++;
		if(elem[elemIndex[pos]]<=elem[elemIndex[childPos]]) break;
		swap(elemIndex, pos, childPos);
		//��֤elemIndex[heapInde[i]]=i����heapIndex����Ӧ����
		swap(heapIndex,elemIndex[pos], elemIndex[childPos]);
		pos=childPos;
		childPos=pos*2;
	}
	if(childPos==heapLen && elem[elemIndex[pos]]>elem[elemIndex[childPos]]) 
	{
		swap(elemIndex, pos, childPos);//ֻ��һ���ӽڵ�����
		swap(heapIndex,elemIndex[pos], elemIndex[childPos]);
	}
}

void priorityQueueWithIndex::swim(int pos)
{
	while(pos/2>0)
	{
		if(elem[elemIndex[pos]]>=elem[elemIndex[pos/2]]) break;
		swap(elemIndex, pos, pos/2);
		swap(heapIndex,elemIndex[pos], elemIndex[pos/2]);
		pos=pos/2;
	}
}
bool priorityQueueWithIndex::insert(int e)
{
	if(elemNum>=cap) return false;
	heapLen++;
	elemNum++;
	elem[elemNum]=e;//ֱ����elemĩβ�����Ԫ��
	elemIndex[heapLen]=elemNum;//�ڶѵĽ�β�����Ԫ����elem�����е�λ��
	heapIndex[elemNum]=heapLen;//��heapIndex�Ľ�β�����Ԫ���ڶ��е�λ��
	
	swim(heapLen);

}

int priorityQueueWithIndex::getMin()
{
	if(heapLen<1) return -1;
	return elem[elemIndex[1]];//elemIndex[1]����СԪ�ص��±�
}

int priorityQueueWithIndex::deleteMin()
{
	if(heapLen<1) return -1;
	swap(elemIndex, 1, heapLen);//���Ѷ��ŵ��ѵ����
	swap(heapIndex, elemIndex[1], elemIndex[heapLen]);
	int min=elem[elemIndex[heapLen]];
	elem[elemIndex[heapLen]]=-1;//��Ԫ�ش�elem�����б��Ϊ-1����ʾɾ��
	heapIndex[elemIndex[heapLen]]=-1;//��heapIndex�ж�Ӧλ�ñ��Ϊ-1
	heapLen--;
	sink(1);
	return min;
}
bool priorityQueueWithIndex::change(int index, int e)//�޸ĵ�index���Ѵ���Ԫ�ص�ֵΪe������������
{
	if(index>elemNum) return false;
	if(heapIndex[index]==-1) return false;
	elem[index]=e;
	sink(heapIndex[index]);
	swim(heapIndex[index]);
}

int priorityQueueWithIndex::insertWithCheck(int e)//�������ӵ�Ԫ�ض����д��ڿ�λ�����Ϊ-1��������ӵ���λ��������ӵ����н�β
{
	if(heapLen==elemNum) //����ѳ�����Ԫ������ĳ���һ�£���˵��Ԫ�������в����ڿ�ȱ��ֱ�Ӳ����β
	{
		insert(e);
		return elemNum;
	}
	int i=1;
	while(i<=elemNum)//����Ԫ������Ŀ�ȱλ��
	{
		if(heapIndex[i]==-1) break;
		i++;
	}
	//������Ԫ��
	elem[i]=e;
	elemIndex[++heapLen]=i;
	heapIndex[i]=heapLen;
	//������
	sink(heapIndex[i]);
	swim(heapIndex[i]);
	return i;
}

void priorityQueueWithIndex::showHeap()
{
	std::cout<<"elems:"<<std::endl;
	for(int i=1; i<=elemNum;i++)
		std::cout<<elem[i]<<" ,";
	std::cout<<std::endl<<"elemIndex"<<std::endl;
	for(int i=1; i<=heapLen; i++)
		std::cout<<elemIndex[i]<<", ";
	std::cout<<std::endl<<"heapIndex"<<std::endl;
	for(int i=1; i<=elemNum; i++)
		std::cout<<heapIndex[i]<<", ";
}