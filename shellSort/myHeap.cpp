#include "stdafx.h"
#include "myHeap.h"
#include <iostream>

heapBinaryTree::heapBinaryTree(int capacity)
{//申请空间，但不初始化数据
	len=0;
	cap=capacity;
	elem=new int[capacity];
}
heapBinaryTree::heapBinaryTree(const int num[], int len)
{//使用已存在的数组数据进行初始化，并调整好堆
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

void heapBinaryTree::sink(int pos)//下沉pos位置的元素到合适的位置
{
	int childPos=pos*2;//计算子节点坐标
	while(childPos<len)//如果左右有子节点
	{
		if(elem[childPos]>elem[childPos+1]) childPos++;//找到子节点中较小的
		if(elem[pos]<=elem[childPos]) break;//如果比两个子节点都小，则不需要再下沉
		swap(elem, pos, childPos);
		pos=childPos;
		childPos=pos*2;
	}
	if(childPos==len && elem[pos]>elem[childPos]) swap(elem, pos, childPos);//只有一个子节点的情况
}

void heapBinaryTree::swim(int pos)//将pos位置的元素上升到合适的位置
{	
	while(pos/2>0)//如果存在父节点
	{
		if(elem[pos]>=elem[pos/2]) break;//如果比父节点大，不需要再上浮
		swap(elem, pos, pos/2);
		pos=pos/2;
	}
}
bool heapBinaryTree::insert(int e)//插入元素到堆的结尾，并上升到合适的位置
{
	if(len>=cap) return false;
	len++;
	elem[len]=e;
	swim(len);

}

int heapBinaryTree::getMin()//取得堆顶的元素，即最小值
{
	if(len<1) return -1;
	return elem[1];
}

int heapBinaryTree::deleteMin()//删除并返回最小值
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
{//用数组来初始化
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
	{//通过比较elem数组（元素的值）的大小来调整elemIndex的顺序
		if(elem[elemIndex[childPos]]>elem[elemIndex[childPos+1]]) childPos++;
		if(elem[elemIndex[pos]]<=elem[elemIndex[childPos]]) break;
		swap(elemIndex, pos, childPos);
		//保证elemIndex[heapInde[i]]=i，对heapIndex作对应调整
		swap(heapIndex,elemIndex[pos], elemIndex[childPos]);
		pos=childPos;
		childPos=pos*2;
	}
	if(childPos==heapLen && elem[elemIndex[pos]]>elem[elemIndex[childPos]]) 
	{
		swap(elemIndex, pos, childPos);//只有一个子节点的情况
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
	elem[elemNum]=e;//直接在elem末尾添加新元素
	elemIndex[heapLen]=elemNum;//在堆的结尾添加新元素在elem数组中的位置
	heapIndex[elemNum]=heapLen;//在heapIndex的结尾添加新元素在堆中的位置
	
	swim(heapLen);

}

int priorityQueueWithIndex::getMin()
{
	if(heapLen<1) return -1;
	return elem[elemIndex[1]];//elemIndex[1]是最小元素的下标
}

int priorityQueueWithIndex::deleteMin()
{
	if(heapLen<1) return -1;
	swap(elemIndex, 1, heapLen);//将堆顶放到堆的最后
	swap(heapIndex, elemIndex[1], elemIndex[heapLen]);
	int min=elem[elemIndex[heapLen]];
	elem[elemIndex[heapLen]]=-1;//将元素从elem数组中标记为-1，表示删除
	heapIndex[elemIndex[heapLen]]=-1;//将heapIndex中对应位置标记为-1
	heapLen--;
	sink(1);
	return min;
}
bool priorityQueueWithIndex::change(int index, int e)//修改第index个已存在元素的值为e，并调整队列
{
	if(index>elemNum) return false;
	if(heapIndex[index]==-1) return false;
	elem[index]=e;
	sink(heapIndex[index]);
	swim(heapIndex[index]);
}

int priorityQueueWithIndex::insertWithCheck(int e)//如果已添加的元素队列中存在空位（标记为-1），则添加到空位，否则添加到队列结尾
{
	if(heapLen==elemNum) //如果堆长度与元素数组的长度一致，则说明元素数组中不存在空缺，直接插入结尾
	{
		insert(e);
		return elemNum;
	}
	int i=1;
	while(i<=elemNum)//查找元素数组的空缺位置
	{
		if(heapIndex[i]==-1) break;
		i++;
	}
	//插入新元素
	elem[i]=e;
	elemIndex[++heapLen]=i;
	heapIndex[i]=heapLen;
	//调整堆
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