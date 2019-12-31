#include <stdio.h>
#include <stdlib.h>
#include "DefineStru.h"

//创建Top和Head，它们都带头结点 
StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));

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

int JudegeAppear(char data)//判断字符是否在这个链表中出现过，如果没出现过，返回TRUE保存
{
	LinkNode * temp;
	temp = Head->Next;
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
		InsertLink(Head, data);	//如果新进入的字符是新字符，就单链表中创建一个新的节点用来保存，未出现过 
	return FALSE;
}

void Statistic(char * str)
{
	int i = 0;
	while(*(str + i) != '\0')
	{
		JudegeAppear(*(str + i));//判断是否字符出现过 
		Push(Top, *(str + i));//入栈 
		i++;
	}
}

// void initWithRoot(LinkNode * head)
// {
// 	LinkNode * temp = head;
// 	while(temp->Next != NULL)
// 	{
// 		temp = temp->Next;
// 		temp->markWetherRoot = FALSE;
// 	}
// }
// HuffmanNode * transform(LinkNode * head)
// {
	
// }
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

// LinkNode * Huffman(LinkNode * head)//生成一棵树，返回它的Root
// {
// 	LinkNode * MinNode1, * MinNode2;
// 	LinkNode * temp = head;
// 	LinkNode * bigRoot;
// 	while(head->Next->Next != NULL)//最后链表中至少有一个元素，这写的有错
// 	{
// 		int min1 = 100000000, min2 = 100000000;//用来找权值最小的两个LinkNode
// 		while(temp->Next != NULL)//遍历一遍链表，找出两个weight最小的结点
// 		{
// 			temp = temp->Next;
// 		if(temp->weight < min1 || temp->weight < min2)
// 		{
// 			if(min1 > min2)
// 			{
// 				min1 = temp->weight;
// 				MinNode1 = temp;
// 			}
// 			else
// 			{
// 				min2 = temp->weight;
// 				MinNode2 = temp;
// 			}
// 		}
// 		}
// 	MinNode1->Pre->Next = MinNode1->Next;
// 	MinNode2->Pre->Next = MinNode2->Next;//让结点断掉
// 	if(MinNode1->markWetherRoot == FALSE)
// 	{
// 		MinNode1->LChind = NULL;
// 		MinNode1->RChild = NULL;
// 	}
// 	if(MinNode2->markWetherRoot = FALSE)
// 	{
// 		MinNode2->LChind = NULL;
// 		MinNode2->RChild = NULL;
// 	}

// 	LinkNode * Root = (LinkNode *) malloc (sizeof(LinkNode));
// 	Root->LChind = MinNode1;
// 	Root->RChild = MinNode2;
// 	Root->weight = MinNode1->weight + MinNode2->weight;
// 	bigRoot = Root;//保存根

// 	Root->Next = Head->Next;
// 	Head->Next = Root;//把新生成的结点（不是叶子结点）连接到链表中
// 	}
// 	return bigRoot;
// }

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




