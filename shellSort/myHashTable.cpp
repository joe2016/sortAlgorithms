#include "stdafx.h"
#include "myHashTable.h"

ChainNode::ChainNode(int key, int val)
{
	_key=key;
	_val=val;
	_next=nullptr;
}

SeparateChainingHashST::SeparateChainingHashST(int chainNum)
{
	_chainNum=chainNum;
	_chainHeads=new NodePoniter[chainNum];//新建一个数组来存放链表的头
	for(int i=0;i<chainNum;i++)//将所有链表头初始化为空指针
		_chainHeads[i]=nullptr;
}

SeparateChainingHashST::~SeparateChainingHashST()
{
	delete[] _chainHeads;
}

void SeparateChainingHashST::put(int key, int val)
{
	int index=hash(key);
	ChainNode* chain=_chainHeads[index];//找到对应的链表头
	if(chain==nullptr) //如果链表为空，新建头指针
	{
		_chainHeads[index]=new ChainNode(key, val);
		return ;
	}

	do
	{
		if(chain->_key==key)//如果key已存在，更新val
		{
			chain->_val=val;
			return;
		}
		
	}while(chain->_next!=nullptr,chain=chain->_next);

	chain->_next=new ChainNode(key, val);//加到链表尾部

}

ChainNode* SeparateChainingHashST::get(int key)
{
	int index=hash(key);
	ChainNode* chain=_chainHeads[index];//找到对应的链表头
	if(chain==nullptr) return nullptr;
	while(chain->_next!=nullptr)
	{
		if(chain->_key==key)//如果key已存在，更新val
		{
			return chain;
		}
		chain=chain->_next;
	}

}