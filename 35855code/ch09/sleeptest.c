#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

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
	int rtn;
	if(signal(SIGQUIT,sig_handler) != SIG_ERR){
		printf("please enter Ctrl-\\\n");
		rtn = sleep(1000);
		printf("sleep returns and %d seconds remain\n",rtn);
		rtn = sleep(3);
		printf("sleep finishes and returns %d seconds\n",rtn);
	}
	return 0;
}
