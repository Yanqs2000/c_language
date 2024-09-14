#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd1,fd2,fd3,fd4;
 	fd1 = open("f1",O_RDWR);
	fd2 = open("f2",O_RDWR);
 	fd3 = open("f3",O_RDWR);
	close(fd2);
	fd4 = open("f4",O_RDWR);
 	printf("fd1=%d\nfd3=%d\nfd4=%d\n",fd1,fd3,fd4);
 	close(fd1);
 	close(fd2);
 	close(fd4);
}
