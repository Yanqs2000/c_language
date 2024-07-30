#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
    int status;
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork failed");
        exit(0);
    }else if(pid == 0){
        printf("child...\n");
        exit(0);
    }else{
        wait(&status);
        printf("termination status :%d\n",status);
        if(WIFEXITED(status)){
            printf("exit status :%d\n",WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("signal number %d\n",WTERMSIG(status));
        }
    }
    return 0;
}
