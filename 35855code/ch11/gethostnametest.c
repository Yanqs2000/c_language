#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	char buf[30];
	if(gethostname(buf,sizeof(buf)-1)==-1)
	{
		perror("gethostname");
		exit(1);
	}
	printf("hostname=%s\n",buf);
	return 0;
}
