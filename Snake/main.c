#include "Snake.h"
#include <string.h>
#define STLEN 200
int main(void)
{
	//��ʼ��һ��Top��Head
	//����Top��Head�����Ƕ���ͷ��� 
	StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
	LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));
	Top->Next = NULL;
	Head->Next = NULL;
	char temp[STLEN];
	fgets(temp, STLEN, stdin);
	temp[strlen(temp) - 1] = '\0';//�ѻ��з���λ'\0'
	Statistic(Top, Head, temp);
	LinkPrintWeight(Head);
	
	printf("���ɵ�Haffman����Ҷ�ӽ���data���ֵ��\n");
	LinkNode * Root = Huffman(Head);//���������ĸ��ڵ�
	leafNodePrint(Root);

	printf("\n���ÿ���ַ���Huffman���룺\n");
	//ע�⣺���ı���洢��ջ�У���ջ����Ȼ�͵����˹���
	Transform(Root);
	initRoot(Root);
	Code * store = (Code *) malloc (sizeof(Code));//ͷ�ڵ�
	store->Next = NULL;//��ʼ��һ�£�������ܳ�����ѭ������
	Encode(Root, store);
	bianli(store);
	return 0;
}
