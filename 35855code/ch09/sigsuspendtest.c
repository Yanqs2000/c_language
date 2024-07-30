#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<signal.h>

void sig_handler(int sig)
{
    switch(sig){
        case SIGQUIT:
            printf("SIGQUIT is caught\n");
            break;
        default:
            printf("other signal is caught\n");
    }
}
int main()
{
    sigset_t set;

    signal(SIGQUIT,sig_handler);
    signal(SIGINT,sig_handler);
    sigemptyset(&set);
    sigaddset(&set,SIGINT);
    printf("please enter Ctrl-\\...\n");
    sigsuspend(&set);
    printf("after sigsuspend returns\n");
    return 0;
}
