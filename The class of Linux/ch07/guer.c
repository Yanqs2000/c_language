#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(int argc,char* argv[]) 
{
    int var = 0;
    pid_t pid;
    
    if((pid = fork()) < 0){
        perror("fork error");
    }
    else if(pid == 0){
	printf("pid=%d ppid=%d\n",getpid(),getppid());
	sleep(2);
	printf("pid=%d ppid=%d\n",getpid(),getppid());
    }else{  
	exit(0);
}
    exit(0);
}
