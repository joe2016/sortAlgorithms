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
	_chainHeads=new NodePoniter[chainNum];//�½�һ����������������ͷ
	for(int i=0;i<chainNum;i++)//����������ͷ��ʼ��Ϊ��ָ��
		_chainHeads[i]=nullptr;
}

SeparateChainingHashST::~SeparateChainingHashST()
{
	delete[] _chainHeads;
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

	do
	{
		if(chain->_key==key)//���key�Ѵ��ڣ�����val
		{
			chain->_val=val;
			return;
		}
		
	}while(chain->_next!=nullptr,chain=chain->_next);

	chain->_next=new ChainNode(key, val);//�ӵ�����β��

}

ChainNode* SeparateChainingHashST::get(int key)
{
	int index=hash(key);
	ChainNode* chain=_chainHeads[index];//�ҵ���Ӧ������ͷ
	if(chain==nullptr) return nullptr;
	while(chain->_next!=nullptr)
	{
		if(chain->_key==key)//���key�Ѵ��ڣ�����val
		{
			return chain;
		}
		chain=chain->_next;
	}

}