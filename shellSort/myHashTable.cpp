#include "stdafx.h"
#include "myHashTable.h"
#include <iostream>
using namespace std;

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

unsigned int SeparateChainingHashST::hash(int key)
{
//	std::hash<int> h;
	return _h(key)%_chainNum;
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

	while(1)
	{
		if(chain->_key==key)//如果key已存在，更新val
		{
			chain->_val=val;
			return;
		}
		if(chain->_next==nullptr) break;
		chain=chain->_next;
	}

	chain->_next=new ChainNode(key, val);//加到链表尾部

}

ChainNode* SeparateChainingHashST::get(int key)
{
	int index=hash(key);
	ChainNode* chain=_chainHeads[index];//找到对应的链表头
	while(chain!=nullptr)
	{
		if(chain->_key==key)
		{
			return chain;//如果找到对应key，则返回node
		}
		chain=chain->_next;
	}
	return nullptr;

}

void SeparateChainingHashST::showChains()
{
	ChainNode* N;
	for(int i=0; i<_chainNum; i++)
	{
		cout<<"Chain"<<i<<endl;
		N=_chainHeads[i];
		while (N)
		{
			cout<<N->_key<<" ";
			N=N->_next;
		}
		cout<<endl;
	}

}

SeparateChainingHashST::~SeparateChainingHashST()
{
	for(int i=0; i<_chainNum; i++)
	{
		deleteAllNodes(_chainHeads[i]);//删除所有链表的节点
	}
	delete[] _chainHeads;//删除数组
}

void SeparateChainingHashST::deleteAllNodes(ChainNode* head)//删除链表头为head的链表
{
	ChainNode* N;
	while (head)
	{
		N=head;
		head=head->_next;
		delete N;
	}
}



LinearProbingHashST::LinearProbingHashST()
{
	_keyNum=0;
	_blockNum=4;//默认空格为4个
	_blocks=new ChainNode*[_blockNum];
	for(int i=0;i<_blockNum;i++) _blocks[i]=nullptr;

}

LinearProbingHashST::LinearProbingHashST(int keyNumEstimate)
{
	_keyNum=0;
	_blockNum=2* keyNumEstimate;//保证空间是将要加入元素个数的2倍
	_blocks=new ChainNode*[_blockNum];
	for(int i=0;i<_blockNum;i++) _blocks[i]=nullptr;

}

LinearProbingHashST::~LinearProbingHashST()
{
	for(int i=0;i<_blockNum;i++)
		if(_blocks[i])	delete _blocks[i];
	delete[] _blocks;
}


unsigned int LinearProbingHashST::hash(int key)
{
	return _h(key)%_blockNum;
}

void LinearProbingHashST::resize(int cap)
{
	auto blocksOld=_blocks;//原数组指针
	_blocks=new ChainNode*[cap];//新建数组
	for(int i=0;i<cap;i++) _blocks[i]=nullptr;

	int blockNumOld=_blockNum;
	_keyNum=0;
	_blockNum=cap;//这里必须先设置正确的_blockNum才能开始调用put
	for(int i=0;i<blockNumOld;i++)//将原数组的数组（node指针）全部插入到新数组中
	{
		if(blocksOld[i]) put(blocksOld[i]);
	}
	delete[] blocksOld;

}

void LinearProbingHashST::put(int key, int val)
{
	if(_keyNum>=_blockNum/2) resize(_blockNum*2);
	int index=hash(key);
	ChainNode* N=_blocks[index];
	while (N)
	{
		if(N->_key == key) 
		{
			N->_val=val;
			return ;
		}
		index=(++index)%_blockNum;
		N=_blocks[index];//如果不为空则查找下一个，到达最后一格回到第一格
	}
	//将新元素添加到空格中
	_blocks[index]=new ChainNode(key, val);
	_keyNum++;
}

void LinearProbingHashST::put(ChainNode* insertNode)
{
	if(_keyNum>=_blockNum/2) resize(_blockNum*2);
	if(insertNode==nullptr) return;
	int index=hash(insertNode->_key);
	ChainNode* N=_blocks[index];
	while (N)
	{
		if(N->_key == insertNode->_key) 
		{
			N->_val=insertNode->_val;
			return ;
		}
		index=(++index)%_blockNum;
		N=_blocks[index];//如果不为空则查找下一个，到达最后一格回到第一格
	}
	//将新元素添加到空格中
	_blocks[index]=insertNode;
	_keyNum++;
}


ChainNode* LinearProbingHashST::get(int key)
{
	int index=hash(key);
	ChainNode* N=_blocks[index];
	while (N)
	{
		if(N->_key == key) 
		{
			return N;
		}
		index=(++index)%_blockNum;
		N=_blocks[index];//如果key不同则查找下一个，直到找到空格
	}
	return nullptr;
}

bool LinearProbingHashST::deleteNode(int key)
{
	if(_keyNum==0) return false;
	int index=hash(key);
	ChainNode* N=_blocks[index];
	while (N)
	{
		if(N->_key == key) 
		{//删除对应元素
			_blocks[index]=nullptr;
			delete N;
			
		//将被删除元素后面的元素（到空格为止）重新插入
			do
			{
				_keyNum--;
				index=(++index)%_blockNum;
				N=_blocks[index];
				_blocks[index]=nullptr;
				put(N);
			}while (N);
			return true;
		}

		index=(++index)%_blockNum;
		N=_blocks[index];//如果key不同则查找下一个，直到找到空格
	}
	return false;

}

void LinearProbingHashST::AdjustSpace()
{
	if(_keyNum<=_blockNum/8) resize(_blockNum/2);
	if(_keyNum>=_blockNum/2) resize(_blockNum*2);
}

void LinearProbingHashST::show()
{//输出所有的格子里的数据，空的输出0
	cout<<"the data of all blocks:"<<endl;
	for(int i=0;i<_blockNum;i++)
	{
		if(_blocks[i]) cout<<_blocks[i]->_key<<" ";
		else cout<<"0 ";
	}
	cout<<endl;
}