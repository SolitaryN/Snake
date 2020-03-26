#include <stdio.h>
#include <stdlib.h>
#include "DefineStru.h"

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
	int i = 0;
	printf("每个字符对应的权值表：");
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

void Pop(StackNode *top)//出栈函数
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

void InsertLink(LinkNode *head, char data) //此处的单链表插入用的是头插法
{//此函数用来在链表中生成结点并保存发现新的字符
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

void JudegeAppear(LinkNode *head, char data) //判断字符是否在这个链表中出现过，如果没出现过，返回TRUE保存
{
	LinkNode *temp;
	temp = head->Next;
	while (temp != NULL)
	{
		if (data == temp->data)//出现过时
		{
			temp->weight++;
			return ; 
		}
		temp = temp->Next;
	}
	//函数执行到这，说明未发现这个字符出现过
	InsertLink(head, data); //如果新进入的字符是新字符，就单链表中创建一个新的节点用来保存，未出现过
	return ;
}

void Statistic(LinkNode *head, char *str)
{//此函数用来统计字符串中的字符的权值
	int i = 0;
	while (*(str + i) != '\0')
	{
		JudegeAppear(head, *(str + i)); //判断是否字符出现过
		i++;
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

void leafNodePrint(LinkNode *Root)
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
{//此函数用来对Huffman树中的叶子结点字符进行编码，生成哈夫曼编码
	//生成的哈夫曼编码编写在栈中（栈的结点类型StackNode）
	if (Root != NULL)
	{
		if (Root->LChild == NULL && Root->RChild == NULL)
		{
			LinkNode * temp = Root;
			Code * hh = (Code *) malloc (sizeof(Code));
			hh->Next = store->Next;
			store->Next = hh;
			
			hh->codeTop = (StackNode *) malloc (sizeof(StackNode));
			//hh->codeTop 是栈的栈顶
			hh->codeTop->Next = NULL;//此处必须初始化，否则有可能出现死循环错误
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
{//此函数用来把字符的哈夫曼编码输出出来
	StackNode * temp = head;
	while(temp->Next != NULL)
	{
		temp = temp->Next;
		printf("%c", temp->data);
	}
}

void bianli(Code * head)
{//该函数用来把每个字符和存放字符哈夫曼编码的链表遍历一下
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
{//此函数用来把刚刚输入的Text内容转化成哈夫曼编码
	int i = 0;
	while(*(text + i) != '\0')
	{
		seekEqualInLink(*(text + i), head);
		i++;
	}
}



