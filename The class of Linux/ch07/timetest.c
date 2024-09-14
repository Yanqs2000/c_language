#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd;
    time_t t;
    struct tm * ptm;
    char datetime[128] = {0};

    if(time(&t) == (time_t)-1){
		perror("time() failed ");
		exit(1);
    }
    if((ptm = localtime(&t)) == NULL){
    	perror("localtime failed");
        exit(2);
	}
     if(strftime(datetime,sizeof(datetime),"%D",ptm) == 0){
		perror("strftime failed");
		exit(3);
	}
     if((fd = open("out",O_RDWR | O_CREAT, 0644)) == -1){
     	perror("open() failed");
		exit(4);
	}
     if(write(fd, datetime, strlen(datetime)) == -1){
     	perror("write() failed");
		exit(5);
	}
     close(fd) ;
     printf("%s\n",datetime);
     return 0;
}
