#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
void sig_handler(int sig)
{
    printf("begin signal handler......\n");
    switch(sig){
        case SIGALRM:
            printf("SIGALRM is caught\n");
            break;
        default:
            printf("other signal is caught\n");
    }
}

int main(void)
{
    int rtn;

    if (signal(SIGALRM, sig_handler) != SIG_ERR){
        rtn = alarm(5);
        printf("first time alarm returns %d second\n",rtn);
        sleep(1);
        rtn = alarm(5);
        printf("last alarm remains %d second\n",rtn);
		rtn = pause();
		printf("pause returns %d\n",rtn);
    }
    return 0;   
}
