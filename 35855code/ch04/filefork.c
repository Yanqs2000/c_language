#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
	int fd;
	int num;
	pid_t pid;
	char buf[20];
	bzero(buf,sizeof(buf));

	fd=open("f1",O_RDWR|O_TRUNC|O_CREAT,644);
	if(fd==-1)
	{
		perror("open");
		exit(1);
	}

	write(fd,"helloworld",10);
	
	lseek(fd,SEEK_SET,0);
	if((pid=fork())<0)
	{
		perror("fork");
	}
	else if(pid==0)
		{
			num=read(fd,buf,5);
			printf("i am child,my pid=%d, read num=%d bytes from f1(fd=%d):%s\n",getpid(),num,fd,buf);
		}
		else
		{
			num=read(fd,buf,5);
			printf("i am parent,my pid=%d, read num=%d bytes from f1(fd=%d):%s\n",getpid(),num,fd,buf);
			wait(NULL);
		}
	close(fd);
}
