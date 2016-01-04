#pragma once
typedef ChainNode* NodePoniter;
class ChainNode
{
public:
	int _key;
	int _val;
	ChainNode* _next;
public:
	ChainNode(int _key, int val);
};

class SeparateChainingHashST
{
public:
	SeparateChainingHashST(int chainNum);
	~SeparateChainingHashST();
	void put(int key, int val);
	ChainNode* get(int key);

private:
	int _chainNum;
	NodePoniter *_chainHeads; //存放链表头的数组
};

int hash(int key);