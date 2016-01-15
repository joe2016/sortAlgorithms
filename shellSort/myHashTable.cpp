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
	_chainHeads=new NodePoniter[chainNum];//�½�һ����������������ͷ
	for(int i=0;i<chainNum;i++)//����������ͷ��ʼ��Ϊ��ָ��
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
	ChainNode* chain=_chainHeads[index];//�ҵ���Ӧ������ͷ
	if(chain==nullptr) //�������Ϊ�գ��½�ͷָ��
	{
		_chainHeads[index]=new ChainNode(key, val);
		return ;
	}

	while(1)
	{
		if(chain->_key==key)//���key�Ѵ��ڣ�����val
		{
			chain->_val=val;
			return;
		}
		if(chain->_next==nullptr) break;
		chain=chain->_next;
	}

	chain->_next=new ChainNode(key, val);//�ӵ�����β��

}

ChainNode* SeparateChainingHashST::get(int key)
{
	int index=hash(key);
	ChainNode* chain=_chainHeads[index];//�ҵ���Ӧ������ͷ
	while(chain!=nullptr)
	{
		if(chain->_key==key)
		{
			return chain;//����ҵ���Ӧkey���򷵻�node
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
		deleteAllNodes(_chainHeads[i]);//ɾ����������Ľڵ�
	}
	delete[] _chainHeads;//ɾ������
}

void SeparateChainingHashST::deleteAllNodes(ChainNode* head)//ɾ������ͷΪhead������
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
	_blockNum=4;//Ĭ�Ͽո�Ϊ4��
	_blocks=new ChainNode*[_blockNum];
	for(int i=0;i<_blockNum;i++) _blocks[i]=nullptr;

}

LinearProbingHashST::LinearProbingHashST(int keyNumEstimate)
{
	_keyNum=0;
	_blockNum=2* keyNumEstimate;//��֤�ռ��ǽ�Ҫ����Ԫ�ظ�����2��
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
	auto blocksOld=_blocks;//ԭ����ָ��
	_blocks=new ChainNode*[cap];//�½�����
	for(int i=0;i<cap;i++) _blocks[i]=nullptr;

	int blockNumOld=_blockNum;
	_keyNum=0;
	_blockNum=cap;//���������������ȷ��_blockNum���ܿ�ʼ����put
	for(int i=0;i<blockNumOld;i++)//��ԭ��������飨nodeָ�룩ȫ�����뵽��������
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
		N=_blocks[index];//�����Ϊ���������һ�����������һ��ص���һ��
	}
	//����Ԫ����ӵ��ո���
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
		N=_blocks[index];//�����Ϊ���������һ�����������һ��ص���һ��
	}
	//����Ԫ����ӵ��ո���
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
		N=_blocks[index];//���key��ͬ�������һ����ֱ���ҵ��ո�
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
		{//ɾ����ӦԪ��
			_blocks[index]=nullptr;
			delete N;
			
		//����ɾ��Ԫ�غ����Ԫ�أ����ո�Ϊֹ�����²���
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
		N=_blocks[index];//���key��ͬ�������һ����ֱ���ҵ��ո�
	}
	return false;

}

void LinearProbingHashST::AdjustSpace()
{
	if(_keyNum<=_blockNum/8) resize(_blockNum/2);
	if(_keyNum>=_blockNum/2) resize(_blockNum*2);
}

void LinearProbingHashST::show()
{//������еĸ���������ݣ��յ����0
	cout<<"the data of all blocks:"<<endl;
	for(int i=0;i<_blockNum;i++)
	{
		if(_blocks[i]) cout<<_blocks[i]->_key<<" ";
		else cout<<"0 ";
	}
	cout<<endl;
}