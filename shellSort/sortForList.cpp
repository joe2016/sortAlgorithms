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


myNode* mergeForList(myNode* a, myNode* b)//�ϲ���������
{
	myNode* result = nullptr;
	if (a == nullptr)
	return(b);
	else if (b==nullptr)
	return(a);

  /* ʹ�õݹ���õķ��� */

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


void mergeSort2ForList(myNode* &head)//����Ĺ鲢����
{
	if(head==nullptr) return;
	queue<myNode*> ptQueue;

	myNode *head1, *head2, *head3;
	head1=head;
	//�������ϲ�����1��2�ϲ���3��4�ϲ����ϲ���ѽ�βָ���ָ�룬����ͷָ��������
	while(head1!=nullptr&&head1->next!=nullptr)
	{
		head2=head1->next;
		head3=head2->next;
		if(head1->val <=head2->val)
		{//���С������ĵ�һ���ڵ�Ƚ�С����ô����Ҫ����λ�ã�ֱ�Ӱѵ�һ���ڵ���Ϊͷָ������У��ڶ����ڵ�ָ���
			ptQueue.push(head1);
			head2->next=nullptr;
		}
		else
		{//����ڶ����Ƚ�С���򽻻�λ��
			ptQueue.push(head2);
			head2->next=head1;
			head1->next=nullptr;
		}
		head1=head3;
	}
	if(head1!=nullptr)//˵���ǵ��������ݣ������һ������ֱ�������
		ptQueue.push(head1);

	//��ʼ�����ϲ�����������У�ע��ϲ�֮��������е�ͷָ�����������
	while(ptQueue.size()!=1)
	{//�ϲ���ĳ���Խ��Խ�����ɺϲ�������ҲԽ��Խ��
	//���ϲ�������ֻ��һ��ʱ���˳�ѭ��
		head1=ptQueue.front();//ȡ����һ������
		ptQueue.pop();
		head2=ptQueue.front();//ȡ�ڶ�������		
		ptQueue.pop();
		ptQueue.push( mergeForList(head1, head2));//�ϲ�֮��������е�ͷָ����������
	}
	head=ptQueue.front();//������ͷָ��

}

//����������򣬷������һ��Ԫ�صĵ�ַ
myNode* quickSortForList(myNode* &head)
{
	if(head==nullptr||head->next==nullptr) return head;

	//�ֳ�С�ڣ����ڣ������ڱ���3������
	auto pivot=head;//ȡ��һ��Ԫ��Ϊ�ڱ�
	auto pt=head;//����ָ��
	myNode* ls_head=new myNode;//С���ڱ�������ͷ���������һ��Ԫ����Ч
	myNode* eq_head=head;//�����ڱ�������ͷ���������һ��Ԫ����Ч
	myNode* bg_head=new myNode;//�����ڱ�������ͷ���������һ��Ԫ����Ч
	myNode* ls_pt=ls_head, *eq_pt=eq_head, *bg_pt=bg_head;
	while(pt=pt->next)
	{
		if(pt->val < pivot->val)
		{//С���ڱ����ӵ���һ���������
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
	ls_pt->next=nullptr;//�������һ��Ԫ��ָ���ָ��
	eq_pt->next=nullptr;
	bg_pt->next=nullptr;
	

	ls_pt=quickSortForList(ls_head->next);//����С���ڱ�������������������������һ��Ԫ�صĵ�ַ
	bg_pt=quickSortForList(bg_head->next);//

	if(ls_pt) //���С���ڱ�������Ϊ�գ���3��������β������һ��
	{
		ls_pt->next=eq_head;
		eq_pt->next=bg_head->next;//���ڵ�һ��Ԫ����Ч��bg_head->next����ͷ
		head=ls_head->next;//����������ͷָ��
	}
	else
	{//���С���ڱ�������Ϊ�գ��ϲ�����2������
		eq_pt->next=bg_head->next;
		head=eq_head;
	}

	delete ls_head;
	delete bg_head;
	//��������ڱ�������Ϊ�շ��ظ���������һ��Ԫ�ص�λ��
	//���򷵻ص����ڱ�����������һ��Ԫ�ص�λ��
	if(bg_pt) return bg_pt;
	else return eq_pt;

}