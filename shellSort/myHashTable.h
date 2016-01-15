#pragma once
#include <iostream>

class ChainNode
{
public:
	int _key;
	int _val;
	ChainNode* _next;
public:
	ChainNode(int _key, int val);
};

typedef ChainNode* NodePoniter;

class SeparateChainingHashST
{
public:
	SeparateChainingHashST(int chainNum);//ָ��������Ŀ
	~SeparateChainingHashST();
	void put(int key, int val);
	ChainNode* get(int key);
	void showChains();//���������ӡ����

private:
	void deleteAllNodes(ChainNode* head);//ɾ������ͷΪhead�����нڵ�
	inline unsigned int  hash(int key);//�����ϣֵ(С����������

private:
	int _chainNum;
	NodePoniter *_chainHeads; //�������ͷ������
	std::hash<int> _h;//��������hash��
};


class LinearProbingHashST
{
public:
	LinearProbingHashST();
	LinearProbingHashST(int keyNumEstimate);
	~LinearProbingHashST();
	void put(int key, int val);
	ChainNode* get(int key);
	bool deleteNode(int key);
	void AdjustSpace();//�����ռ䣬�����֤�ռ������ʱ�����1/8~1/2
	void show();

private:
	inline unsigned int hash(int key);
	void resize(int cap);//���ø�����ĿΪcap
	void put(ChainNode* N);

private:
	int _keyNum;//�����Ԫ����Ŀ
	int _blockNum;//������Ŀ
	NodePoniter* _blocks;//�����������ָ��
	std::hash<int> _h;
};