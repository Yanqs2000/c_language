#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

static void
sig_handler(int sig)
{
	switch(sig){
		case SIGQUIT:
			printf("SIGQUIT is caught\n");
			break;
		default:
			printf("other signal is caught\n");
	}
}

int main(void)
{
	int rtn;
	sigset_t set, oldset;

	if (signal(SIGQUIT, sig_handler) == SIG_ERR)
		printf("signal() error\n");
	
	rtn = sigpending(&set);
	if(rtn == 0){
		rtn = sigismember(&set, SIGQUIT);
		if(rtn == 1){
			printf("SIGQUIT is pending\n");
		}else{
			printf("SIGQUIT is not pending\n");
		}
	}else{
		printf("sigpending() error\n");
		exit(1);
	}
	
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);

	if (sigprocmask(SIG_SETMASK, &set, &oldset) == -1)
		printf("set new procmask error\n");

	printf("sleep 3 seconds and please enter Ctrl-\\...\n");

	sleep(3);	

/* try to get the pending signal again */

	sigemptyset(&set);
	rtn = sigpending(&set);
	if(rtn == 0){
		rtn = sigismember(&set, SIGQUIT);
		if(rtn == 1){
			printf("SIGQUIT is pending\n");
		}else{
			printf("SIGQUIT is not pending\n");
		}
	}else{
		printf("sigpending() error\n");
		exit(1);
	}

	if(sigprocmask(SIG_UNBLOCK, &set, NULL) == -1){
		printf("unblock SIGQUIT error\n");
		exit(3);
	}

/*reset oldset*/
	sigprocmask(SIG_SETMASK, &oldset, NULL);
	return 0;
}
