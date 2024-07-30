#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void sig_handler(int sig)
{
    switch(sig){
        case SIGABRT:
            printf("signal SIGABRT is caught\n");
            break;
        default:
            printf("other signal is caught\n");
    }
}

int main()
{
    signal(SIGABRT,sig_handler);
    abort();
    printf("after abort()\n");
    return 0;
}
