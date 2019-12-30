#include <stdio.h>
#include "Snake.h"
int main(void)
{
	//初始化一下Top和Head
	Top->Next = NULL;
	Head->Next = NULL;
	Statistic("this is a good day"); 
	Pop(Top);
	printf("\n");
	LinkPrintWeight(Head);
	return 0;
}
