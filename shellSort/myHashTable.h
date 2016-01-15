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
	SeparateChainingHashST(int chainNum);//指定链表数目
	~SeparateChainingHashST();
	void put(int key, int val);
	ChainNode* get(int key);
	void showChains();//所有链表打印出来

private:
	void deleteAllNodes(ChainNode* head);//删除链表头为head的所有节点
	inline unsigned int  hash(int key);//计算哈希值(小于链表数）

private:
	int _chainNum;
	NodePoniter *_chainHeads; //存放链表头的数组
	std::hash<int> _h;//用来计算hash码
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
	void AdjustSpace();//调整空间，如果保证空间利用率保持在1/8~1/2
	void show();

private:
	inline unsigned int hash(int key);
	void resize(int cap);//设置格子数目为cap
	void put(ChainNode* N);

private:
	int _keyNum;//已添加元素数目
	int _blockNum;//格子数目
	NodePoniter* _blocks;//格子数组的首指针
	std::hash<int> _h;
};