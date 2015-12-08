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

//链表归并排序
myNode* mergeForList(myNode* a, myNode* b);
void mergeSort2ForList(myNode* &head);

//链表快速排序
myNode* quickSortForList(myNode* &head);