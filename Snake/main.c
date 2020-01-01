#include "Snake.h"
int main(void)
{
	//初始化一下Top和Head
	//创建Top和Head，它们都带头结点 
	StackNode * Top = (StackNode *) malloc (sizeof(StackNode));
	LinkNode  * Head = (LinkNode *) malloc (sizeof(LinkNode));
	Top->Next = NULL;
	Head->Next = NULL;
	char * temp = "This is a good day, and I think I will have good future.";
	Statistic(Top, Head, temp);
	LinkPrintWeight(Head);
	
	printf("生成的Haffman树的叶子结点的data域的值：\n");
	LinkNode * Root = Huffman(Head);
	leafNodePrint(Root);
	printf("\n");

	printf("输出每个字符的Huffman编码：\n");
	//注意：它的编码存储在栈中，出栈后自然就倒置了过来
	Transform(Root);
	initRoot(Root);
	Code * store = (Code *) malloc (sizeof(Code));//头节点
	store->Next = NULL;//初始化一下，避免可能出现死循环问题
	Encode(Root, store);
	bianli(store);
	return 0;
}
