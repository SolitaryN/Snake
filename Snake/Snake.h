#include <stdio.h>
#include <stdlib.h>
#include "DefineStru.h"

void Push(StackNode *top, char data) //��ջ����, topΪջ��
{
	StackNode * temp;
	temp = (StackNode *)malloc(sizeof(StackNode));
	if (temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);
	}
	temp->data = data;
	temp->Next = top->Next;
	top->Next = temp;
}

void LinkPrintWeight(LinkNode *head)
{//��������������������������data��weight
	LinkNode *temp = head;
	int i = 0;
	printf("ÿ���ַ���Ӧ��Ȩֵ��");
	printf("\n----------------------------------------------------\n");
	while (temp->Next != NULL)
	{
		temp = temp->Next;
		if(i < 6)
		{
			i++;
			printf("%c %d\t", temp->data, temp->weight);
		}
		else if(i == 6)
		{
			i = 0;
			printf("%c %d\n", temp->data, temp->weight);
		}
	}
	printf("\n----------------------------------------------------\n");
}

void Pop(StackNode *top)//��ջ����
{
	StackNode * temp;
	while (top->Next != NULL)
	{
		temp = top->Next;
		printf("%c ", temp->data);
		top->Next = temp->Next;
		free(temp);
	}
}

void InsertLink(LinkNode *head, char data) //�˴��ĵ���������õ���ͷ�巨
{//�˺������������������ɽ�㲢���淢���µ��ַ�
	LinkNode *temp;
	temp = (LinkNode *)malloc(sizeof(LinkNode));
	if (temp == NULL)
	{
		printf("Memory space application failure");
		exit(0);
	}
	temp->LChild = NULL;
	temp->RChild = NULL;
	temp->data = data;
	temp->weight = 1;
	temp->Next = head->Next;
	if (head->Next != NULL)
	{
		head->Next->Pre = temp;
	}
	temp->Pre = head;
	head->Next = temp;
}

void JudegeAppear(LinkNode *head, char data) //�ж��ַ��Ƿ�����������г��ֹ������û���ֹ�������TRUE����
{
	LinkNode *temp;
	temp = head->Next;
	while (temp != NULL)
	{
		if (data == temp->data)//���ֹ�ʱ
		{
			temp->weight++;
			return ; 
		}
		temp = temp->Next;
	}
	//����ִ�е��⣬˵��δ��������ַ����ֹ�
	InsertLink(head, data); //����½�����ַ������ַ����͵������д���һ���µĽڵ��������棬δ���ֹ�
	return ;
}

void Statistic(LinkNode *head, char *str)
{//�˺�������ͳ���ַ����е��ַ���Ȩֵ
	int i = 0;
	while (*(str + i) != '\0')
	{
		JudegeAppear(head, *(str + i)); //�ж��Ƿ��ַ����ֹ�
		i++;
	}
}

LinkNode * FindMin (LinkNode * head)//�˺�������,����֤
{//�˺��������������������ҵ�weight��С�Ľڵ�ĵ�ַ�������ظõ�ַ
	LinkNode * temp = head;
	LinkNode * min;
	int bi = 100000000; //������Ȩֵ��С�Ľ��
	while (temp->Next != NULL) //����������
	{
		temp = temp->Next;
		if (temp->weight < bi)
		{
			bi = temp->weight;
			min = temp;
		}
	}
	return min;
}

void DeleteNode(LinkNode * s)//ɾ���������е����ݣ�����֤�˺�������
{
	s->Pre->Next = s->Next;
	if(s->Next != NULL)
	{
		s->Next->Pre = s->Pre;
	}
}

LinkNode * CreatNode(LinkNode * a, LinkNode * b)//�Ѽ��飬��������
{//�˺����������ж������ڵ���кϲ���һ����
	LinkNode * newNode = (LinkNode *) malloc (sizeof(LinkNode));
	newNode->weight = a->weight + b->weight;
	newNode->LChild = a;
	newNode->RChild = b;
	return newNode;
}

void ConnectLink(LinkNode * head, LinkNode * newNode)
{//�˺��������������ɵ����ĸ�����������
	newNode->Next = head->Next;
	if(head->Next != NULL)
	{
		head->Next->Pre = newNode;
	}
	newNode->Pre = head;
	head->Next = newNode;
}

LinkNode * Huffman(LinkNode * head) //����Huffmanһ���������ҷ���Root
{	//����֤���˺�����Ч
	//����headָ�벻�����䶯
	while(head->Next->Next != NULL)//���������϶���ʣ��һ���ڵ㣬Root
	{
		LinkNode * a = FindMin(head);//��weight��С�Ľڵ�
		DeleteNode(a);//�ҵ�֮����ڵ�������ɾ������ڵ�
		LinkNode * b = FindMin(head);
		DeleteNode(b);
		LinkNode * c = CreatNode(a, b);//���ҵ�������weight��С�Ľڵ�����һ����
		ConnectLink(head, c);//�������ɵ����ĸ��ڵ����ӵ���������
	}
	return head->Next;
}

void leafNodePrint(LinkNode *Root)
{//�˺�����������Ҷ�ӽڵ㣬��������ǵ�data��
	if (Root != NULL)
	{
		if (Root->LChild == NULL && Root->RChild == NULL)
			printf("%c ", Root->data);
		leafNodePrint(Root->LChild);
		leafNodePrint(Root->RChild);
	}
}

void Transform(LinkNode * Root)
{//�ѽ���е�Preָ��ָ�򸸽ڵ�
	if(Root != NULL)
	{
		if(Root->LChild != NULL)
			Root->LChild->Pre = Root;
		if(Root->RChild != NULL)
			Root->RChild->Pre = Root;
		Transform(Root->LChild);
		Transform(Root->RChild);
	}
}

void initRoot(LinkNode * Root)
{//��Root��Preָ�뻯Ϊ��
	Root->Pre = NULL;
}

void Encode(LinkNode *Root, Code * store)//����ͷ�巨
{//�˺���������Huffman���е�Ҷ�ӽ���ַ����б��룬���ɹ���������
	//���ɵĹ����������д��ջ�У�ջ�Ľ������StackNode��
	if (Root != NULL)
	{
		if (Root->LChild == NULL && Root->RChild == NULL)
		{
			LinkNode * temp = Root;
			Code * hh = (Code *) malloc (sizeof(Code));
			hh->Next = store->Next;
			store->Next = hh;
			
			hh->codeTop = (StackNode *) malloc (sizeof(StackNode));
			//hh->codeTop ��ջ��ջ��
			hh->codeTop->Next = NULL;//�˴������ʼ���������п��ܳ�����ѭ������
			hh->data = Root->data;
			while(temp->Pre != NULL)
			{
				if(temp->Pre->RChild == temp)
					Push(hh->codeTop, '1');
				else if(temp->Pre->LChild == temp)
					Push(hh->codeTop, '0');
				temp = temp->Pre;
			}
		}
		Encode(Root->LChild, store);
		Encode(Root->RChild, store);
	}
}

void EncodeChar(StackNode * head)
{//�˺����������ַ��Ĺ����������������
	StackNode * temp = head;
	while(temp->Next != NULL)
	{
		temp = temp->Next;
		printf("%c", temp->data);
	}
}

void bianli(Code * head)
{//�ú���������ÿ���ַ��ʹ���ַ�������������������һ��
	Code * temp = head;
	while(temp->Next != NULL)
	{
		temp = temp->Next;
		printf("%c\t", temp->data);
		EncodeChar(temp->codeTop);
		printf("\n");
	}
}

void seekEqualInLink(char data, Code * head)
{
	Code * temp = head->Next;
	while(temp != NULL)
	{
		if(temp->data == data)
			EncodeChar(temp->codeTop);
		temp = temp->Next;
	}
}

void EncodeText(char * text, Code * head)
{//�˺��������Ѹո������Text����ת���ɹ���������
	int i = 0;
	while(*(text + i) != '\0')
	{
		seekEqualInLink(*(text + i), head);
		i++;
	}
}



