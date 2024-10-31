#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void sig_handler(int sig)
{
    switch(sig){
        case SIGPIPE:
            printf("Get SIGPIPE signal:reader does not exist\n");
        case SIGCHLD:
            printf("Get SIGCHLD signal:child exits\n");
    }
}
int main()
{
    pid_t pid;
    char data[32] ={0};
    char buf[32] = {0};
	int num=-2;
    int fds[2]; 
    signal(SIGCHLD,sig_handler);
    if(pipe(fds) == 0){
        
        pid = fork(); 
        if(pid == 0){

		close(fds[0]);
            signal(SIGCHLD,SIG_DFL);
            signal(SIGPIPE,sig_handler);
		sprintf(data,"hello");
            write(fds[1],data,strlen(data));
	printf("child waiting 3s for parent's reading\n");
	sleep(3);

close(fds[1]);
            exit(0);
        }else if(pid > 0){
            close(fds[1]);
	printf("parent waiting 2s for child's writing\n");
		sleep(2);


            num=read(fds[0],buf,sizeof(buf));
		if(num==-1)
		perror("parent read");
else
            printf("parent:readnum:%d  readstr:%s\n",num,buf);
	printf("parent waiting 3s for child's exit\n");
		sleep(3);


            num=read(fds[0],buf,sizeof(buf));
		if(num==-1)
		perror("parent read");
else
            printf("parent:readnum:%d  readstr:%s\n",num,buf);
        }
    }
    return 0;
}
