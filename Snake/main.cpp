#include <stdio.h>
#include "Snake.h"
int main(void)
{
	char *a = "this a good day";
	int i = 0;
	while(*(a + i) != '\0')
	{
		printf("%c", *(a + i));
		i++;
	}
	printf("\n%d", i);
	return 0;
}
