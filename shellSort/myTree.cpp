#include "stdafx.h"
#include "myTree.h"
#include <iostream>

treeNode::treeNode(int key, int val, treeNode* left, treeNode* right)
	:_key(key), _val(val), _left(left), _right(right), _nodeNum(1), _color(BLACK)
{
	
}
treeNode::treeNode(int key, int val)
	:_key(key), _val(val), _nodeNum(1), _color(BLACK)
{
}

treeNode::treeNode(int key, int val, bool color)
	:_key(key), _val(val), _nodeNum(1), _color(color)
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

void BST::deleteAllNodes(treeNode* root)//后序遍历二叉树，并删除节点
{
	if(root==nullptr) return;
	deleteAllNodes(root->_left);
	deleteAllNodes(root->_right);
	delete root;
	root=nullptr;
}

void BST::put(int key, int val)//添加键值为key，值为val的节点
{
	_root=put(_root, key, val);
}

treeNode* BST::put(treeNode* root, int key, int val)
{
	if(root==nullptr) return new treeNode(key, val);
	if(key< root->_key) root->_left=put(root->_left, key, val);
	else if(key> root->_key) root->_right=put(root->_right, key, val);
	else root->_val=val;//如果已存在则更新val
	root->_nodeNum=size(root->_left)+size(root->_right)+1;//更新节点数，不用root->_nodeNum++;是考虑到节点已存在的情况
	return root;
}

treeNode* BST::get(int key)//获取键值为key的值
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

void BST::inorder()//前序遍历，顺序输出节点
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

int BST::size(treeNode* root)//获取以root为根的二叉树的节点数
{
	if(root==nullptr) return 0;
	else return root->_nodeNum;
}
treeNode* BST::select(int rank)
{
	if(rank>size(_root)) return nullptr;//如果排名比节点数还多
	return select(_root, rank);
}

treeNode* BST::select(treeNode* root, int rank)
{
	if(root==nullptr) return nullptr;
	int curRank=size(root->_left)+1;//(!)当前节点（在该根节点的树中的）排名为左子树+1
	if(rank==curRank) return root;
	else if(rank<curRank) return select(root->_left, rank);
	else return select(root->_right, rank-curRank);//(!)如果在右子树中，则在右子树中的排名为总排名-当前节点的排名

}

int BST::rank(int key)//获得键值为key的排名
{
	return rank(_root, key);
}

int BST::rank(treeNode* root, int key)//获得键值为key的排名
{
	if(root==nullptr) return 0;//如果没找到，返回0
	int curRank=size(root->_left)+1;
	if(key< root->_key) return rank(root->_left, key);
	else if(key> root->_key) return curRank+rank(root->_right, key);
	return curRank;
}


int BST::floor(int key)//获得不大于key的最大键值
{
	treeNode* res=floor(_root, key);
	if(res)	return res->_key;
	else return key+1;//如果没有找到，返回key+1
}

treeNode* BST::floor(treeNode* root, int key)
{
	if(root==nullptr) return nullptr;
	if(key< root->_key) return floor(root->_left, key);//如果比当前节点小，必定在左子树
	else if(key> root->_key) //(!)如果比当前节点大，可能在右子树
	{
		treeNode* res=floor(root->_right, key);
		if(res==nullptr) return root;//(!)如果不在右子树，则返回当前节点
		else return res;
	}
	else return root;//如果等于当前节点，返回当前节点
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
	delete res;//释放节点内存
	return key;
}


treeNode* BST::removeMinNode(treeNode* &root)//(!)这里用指针的引用，因为会改变实参（指针）的内容
{
	if(root->_left==nullptr) //如果没有左子树，则该节点为最小
	{
		treeNode* res=root;
		root=root->_right;//(!)将右子树（可能为空）的根节点代替当前节点,形参用指针引用的原因
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


treeNode* BST::removeNode(treeNode* &root, int key)//(!)这里用指针的引用，因为会改变实参（指针）的内容
{
	if(root==nullptr) return root;//没找到
	treeNode* res=nullptr;
	if(key< root->_key) res= removeNode(root->_left, key);
	else if(key> root->_key) res= removeNode(root->_right, key);
	else //找到
	{
		if(root->_left==nullptr)//如果只有一个或0个子树，则直接将存在的子树（或空）代替当前节点
		{
			root=root->_right;

		}
		else if(root->_right==nullptr)
		{
			root=root->_left;
		}
		else//(!)如果左右子树都存在,则用右子树中最小节点来代替当前节点
		{
			treeNode* rootNew=removeMinNode(root->_right);
			rootNew->_left=root->_left;
			if(rootNew!=root->_right)//（！）如果右子树的最小节点刚好是root的右子节点，则不需要处理
				rootNew->_right=root->_right;
			root=rootNew;
		}
	}
	root->_nodeNum=size(root->_left)+size(root->_right)+1;
	return res;

}


bool RedBlackBST::isRed(treeNode* N)
{
	if(N && (N->_color==RED)) return true;
	return false;
}

treeNode* RedBlackBST::rotateLeft(treeNode* N)
{
//	if(N==nullptr || (N->_right==nullptr)|| (N->_right->_color!=RED)) return N;

	//将N和他的右子节点互换位置，同时rightNode的左子树移动到N的右子树
	treeNode* rightNode=N->_right;
	N->_right=rightNode->_left;
	rightNode->_left=N;
	//颜色互换
	rightNode->_color=N->_color;
	N->_color=RED;
	//更新节点数目
	rightNode->_nodeNum=N->_nodeNum;
	N->_nodeNum=1+size(N->_left)+size(N->_right);
	return rightNode;
}

treeNode* RedBlackBST::rotateRight(treeNode* N)//实现刚好与左旋转相反
{
	treeNode* leftNode=N->_left;
	N->_left=leftNode->_right;
	leftNode->_right=N;
	//颜色互换
	leftNode->_color=N->_color;
	N->_color=RED;
	//更新节点数
	leftNode->_nodeNum=N->_nodeNum;
	N->_nodeNum=1+size(N->_left)+size(N->_right);
	return leftNode;

}

void RedBlackBST::changeColor(treeNode* N)
{
	N->_color=RED;//父节点变为红，表示与祖父节点结合形成一个3节点
	N->_left->_color=BLACK;
	N->_right->_color=BLACK;
}

void RedBlackBST::put(int key, int val)//添加键值为key，值为val的节点
{
	_root=put(_root, key, val);
	_root->_color=BLACK;//根节点为黑

}

treeNode* RedBlackBST::put(treeNode* root, int key, int val)
{
	if(root==nullptr) return new treeNode(key, val, RED);//默认新节点为红
	if(key < root->_key) root->_left=put(root->_left, key, val);
	else if(key > root->_key) root->_right=put(root->_right, key, val);
	else 
	{
		root->_val=val;
		return root;
	}
	root->_nodeNum=size(root->_left)+size(root->_right)+1;
	if(!isRed(root->_left) && isRed(root->_right)) root=rotateLeft(root);
	if(isRed(root->_left) && isRed(root->_left->_left)) root=rotateRight(root);
	if(isRed(root->_left) && isRed(root->_right)) changeColor(root);

	return root;
}


int RedBlackBST::deleteMin()//删除键值最小的节点（释放内存）
{
	return 0;
}

bool RedBlackBST::deleteNode(int key)//删除键值为key的节点（释放内存）
{
	return false;
}