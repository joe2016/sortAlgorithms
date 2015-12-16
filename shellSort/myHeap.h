#pragma once


//二叉堆，从小到大排序
class heapBinaryTree
{
public:
	heapBinaryTree(int capacity);//指定容量
	heapBinaryTree(const int num[], int len);//用数组初始化堆
	~heapBinaryTree();
	inline int getCapacity(){return cap;}
	inline int getLen(){return len;}
	bool insert(int e);
	int getMin();//取得最小值
	int deleteMin();//删除并返回最小值
	void showHeap();
private:
	void sink(int pos);//将pos位置的元素下沉到合适的位置
	void swim(int pos);
	inline void swap(int num[], int pos1, int pos2);
private:
	int len;//堆长度
	int cap;//可扩展的最大容量
	int *elem;//元素数组

};

class priorityQueueWithIndex
{
public:
	priorityQueueWithIndex(int capacity);
	priorityQueueWithIndex(const int num[], int len);
	~priorityQueueWithIndex();
	inline int getCapacity(){return cap;}
	inline int getLen(){return heapLen;}
	bool insert(int e);
	int getMin();//取得最小值
	int deleteMin();//删除并返回最小值
	void showHeap();
	bool change(int index, int e);//修改第index个元素的值为e，并调整队列
	int insertWithCheck(int e);//如果已添加的元素队列中存在空位（标记为-1），则添加到空位，否则添加到队列结尾,返回插入位置
private:
	void sink(int pos);//将pos位置的元素下沉到合适的位置
	void swim(int pos);
	inline void swap(int num[], int pos1, int pos2);

private:
	int heapLen;//堆的大小
	int elemNum;//已加元素的大小，包括被删除的
	int cap;
	//下面3个数组用来保存数据，elem[elemIndex[1]]表示最大（小）元素的值
	//heapIndex[1]表示第一个插入的元素在堆中的位置
	//elemIndex[heapInde[i]]=i
	int *elem;//元素数组，按插入顺序保存
	int *elemIndex;//用来保存元素数组的下标（元素的插入顺序），堆结构，元素小（大）的优先
	int *heapIndex;//用来保存堆的下标（元素在堆里的位置），按元素的插入顺序保存
	
};