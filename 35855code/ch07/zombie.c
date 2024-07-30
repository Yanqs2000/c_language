#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    if((pid = fork()) < 0){
        perror("fork failed");
        exit(1);
    }else if(pid == 0){
        printf("child...\n");
    }else{  
        printf("parent...\n");
        while(1);
    }
    return 0;
}
