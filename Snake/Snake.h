#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct StackNode{
	struct StackNode * Next;                                                                                                                                                                                                                                                                                                              
	char data;
} StackNode;					//�˴���������ջ�Ľڵ� 

typedef struct LinkNode{
	int weight;				//Ȩֵ 
	char data;
	struct LinkNode * Next;
} LinkNode;					//�˴������˵�����Ľڵ㣬����������ֵĶ�����Щ�ַ��������ַ����ֵĴ��� 

//����Top��Head�����Ƕ���ͷ��� 
StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));

void InsertLink(LinkNode * Head, char data)		//�˴��ĵ���������õ���ͷ�巨 
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

void Push(StackNode * top, char data)			//��ջ����, topΪջ�� 
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

void Pop(StackNode * top)
{
	while(top->Next != NULL)
	{
     printf("%c ", top->data);
     top = top->Next;
	} 
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
	return FALSE;
}

void Statistic(char * str)
{
	int i = 0;
	while(*(str + i) != '\0')
	{
		JudegeAppear(*(str + i));//�ж��Ƿ��ַ����ֹ� 
		Push(Top, *(str + i));//��ջ 
		i++;
	}
}
