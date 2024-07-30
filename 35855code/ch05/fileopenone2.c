#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
main()
{
	int fd;
	int len;
	char buf[200];
	fd = open("test1.txt",O_RDWR|O_TRUNC);//1
	if(fd1==-1)
	{
		perror("open");
		exit(1);
	}
	write(fd1,"Hello World!\n",sizeof("Hello World!\n"));//1
	len = lseek(fd, 0, SEEK_END);//2
	lseek(fd, 0, SEEK_SET);//2
	read(fd, buf,len);//2
	printf("%s",buf);//1
	close(fd);//1
}