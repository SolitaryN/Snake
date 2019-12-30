#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct StackNode{
	struct StackNode * Next;                                                                                                                                                                                                                                                                                                              
	char data;
} StackNode;					//此处定义了链栈的节点 

typedef struct LinkNode{
	int weight;				//权值 
	char data;
	struct LinkNode * Next;
} LinkNode;					//此处定义了单链表的节点，用来保存出现的都有哪些字符，还有字符出现的次数 

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
		printf("%d ", temp->weight);
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
