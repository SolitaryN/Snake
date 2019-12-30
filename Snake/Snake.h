#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
	struct Node * Next;                                                                                                                                                                                                                                                                                                              
	char data;
}StackNode;//此处定义了链栈的节点 

typedef struct LinkNode{
	int weight;
	char data;
	struct LinkNode * Next;
} LinkNode;//此处定义了单链表的节点，用来保存出现的都有哪些字符，还有字符出现的次数 

//创建Top和Head，它们都带头结点 
StackNode Top;
LinkNode Head;
//初始化一下Top和Head
Top->Next = NULL;
Head->Next = NULL; 

void InsertLink(LinkNode * Head, char data)//此处的单链表插入用的是头插法 
{
	LinkNode * temp;
	temp = (LinkNode *) malloc (LinkNode);
	if(temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);	
	}	
	temp->data = data;
	temp->Next = Head->Next;
	Head->Next = temp;
} 

void Push(StackNode * top, char data)//入栈函数, top为栈顶 
{
	StackNode * temp;
	temp = (StackNode *) malloc (StackNode);
	if(temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);	
	}
	temp->data = data;
	temp->Next = top->Next;
	top->Next = temp;
}

void Statistic(char * str)
{
	int i = 0;
	while(*(str + i) != '\0')
	{
		
	}
}
