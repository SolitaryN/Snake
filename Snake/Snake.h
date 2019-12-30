#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode{
	struct Node * Next;                                                                                                                                                                                                                                                                                                              
	char data;
}StackNode;//�˴���������ջ�Ľڵ� 

typedef struct LinkNode{
	int weight;
	char data;
	struct LinkNode * Next;
} LinkNode;//�˴������˵�����Ľڵ㣬����������ֵĶ�����Щ�ַ��������ַ����ֵĴ��� 

//����Top��Head�����Ƕ���ͷ��� 
StackNode Top;
LinkNode Head;
//��ʼ��һ��Top��Head
Top->Next = NULL;
Head->Next = NULL; 

void InsertLink(LinkNode * Head, char data)//�˴��ĵ���������õ���ͷ�巨 
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

void Push(StackNode * top, char data)//��ջ����, topΪջ�� 
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
