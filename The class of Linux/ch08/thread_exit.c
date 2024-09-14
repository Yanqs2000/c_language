//thread_exit.c
//Ïß³ÌÍË³ö
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_fun(void *ptr);

int main(int argc, char **argv)
{
	int rtn;
	pthread_t thread_id;
	char *message = "new_thread";
	rtn = pthread_create(&thread_id, NULL, &thread_fun, (void*)message);
	if(rtn != 0)
	{
		perror("pthread_create error !");
		exit(1);
	}
	pthread_exit(0);
}

void *thread_fun(void *ptr)
{
	pthread_t new_thid;
	char *message;
	message = (char*)ptr;
	new_thid = pthread_self();
	printf("This is a new thread, thread ID is %u, message: %s\n", new_thid, message);
	sleep(2);
	printf("-----end-----\n");
}
