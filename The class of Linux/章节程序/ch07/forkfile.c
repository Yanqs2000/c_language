#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char* argv[])
{
    pid_t pid;
    int fd;
    char * info = "hello world";
    char buf[64] = {0};
    int nBytes;
    fd = open("file",O_RDWR | O_CREAT);
    if(fd < 0){
        perror("open file failed");
        exit(1);
    }

    printf("before fork\n");
    if((pid = fork()) < 0){
        perror("fork error");
    }
    else if(pid == 0){
        if((nBytes = write(fd, info, strlen(info))) < 0){
            perror("write failed");
        }
        exit(0);
    }else{
        sleep(1);
        lseek(fd, 0,SEEK_SET);
        if((nBytes = read(fd, buf, 64)) < 0){
            perror("read failed");
        }
        printf("%s\n",buf);
    }
    exit(0);
}
