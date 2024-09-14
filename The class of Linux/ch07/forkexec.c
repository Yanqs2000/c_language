#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char* argv[]) 
{
    int var = 0;
    int fd; 
    pid_t pid;
    
    printf("before fork\n");
    if((pid = fork()) < 0){
        perror("fork error");
    }
    else if(pid == 0){
        fd = open("restdout", O_RDWR | O_CREAT, 0644);      
        if(fd < 0){
            perror("open failed");
            exit(1);
        }
        dup2(fd, 1);//重定向标准输出到文件restdout
        execl("/bin/ls","ls","-l",NULL);
        perror("execl failed");
    }else{  
        printf("parent writes to stdout\n");
    }
    exit(0);
}
