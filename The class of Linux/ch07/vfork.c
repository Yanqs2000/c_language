#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int global; 

int main(int argc,char* argv[]) 
{
	int var = 0;
	pid_t pid;

	printf("before fork\n");

	if((pid = vfork()) < 0){
		perror("fork error");
	}
	else if(pid == 0){
		global ++;
		var ++;
		_exit(0);
	}
	sleep(3);
	printf("pid = %d global = %d var = %d\n",getpid(), global, var);
	exit(0);
}
