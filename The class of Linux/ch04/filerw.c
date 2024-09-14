#include <fcntl.h>
main()
{
 	int fd;
 	int num;
 	char buf[20];
 	fd=open("f1",O_RDONLY);   // open f1 for read only
 	if(fd= = -1)
	{
 		perror("open");
 		exit(1);
	}

 	while((num=read(fd,buf,20))>0)
	{
		if(write(1,buf,num)<num)
		printf("write 1 less than should\n");
	}

 	close(fd);
}
