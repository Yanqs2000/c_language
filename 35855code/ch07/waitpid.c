#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define CHILDS  5
int main(int argc, char* argv[]) 
{
    int i, status; 
    pid_t pids[CHILDS];
    pid_t pid_w = -1;
    for(i = 0; i < CHILDS; i++){//创建5个子进程
        if((pids[i] = fork()) < 0){
            perror("fork failed");
            exit(-1);
        }else if(pids[i] == 0){
            sleep(i);
            printf("%d created\n",getpid());
            exit(i);
        }
    }
    pid_w = waitpid(pids[4], &status, 0);//等待PID为pids[4]的子进程结束
    printf("child(PID:%d) exits %d\n", pid_w, status);
    return 0;   
}
