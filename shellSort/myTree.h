#pragma once

class treeNode
{
public :
	treeNode(int key, int val, treeNode* left, treeNode* right);
	treeNode(int key, int val);
public:
	int _key;
	int _val;
	treeNode* _left;
	treeNode* _right;
	int _nodeNum;//�Ըýڵ�Ϊ�������Ľڵ���
};
class BST
{
public:
	BST();
	~BST();
	void put(int key, int val);//���Ӽ�ֵΪkey��ֵΪval�Ľڵ�
	treeNode* get(int key);//��ü�ֵΪkey�Ľڵ�
	void inorder();//ǰ�������������ӡ����ֵ
	treeNode* select(int r);//�������Ϊr�Ľڵ�
	int rank(int key);//��ü�ֵΪkey������
	int floor(int key);//��ò�����key������ֵ
	treeNode* getMin();//��ü�ֵ��С�Ľڵ�
	int deleteMin();//ɾ����ֵ��С�Ľڵ㣨�ͷ��ڴ棩
	bool deleteNode(int key);//ɾ����ֵΪkey�Ľڵ㣨�ͷ��ڴ棩

private:
	treeNode* put(treeNode* root, int key, int val);
	treeNode* get(treeNode* root, int key);
	void inorder(treeNode* root);
	void deleteAllNodes(treeNode* root);
	int size(treeNode* root);//��ȡ��rootΪ���Ķ������Ľڵ���
	treeNode* select(treeNode* root, int rank);
	int rank(treeNode* root, int key);
	treeNode* floor(treeNode* root, int key);
	treeNode* getMin(treeNode* root);
	treeNode* removeMinNode(treeNode* &root);//����ֵ��С�Ľڵ�������Ƴ������ظýڵ㣨���ͷ��ڴ棩
	treeNode* removeNode(treeNode* &root, int key);//����ֵΪkey�Ľڵ�������Ƴ������ظýڵ㣨���ͷ��ڴ棩

private:
	treeNode* _root;
};