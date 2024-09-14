#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
main()
{
	pid_t id;

	id=fork();//2
	if(id<0)
	{
		perror("fork");
		exit(1);//1
	}
	else if(id==0)//1
	{  
		system("ls -l");//1
		sleep(1);//1
		exit(1);//1
	}
	else
	{
		printf("child pid=%d\n",id);//1
		wait();//1
		sytem("ps -aux");//1
	}
}