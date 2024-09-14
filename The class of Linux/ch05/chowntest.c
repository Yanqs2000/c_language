#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
	struct stat buf;
	
	unlink("f1");
	system("touch f1");

	int fd;
    fd = open("f1",O_CREAT|O_RDWR,0644);
 	write(fd,"helloworld",10);

	ftruncate(fd,1);
	close(fd);

	stat("f1",&buf);
	printf("old userid:%d  grpid:%d\n",buf.st_uid,buf.st_gid);

	chown("f1",-1,502);
	stat("f1",&buf);

	printf("new userid:%d  grpid:%d\n",buf.st_uid,buf.st_gid);
}
