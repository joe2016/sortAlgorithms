#include "stdafx.h"
#include "myTree.h"
#include <iostream>

treeNode::treeNode(int key, int val, treeNode* left, treeNode* right)
	:_key(key), _val(val), _left(left), _right(right), _nodeNum(1)
{
	
}
treeNode::treeNode(int key, int val)
	:_key(key), _val(val), _nodeNum(1)
{
}



BST::BST()
	:_root(nullptr)
{
}



BST::~BST()
{
	deleteAllNodes(_root);
}

void BST::deleteAllNodes(treeNode* root)//�����������������ɾ���ڵ�
{
	if(root==nullptr) return;
	deleteAllNodes(root->_left);
	deleteAllNodes(root->_right);
	delete root;
	root=nullptr;
}

void BST::put(int key, int val)//��Ӽ�ֵΪkey��ֵΪval�Ľڵ�
{
	_root=put(_root, key, val);
}

treeNode* BST::put(treeNode* root, int key, int val)
{
	if(root==nullptr) return new treeNode(key, val);
	if(key< root->_key) root->_left=put(root->_left, key, val);
	else if(key> root->_key) root->_right=put(root->_right, key, val);
	else root->_val=val;//����Ѵ��������val
	root->_nodeNum=size(root->_left)+size(root->_right)+1;//���½ڵ���������root->_nodeNum++;�ǿ��ǵ��ڵ��Ѵ��ڵ����
	return root;
}

treeNode* BST::get(int key)//��ȡ��ֵΪkey��ֵ
{
	return get(_root, key);

}

treeNode* BST::get(treeNode* root, int key)
{
	if(root==nullptr) return root;
	if(key< root->_key) return get(root->_left, key);
	else if(key> root->_key) return get(root->_right, key);
	else return root;
}

void BST::inorder()//ǰ�������˳������ڵ�
{
	std::cout<<"values in order:"<<std::endl;
	inorder(_root);
	std::cout<<std::endl;
}
void BST::inorder(treeNode* root)
{
	if(root==nullptr) return ;
	inorder(root->_left);
	std::cout<<root->_key<<" ";
	inorder(root->_right);
}

int BST::size(treeNode* root)//��ȡ��rootΪ���Ķ������Ľڵ���
{
	if(root==nullptr) return 0;
	else return root->_nodeNum;
}
treeNode* BST::select(int rank)
{
	if(rank>size(_root)) return nullptr;//��������Ƚڵ�������
	return select(_root, rank);
}

treeNode* BST::select(treeNode* root, int rank)
{
	if(root==nullptr) return nullptr;
	int curRank=size(root->_left)+1;//(!)��ǰ�ڵ㣨�ڸø��ڵ�����еģ�����Ϊ������+1
	if(rank==curRank) return root;
	else if(rank<curRank) return select(root->_left, rank);
	else return select(root->_right, rank-curRank);//(!)������������У������������е�����Ϊ������-��ǰ�ڵ������

}

int BST::rank(int key)//��ü�ֵΪkey������
{
	return rank(_root, key);
}

int BST::rank(treeNode* root, int key)//��ü�ֵΪkey������
{
	if(root==nullptr) return 0;//���û�ҵ�������0
	int curRank=size(root->_left)+1;
	if(key< root->_key) return rank(root->_left, key);
	else if(key> root->_key) return curRank+rank(root->_right, key);
	return curRank;
}


int BST::floor(int key)//��ò�����key������ֵ
{
	treeNode* res=floor(_root, key);
	if(res)	return res->_key;
	else return key+1;//���û���ҵ�������key+1
}

treeNode* BST::floor(treeNode* root, int key)
{
	if(root==nullptr) return nullptr;
	if(key< root->_key) return floor(root->_left, key);//����ȵ�ǰ�ڵ�С���ض���������
	else if(key> root->_key) //(!)����ȵ�ǰ�ڵ�󣬿�����������
	{
		treeNode* res=floor(root->_right, key);
		if(res==nullptr) return root;//(!)����������������򷵻ص�ǰ�ڵ�
		else return res;
	}
	else return root;//������ڵ�ǰ�ڵ㣬���ص�ǰ�ڵ�
}

treeNode* BST::getMin()
{
	return getMin(_root);
}


treeNode* BST::getMin(treeNode* root)
{
	if(root->_left==nullptr) return root;
	return getMin(root->_left);
}


int BST::deleteMin()
{
	if(_root==nullptr) return 0;
	treeNode* res=removeMinNode(_root);
	int key=res->_key;
	delete res;//�ͷŽڵ��ڴ�
	return key;
}


treeNode* BST::removeMinNode(treeNode* &root)//(!)������ָ������ã���Ϊ��ı�ʵ�Σ�ָ�룩������
{
	if(root->_left==nullptr) //���û������������ýڵ�Ϊ��С
	{
		treeNode* res=root;
		root=root->_right;//(!)��������������Ϊ�գ��ĸ��ڵ���浱ǰ�ڵ�,�β���ָ�����õ�ԭ��
		return res;
	}
	root->_nodeNum--;
	return removeMinNode(root->_left);
	 
}

bool  BST::deleteNode(int key)
{
	treeNode* res=removeNode(_root, key);
	if(res==nullptr) return false;
	delete res;
	return true;
	
}

treeNode* BST::removeNode(treeNode* &root, int key)//(!)������ָ������ã���Ϊ��ı�ʵ�Σ�ָ�룩������
{
	if(root==nullptr) return root;//û�ҵ�
	if(key< root->_key) return removeNode(root->_left, key);
	else if(key> root->_key) return removeNode(root->_right, key);
	else //�ҵ�
	{
		treeNode* res=root;//Ҫ���صĽڵ�
		if(root->_left==nullptr)//���ֻ��һ����0����������ֱ�ӽ����ڵ���������գ����浱ǰ�ڵ�
		{
			root=root->_right;

		}
		else if(root->_right==nullptr)
		{
			root=root->_left;
		}
		else//(!)�����������������,��������������С�ڵ������浱ǰ�ڵ�
		{
			treeNode* rootNew=removeMinNode(root->_right);
			rootNew->_left=root->_left;
			rootNew->_right=root->_right;
			root=rootNew;
		}
		return res;
	}

}