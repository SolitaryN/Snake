#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FLASE 0

typedef struct StackNode{
	struct Node * Next;                                                                                                                                                                                                                                                                                                              
	char data;
}StackNode;					//�˴���������ջ�Ľڵ� 

typedef struct LinkNode{
	int weight;				//Ȩֵ 
	char data;
	struct LinkNode * Next;
} LinkNode;					//�˴������˵�����Ľڵ㣬����������ֵĶ�����Щ�ַ��������ַ����ֵĴ��� 

//����Top��Head�����Ƕ���ͷ��� 
StackNode Top;
LinkNode Head;
//��ʼ��һ��Top��Head
Top->Next = NULL;
Head->Next = NULL; 

void InsertLink(LinkNode * Head, char data)		//�˴��ĵ���������õ���ͷ�巨 
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

void Push(StackNode * top, char data)			//��ջ����, topΪջ�� 
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

int JudegeAppear(char data)//�ж��ַ��Ƿ�����������г��ֹ������û���ֹ�������TRUE����
{
	LinkNode * temp;
	temp = Head->Next;
	int j = 0;			//�˴���j�����ж��Ƿ�Ҫ��ջ���ַ�Ϊ��һ�γ��ֵ��ַ�
	while(temp != NULL)
	{	
		if(data == temp->data)
		{
			temp->weight++;
			j = 1;
			return TRUE;//���ֹ� 
		}
		temp =  temp->Next;
	}
	if(j == 0)
		InsertLink(Head, data);	//����½�����ַ������ַ����͵������д���һ���µĽڵ��������棬δ���ֹ� 
}

void Statistic(char * str)
{
	int i = 0;
	while(*(str + i) != '\0')
	{
			 
		
	}
}
