//尝试从FIFO文件中读数据
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main(int argc,char * argv[]) 
{
    int fd; 
    char info[128] = {0};
    if((fd = open("file.fifo",O_RDWR)) == -1){ 
        printf("open FIFO failed\n");
        exit(1);
    }
    if(read(fd,info,sizeof(info)) == -1){ 
        printf("read failed\n");
        exit(2);
    }
    printf("%s\n",info);
    return 0;
}
