#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
	sigset_t oldset;
	int member;
	if(sigprocmask(SIG_BLOCK, NULL, &oldset) == 0){
		if((member = sigismember(&oldset, SIGINT)) == 1){
			printf("signal SIGINT is in oldset\n");
		}else if(member == 0){
			printf("signal SIGINT is not in oldset\n");
		}else{
			printf("sigismember error\n");
		}
	}
	return 0;
}
