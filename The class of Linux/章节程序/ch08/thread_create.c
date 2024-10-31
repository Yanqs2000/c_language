//thread_create.c
//线程创建
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_fun();

int main(int argc, char **argv)
{
	int rtn;
	pthread_t thread_id;
	rtn = pthread_create(&thread_id, NULL, &thread_fun, NULL);
	if(rtn != 0)
	{
		perror("pthread_create error !");
		exit(1);
	}
	sleep(1);
	return 0;
}

void *thread_fun()
{
	pthread_t new_thid;
	new_thid = pthread_self();
	printf("This is a new thread, thread ID is %u\n", new_thid);
	printf("-----end-----\n");
}
