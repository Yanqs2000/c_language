#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
main()
{
int fd1,fd2;
int num;
char buf[20];
fd1 = open("f1",O_RDWR|O_TRUNC);
if(fd1==-1)
{
perror("open");
exit(1);
}
printf("fd1 is %d \n",fd1);
fd2 = open("f1",O_RDWR);
if(fd2==-1)
{
perror("open");
exit(1);
}
printf("fd2 is %d \n",fd2);
num=write(fd1,"hello world!",12);
printf("fd1:write num=%d bytes into f1\n",num);
num=read(fd2, buf,20);
buf[num]=0;
printf("fd2:read  %d bytes from f1: %s\n",num, buf);
close(fd1);
close(fd2);

}