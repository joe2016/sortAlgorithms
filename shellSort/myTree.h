#pragma once

#define BLACK false
#define RED true
class treeNode
{
public :
	treeNode(int key, int val, treeNode* left, treeNode* right);
	treeNode(int key, int val);
	treeNode(int key, int val, bool color);

public:
	int _key;
	int _val;
	treeNode* _left;
	treeNode* _right;
	int _nodeNum;//以该节点为根的树的节点数
	bool _color;//节点颜色，用于红黑树
};
class BST
{
public:
	BST();
	~BST();
	virtual void put(int key, int val);//添加键值为key，值为val的节点
	treeNode* get(int key);//获得键值为key的节点
	void inorder();//前序遍历树，并打印出键值
	treeNode* select(int r);//获得排名为r的节点
	int rank(int key);//获得键值为key的排名
	int floor(int key);//获得不大于key的最大键值
	treeNode* getMin();//获得键值最小的节点
	virtual int deleteMin();//删除键值最小的节点（释放内存）
	virtual bool deleteNode(int key);//删除键值为key的节点（释放内存）

protected:
	treeNode* put(treeNode* root, int key, int val);
	treeNode* get(treeNode* root, int key);
	void inorder(treeNode* root);
	void deleteAllNodes(treeNode* root);
	int size(treeNode* root);//获取以root为根的二叉树的节点数
	treeNode* select(treeNode* root, int rank);
	int rank(treeNode* root, int key);
	treeNode* floor(treeNode* root, int key);
	treeNode* getMin(treeNode* root);
	treeNode* removeMinNode(treeNode* &root);//将键值最小的节点从树中移除，返回该节点（不释放内存）
	treeNode* removeNode(treeNode* &root, int key);//将键值为key的节点从树中移除，返回该节点（不释放内存）

protected:
	treeNode* _root;
};

class RedBlackBST: public BST
{
public:
//	RedBlackBST();
//	~RedBlackBST();
	void put(int key, int val);//添加键值为key，值为val的节点
	int deleteMin();//删除键值最小的节点（释放内存）
	bool deleteNode(int key);//删除键值为key的节点（释放内存）

private:
	bool isRed(treeNode* N);//判断节点是否为红
	treeNode* rotateLeft(treeNode* N);
	treeNode* rotateRight(treeNode* N);
	void changeColor(treeNode* N);
	treeNode* put(treeNode* root, int key, int val);
};