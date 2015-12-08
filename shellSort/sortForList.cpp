#include "stdafx.h"
#include "sortForList.h"
#include <queue>
#include <iostream>
using namespace std;

myNode* makeListByArray(const int* a, int len)
{
	myNode* head=new myNode;
	head->val=a[0];
	head->next=nullptr;
	myNode* nodeTmp=head;
	for(int i=1;i<len;i++)
	{
		myNode* node1=new myNode;
		node1->val=a[i];
		node1->next=nullptr;
		nodeTmp->next=node1;
		nodeTmp=node1;
	}
	return head;
}

void showList(const myNode* head)
{
	while(head!=nullptr)
	{
		std::cout<<head->val<<", ";
		head=head->next;
	}
}

void deleteList(myNode* head)
{
	while(head!=nullptr)
	{
		myNode* tmp=head->next;
		delete head;
		head=tmp;
	}
}


myNode* mergeForList(myNode* a, myNode* b)//合并两个链表
{
	myNode* result = nullptr;
	if (a == nullptr)
	return(b);
	else if (b==nullptr)
	return(a);

  /* 使用递归调用的方法 */

	 if (a->val <= b->val)
	{
     result = a;
     result->next = mergeForList(a->next, b);
	 }
	 else	  
	 {
     result = b;
     result->next = mergeForList(a, b->next);
	 }
	 return(result);

}


void mergeSort2ForList(myNode* &head)//链表的归并排序
{
	if(head==nullptr) return;
	queue<myNode*> ptQueue;

	myNode *head1, *head2, *head3;
	head1=head;
	//先两两合并，如1和2合并，3和4合并，合并完把结尾指向空指针，并把头指针加入队列
	while(head1!=nullptr&&head1->next!=nullptr)
	{
		head2=head1->next;
		head3=head2->next;
		if(head1->val <=head2->val)
		{//如果小序列里的第一个节点比较小，那么不需要交换位置，直接把第一个节点作为头指针入队列，第二个节点指向空
			ptQueue.push(head1);
			head2->next=nullptr;
		}
		else
		{//如果第二个比较小，则交换位置
			ptQueue.push(head2);
			head2->next=head1;
			head1->next=nullptr;
		}
		head1=head3;
	}
	if(head1!=nullptr)//说明是单数个数据，把最后一个数据直接入队列
		ptQueue.push(head1);

	//开始两两合并队列里的序列，注意合并之后的新序列的头指针会继续入队列
	while(ptQueue.size()!=1)
	{//合并后的长度越来越长，可合并的序列也越来越少
	//当合并的序列只有一个时，退出循环
		head1=ptQueue.front();//取出第一个序列
		ptQueue.pop();
		head2=ptQueue.front();//取第二个序列		
		ptQueue.pop();
		ptQueue.push( mergeForList(head1, head2));//合并之后的新序列的头指针继续入队列
	}
	head=ptQueue.front();//排序后的头指针

}

//链表快速排序，返回最后一个元素的地址
myNode* quickSortForList(myNode* &head)
{
	if(head==nullptr||head->next==nullptr) return head;

	//分成小于，等于，大于哨兵的3个链表
	auto pivot=head;//取第一个元素为哨兵
	auto pt=head;//遍历指针
	myNode* ls_head=new myNode;//小于哨兵的链表头，该链表第一个元素无效
	myNode* eq_head=head;//等于哨兵的链表头，该链表第一个元素有效
	myNode* bg_head=new myNode;//大于哨兵的链表头，该链表第一个元素无效
	myNode* ls_pt=ls_head, *eq_pt=eq_head, *bg_pt=bg_head;
	while(pt=pt->next)
	{
		if(pt->val < pivot->val)
		{//小于哨兵，加到第一个链表后面
			ls_pt->next=pt;
			ls_pt=ls_pt->next;
		}
		else if(pt->val == pivot->val)
		{
			eq_pt->next=pt;
			eq_pt=eq_pt->next;
		}
		else 
		{
			bg_pt->next=pt;
			bg_pt=bg_pt->next;
		}
	}
	ls_pt->next=nullptr;//链表最后一个元素指向空指针
	eq_pt->next=nullptr;
	bg_pt->next=nullptr;
	

	ls_pt=quickSortForList(ls_head->next);//整理小于哨兵的链表，返回整理后的链表的最后一个元素的地址
	bg_pt=quickSortForList(bg_head->next);//

	if(ls_pt) //如果小于哨兵的链表不为空，则将3个链表首尾链接在一起
	{
		ls_pt->next=eq_head;
		eq_pt->next=bg_head->next;//由于第一个元素无效，bg_head->next才是头
		head=ls_head->next;//整理后链表的头指针
	}
	else
	{//如果小于哨兵的链表为空，合并其他2个链表
		eq_pt->next=bg_head->next;
		head=eq_head;
	}

	delete ls_head;
	delete bg_head;
	//如果大于哨兵的链表不为空返回该链表的最后一个元素的位置
	//否则返回等于哨兵的链表的最后一个元素的位置
	if(bg_pt) return bg_pt;
	else return eq_pt;

}