#include <stdio.h>
#include <stdlib.h>
#include "DefineStru.h"

void InsertLink(LinkNode *head, char data) //此处的单链表插入用的是头插法
{
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

void Push(StackNode *top, char data) //入栈函数, top为栈顶
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
{//这个函数用来遍历单链表，并输出data和weight
	LinkNode *temp = head;
	while (temp->Next != NULL)
	{
		temp = temp->Next;
		printf("%c %d\n", temp->data, temp->weight);
	}
}

void Pop(StackNode *top)//出栈函数,没什么用，可以删除
{
	while (top->Next != NULL)
	{
		top = top->Next;
		printf("%c ", top->data);
	}
}

int JudegeAppear(LinkNode *head, char data) //判断字符是否在这个链表中出现过，如果没出现过，返回TRUE保存
{
	LinkNode *temp;
	temp = head->Next;
	int j = 0; //此处的j用来判断是否将要入栈的字符为第一次出现的字符
	while (temp != NULL)
	{
		if (data == temp->data)
		{
			temp->weight++;
			j = 1;
			return TRUE; //出现过
		}
		temp = temp->Next;
	}
	if (j == 0)
		InsertLink(head, data); //如果新进入的字符是新字符，就单链表中创建一个新的节点用来保存，未出现过
	return FALSE;
}

void Statistic(StackNode *Top, LinkNode *head, char *str)
{//此函数用来统计字符串中的字符的权值
	int i = 0;
	while (*(str + i) != '\0')
	{
		JudegeAppear(head, *(str + i)); //判断是否字符出现过
		Push(Top, *(str + i));			//入栈
		i++;
	}
}

void loopLink(LinkNode *head)
{//此函数用来进行对单链表进行遍历并输出weight,没什么用，可删除
	LinkNode *temp = head;
	while (temp != NULL)
	{
		temp = temp->Next;
		printf("%d ", temp->weight);
	}
}

LinkNode * FindMin (LinkNode * head)//此函数可行,已验证
{//此函数用来进行在链表中找到weight最小的节点的地址，并返回该地址
	LinkNode * temp = head;
	LinkNode * min;
	int bi = 100000000; //用来找权值最小的结点
	while (temp->Next != NULL) //遍历单链表
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

void DeleteNode(LinkNode * s)//删除单链表中的数据，已验证此函数可行
{
	s->Pre->Next = s->Next;
	if(s->Next != NULL)
	{
		s->Next->Pre = s->Pre;
	}
}

LinkNode * CreatNode(LinkNode * a, LinkNode * b)//已检验，函数可行
{//此函数用来进行对两个节点进行合并成一颗树
	LinkNode * newNode = (LinkNode *) malloc (sizeof(LinkNode));
	newNode->weight = a->weight + b->weight;
	newNode->LChild = a;
	newNode->RChild = b;
	return newNode;
}

void ConnectLink(LinkNode * head, LinkNode * newNode)
{//此函数用来连接生成的树的根与链表连接
	newNode->Next = head->Next;
	if(head->Next != NULL)
	{
		head->Next->Pre = newNode;
	}
	newNode->Pre = head;
	head->Next = newNode;
}

LinkNode * Huffman(LinkNode * head) //生成Huffman一颗树，并且返回Root
{	//已验证，此函数有效
	//保持head指针不发生变动
	while(head->Next->Next != NULL)//单链表最后肯定会剩下一个节点，Root
	{
		LinkNode * a = FindMin(head);//找weight最小的节点
		DeleteNode(a);//找到之后就在单链表中删除这个节点
		LinkNode * b = FindMin(head);
		DeleteNode(b);
		LinkNode * c = CreatNode(a, b);//用找到的两个weight最小的节点生成一颗树
		ConnectLink(head, c);//把新生成的树的根节点连接到单链表中
	}
	return head->Next;
}

void leafNodePrint(LinkNode *Root)//此函数用来做实验，没事么用，可删
{//此函数用来遍历叶子节点，并输出它们的data域
	if (Root != NULL)
	{
		if (Root->LChild == NULL && Root->RChild == NULL)
			printf("%c ", Root->data);
		leafNodePrint(Root->LChild);
		leafNodePrint(Root->RChild);
	}
}

void Transform(LinkNode * Root)
{//把结点中的Pre指针指向父节点
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
{//把Root的Pre指针化为空
	Root->Pre = NULL;
}

void Encode(LinkNode *Root, Code * store)//运用头插法
{
	if (Root != NULL)
	{
		if (Root->LChild == NULL && Root->RChild == NULL)
		{
			LinkNode * temp = Root;
			Code * hh = (Code *) malloc(sizeof(Code));
			store->Next = hh;
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

void bianli(Code * head)
{
	Code * temp = head;
	while(temp != NULL)
	{
		temp = temp->Next;
		Pop(temp->codeTop);
	}
}


