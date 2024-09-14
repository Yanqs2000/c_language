#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sig_handler(int sig)
{
	switch(sig){
		case SIGINT: 
			printf("signal SIGINT is caught\n");
			break;
		default:
			printf("other signal is caught\n");
	}
}

int main()
{
	int second = 0;
	if(signal(SIGINT,sig_handler) != SIG_ERR){
		while(1){
			printf("%d\n", second ++);
			sleep(1);
		}
	}
	return 0;
}
