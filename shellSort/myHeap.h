#pragma once


//����ѣ���С��������
class heapBinaryTree
{
public:
	heapBinaryTree(int capacity);//ָ������
	heapBinaryTree(const int num[], int len);//�������ʼ����
	~heapBinaryTree();
	inline int getCapacity(){return cap;}
	inline int getLen(){return len;}
	bool insert(int e);
	int getMin();//ȡ����Сֵ
	int deleteMin();//ɾ����������Сֵ
	void showHeap();
private:
	void sink(int pos);//��posλ�õ�Ԫ���³������ʵ�λ��
	void swim(int pos);
	inline void swap(int num[], int pos1, int pos2);
private:
	int len;//�ѳ���
	int cap;//����չ���������
	int *elem;//Ԫ������

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
	int getMin();//ȡ����Сֵ
	int deleteMin();//ɾ����������Сֵ
	void showHeap();
	bool change(int index, int e);//�޸ĵ�index��Ԫ�ص�ֵΪe������������
	int insertWithCheck(int e);//�������ӵ�Ԫ�ض����д��ڿ�λ�����Ϊ-1��������ӵ���λ��������ӵ����н�β,���ز���λ��
private:
	void sink(int pos);//��posλ�õ�Ԫ���³������ʵ�λ��
	void swim(int pos);
	inline void swap(int num[], int pos1, int pos2);

private:
	int heapLen;//�ѵĴ�С
	int elemNum;//�Ѽ�Ԫ�صĴ�С��������ɾ����
	int cap;
	//����3�����������������ݣ�elem[elemIndex[1]]��ʾ���С��Ԫ�ص�ֵ
	//heapIndex[1]��ʾ��һ�������Ԫ���ڶ��е�λ��
	//elemIndex[heapInde[i]]=i
	int *elem;//Ԫ�����飬������˳�򱣴�
	int *elemIndex;//��������Ԫ��������±꣨Ԫ�صĲ���˳�򣩣��ѽṹ��Ԫ��С���󣩵�����
	int *heapIndex;//��������ѵ��±꣨Ԫ���ڶ����λ�ã�����Ԫ�صĲ���˳�򱣴�
	
};