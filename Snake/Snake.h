#include <stdio.h>
#include <stdlib.h>
#include "DefineStru.h"

//创建Top和Head，它们都带头结点 
StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));

void InsertLink(LinkNode * Head, char data)		//此处的单链表插入用的是头插法 
{
	LinkNode * temp;
	temp = (LinkNode *) malloc (sizeof(LinkNode));
	if(temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);
	}	
	temp->data = data;
	temp->weight = 1;
	temp->Next = Head->Next;
	Head->Next = temp;
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

int * Huffman(LinkNode * head)//生成Haffman编码
{
	int min1 = 100000000, min2 = 100000000;
	LinkNode MinNode1, MinNode2;
	LinkNode * temp = head;
	while(temp->Next != NULL)//遍历一遍链表，找出两个weight最小的结点
	{
		if((temp->weight < min1 || temp->weight < min2) && (temp->mark != TRUE))
		{
			if(min1 > min2)
			{
				min1 = temp->weight;
				MinNode1 = *(temp);
			}
			else
			{
				min2 = temp->weight;
				MinNode2 = *(temp);
			}
		}
		MinNode1.mark = TRUE;
		MinNode2.mark = TRUE;//表示已经取出了链表中的值
		temp = temp->Next;
	}
	HuffmanNode * temp1 = Transform(MinNode1);
	HuffmanNode * temp2 = Transform(MinNode2);
	HuffmanNode * Root = (HuffmanNode *) malloc (sizeof(HuffmanNode));
	Root->LChind = temp1;
	Root->RChild = temp2;
	Root->weight = temp1->weight + temp2->weight;
	Root->MarkWetherNull = TRUE;//标记一下不是叶子结点
	LinkNode * NextLink = Transform1(*(Root));
	NextLink->Next = Head->Next;
	Head->Next = NextLink;//把新生成的结点（不是叶子结点）连接到链表中
}

HuffmanNode * Transform(LinkNode a)//把LinkNode转为Huffman
{
	HuffmanNode * temp = (HuffmanNode *) malloc (sizeof(HuffmanNode));
	temp->data = a.data;
	temp->weight = a.weight;
//	temp->LChind = NULL;//都是叶子结点，没错
//	temp->RChild = NULL;
	return temp;
}

LinkNode * Transform1(HuffmanNode a)//把Huffman转为LinkNode
{
	LinkNode * temp = (LinkNode *) malloc (sizeof(LinkNode));
	temp->weight = a.weight;
	temp->mark = 0;
}

