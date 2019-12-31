#include <stdio.h>
#include "Snake.h"
int main(void)
{
	//初始化一下Top和Head
	//创建Top和Head，它们都带头结点 
	StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
	LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));
	Top->Next = NULL;
	Head->Next = NULL;
	char * temp = "wwwwangazzz";
	Statistic(Top, Head, temp);

	Pop(Top);
	printf("\n");

	LinkPrintWeight(Head);
	
	LinkNode * Root = Huffman(Head);
	leafNodePrint(Root);
	return 0;
}
