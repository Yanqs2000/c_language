//创建FIFO文件，并将argv[1] 写入文件
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int main(int argc,char * argv[]) 
{
    int fd; 
    int rtn;
    if(argc != 2){
        printf("need a string\n");
        exit(1);
    }
    
    if(mkfifo("file.fifo", 0644) == -1){ 
        if(errno == EEXIST){
            printf("file.fifo exists\n");
        }
    }

    if((fd = open("file.fifo",O_RDWR)) == -1){ 
        printf("open FIFO failed\n");
        exit(2);
    }
    if((rtn = write(fd,argv[1],strlen(argv[1]) + 1)) == -1){ 
        printf("write failed\n");
        exit(3);
    }
    pause();
    return 0;
}
