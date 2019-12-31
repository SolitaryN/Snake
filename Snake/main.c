#include <stdio.h>
#include <string.h>
#include "Snake.h"
int main(void)
{
	//��ʼ��һ��Top��Head
	//����Top��Head�����Ƕ���ͷ��� 
	StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
	LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));
	Top->Next = NULL;
	Head->Next = NULL;
	char *temp = "hhhwwwooopppppp";
	Statistic(Top, Head, temp);
	// Pop(Top);//��ջ����
	// printf("\n");

	printf("���ÿ���ַ���Ӧ��Ȩֵ��\n");
	LinkPrintWeight(Head);
	
	printf("���ɵ�Haffman����Ҷ�ӽ���data���ֵ��\n");
	LinkNode * Root = Huffman(Head);
	leafNodePrint(Root);
	printf("\n");

	printf("���ÿ���ַ���Huffman���룺\n");
	//ע�⣺���ı���洢��ջ�У���ջ����Ȼ�͵����˹���
	Transform(Root);
	initRoot(Root);
	Code * store = (Code *) malloc (sizeof(Code));
	Encode(Root, store);
	bianli(store);
	return 0;
}
