#include "Snake.h"
int main(void)
{
	//��ʼ��һ��Top��Head
	//����Top��Head�����Ƕ���ͷ��� 
	StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
	LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));
	Top->Next = NULL;
	Head->Next = NULL;
	char * temp = "This is a good day, and I think I will have good future.";
	Statistic(Top, Head, temp);
	LinkPrintWeight(Head);
	
	printf("���ɵ�Haffman����Ҷ�ӽ���data���ֵ��\n");
	LinkNode * Root = Huffman(Head);
	leafNodePrint(Root);
	printf("\n");

	printf("���ÿ���ַ���Huffman���룺\n");
	//ע�⣺���ı���洢��ջ�У���ջ����Ȼ�͵����˹���
	Transform(Root);
	initRoot(Root);
	Code * store = (Code *) malloc (sizeof(Code));//ͷ�ڵ�
	store->Next = NULL;//��ʼ��һ�£�������ܳ�����ѭ������
	Encode(Root, store);
	bianli(store);
	return 0;
}
