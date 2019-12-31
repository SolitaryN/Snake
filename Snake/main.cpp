#include <stdio.h>
#include "Snake.h"
int main(void)
{
	//初始化一下Top和Head
	Top->Next = NULL;
	Head->Next = NULL;
	char * temp = "aaaowpanbbdflcb";
	Statistic(temp); 
	Pop(Top);
	printf("\n");
	LinkPrintWeight(Head);
	// initWithRoot(Head);
	leafNodePrint(Huffman(Head));
	return 0;
}
