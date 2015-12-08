#pragma once



class myNode
{
public :
	int val;
	myNode* next;
};

myNode* makeListByArray(const int* a, int len);
void showList(const myNode* head);
void deleteList(myNode* head);

//����鲢����
myNode* mergeForList(myNode* a, myNode* b);
void mergeSort2ForList(myNode* &head);

//�����������
myNode* quickSortForList(myNode* &head);