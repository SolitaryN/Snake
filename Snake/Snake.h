#include <stdio.h>
#include <stdlib.h>
#include "DefineStru.h"

void InsertLink(LinkNode * head, char data)		//此处的单链表插入用的是头插法 
{
	LinkNode * temp;
	temp = (LinkNode *) malloc (sizeof(LinkNode));
	if(temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);
	}	
	temp->LChild = NULL; temp->RChild = NULL;
	temp->data = data;
	temp->weight = 1;
	temp->Next = head->Next;
	if(head->Next != NULL)
	{
		head->Next->Pre = temp;
	}
	temp->Pre = head;
	head->Next = temp;
} 

void Push(StackNode * top, char data)			//入栈函数, top为栈顶 
{
	StackNode * temp;
	temp = (StackNode *) malloc (sizeof(StackNode));
	if(temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);	
	}
	temp->data = data;
	temp->Next = top->Next;
	top->Next = temp;
}

void LinkPrintWeight(LinkNode * head)
{
	LinkNode * temp = head;
	while(temp->Next != NULL)
	{
		temp = temp->Next;
		printf("%c %d\n", temp->data, temp->weight);
	}
}

void Pop(StackNode * top)
{
	while(top->Next != NULL)
	{
	 top = top->Next;
     printf("%c ", top->data);
	} 
}

int JudegeAppear(LinkNode * head ,char data)//判断字符是否在这个链表中出现过，如果没出现过，返回TRUE保存
{
	LinkNode * temp;
	temp = head->Next;
	int j = 0;			//此处的j用来判断是否将要入栈的字符为第一次出现的字符
	while(temp != NULL)
	{	
		if(data == temp->data)
		{
			temp->weight++;
			j = 1;
			return TRUE;//出现过 
		}
		temp =  temp->Next;
	}
	if(j == 0)
		InsertLink(head, data);	//如果新进入的字符是新字符，就单链表中创建一个新的节点用来保存，未出现过 
	return FALSE;
}

void Statistic(StackNode * Top, LinkNode * head, char * str)
{
	int i = 0;
	while(*(str + i) != '\0')
	{
		JudegeAppear(head, *(str + i));//判断是否字符出现过 
		Push(Top, *(str + i));//入栈 
		i++;
	}
}

void loopLink(LinkNode * head)
{
	LinkNode * temp = head;
	while(temp != NULL)
	{
		temp = temp->Next;
		printf("%d ", temp->weight);
	}
}

LinkNode * Huffman(LinkNode * head)//生成Huffman一颗树，并且返回Root
{
	LinkNode * MinNode1, * MinNode2, * headCopy;//保存两个最小权值结点地址
	headCopy = head;
	while(head->Next->Next != NULL)//确保单链表中至少有两个元素
	{
		loopLink(head);
		LinkNode * temp = head;//temp用来遍历，会逐个向下移动
		while(temp->Next != NULL)//遍历单链表
		{
			loopLink(head);
			temp = temp->Next;
			int min1 = 100000000, min2 = 100000000;//用来找权值最小的两个结点
			if(temp->weight < min1 || temp->weight < min2)
			{
				if(min1 > min2)
				{
				 min1 = temp->weight;
				 MinNode1 = temp;
				}
				else
				{
				 min2 = temp->weight;
				 MinNode2 = temp;
				}
			}
		}
		//找到两个weight最小的结点MinNode1和MinNode2
		LinkNode * connect = (LinkNode *) malloc (sizeof(LinkNode));
		//生成一个连接两个最小结点的结点
		connect->LChild = MinNode1;
		connect->RChild = MinNode2;
		connect->weight = MinNode1->weight + MinNode2->weight;

		//把单链表中两个weight最小的结点删除
		MinNode1->Pre->Next = MinNode1->Next;
		MinNode2->Pre->Next = MinNode2->Next;
		MinNode1->Next = NULL;
		MinNode1->Pre = NULL;
		MinNode2->Next = NULL;
		MinNode2->Pre = NULL;
		//单链表连接上结点connect
		connect->Next = headCopy->Next;
		connect->Pre = headCopy;
		headCopy->Next = connect;
	}
	return headCopy->Next;
}

void leafNodePrint(LinkNode * Root)
{
	if(Root != NULL)
	{
		if(Root->LChild == NULL && Root->RChild == NULL)
			printf("%c ", Root->data);
		leafNodePrint(Root->LChild);
		leafNodePrint(Root->RChild);
	}
}




