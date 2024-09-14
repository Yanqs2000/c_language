//pipe的典型用法2。
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int fds[2]; 
	int pid1,pid2;
	int sibling,self;
	if(pipe(fds) == 0)
	{
		if((pid1 = fork()) == 0)
		{
			close(fds[0]);
			self = getpid();
			write(fds[1],&self,sizeof(int));
			exit(1);
		}
		if((pid2 = fork()) == 0)
		{
			close(fds[1]);
			read(fds[0],&sibling,sizeof(int));
			printf("sibling pid = %d\n",sibling);
			exit(2);
		}
	}
	return 0;
}
