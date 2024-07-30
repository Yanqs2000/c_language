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
    char data[32] = "hello";
    int fds[2]; 
    signal(SIGCHLD,sig_handler);//设置当前进程对对SIGCHLD信号捕捉函数
    if(pipe(fds) == 0){
        
        pid = fork(); 
        if(pid == 0){
		printf("Child is waiting 2s for closing pipereadend of parent\n");
		sleep(2);
		close(fds[0]);//关闭子进程管道读端
            signal(SIGCHLD,SIG_DFL);//设置子进程对SIGCHLD信号默认处理方式
            signal(SIGPIPE,sig_handler);//设置子进程对SIGPIPE信号捕捉函数
            write(fds[1],data,strlen(data));//子进程写data进入管道

        }else if(pid > 0){
	    close(fds[0]);//关闭父进程管道读端
            wait(NULL);
            }
    }
    return 0;
}
