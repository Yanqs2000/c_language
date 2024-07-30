#include <errno.h>
#include <stdio.h>
int main()
{
	printf("errno1=%d\n",errno);
	if(fopen("any","r")==NULL)
	{
	    perror("fopen");
	}
	return 0;
}
