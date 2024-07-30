//判断子进程是否存在
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<signal.h>
#include<errno.h>

int main(void)
{
    pid_t pid;
    int rtn;
    pid = fork(); 
    if(pid == 0){
        exit(1);
    }else if(pid > 0){
        wait(NULL);
        rtn = kill(pid,0);
        if(rtn == -1){ 
            if(errno == ESRCH){ 
                printf("process does not exit\n");
            }
        }
    }
    return 0;   
}
