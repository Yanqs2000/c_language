//thread_join.c
//Ïß³ÌµÈ´ý
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_fun(void *ptr);

int main(int argc, char **argv)
{
	int rtn1, rtn2;
	pthread_t thread_id1;
	pthread_t thread_id2;
	char *message1 = "new_thread1";
	char *message2 = "new_thread2";
	rtn1 = pthread_create(&thread_id1, NULL, &thread_fun, (void*)message1);
	if(rtn1 != 0)
	{
		perror("pthread_create error !");
		exit(1);
	}
	rtn2 = pthread_create(&thread_id2, NULL, (void*)thread_fun, (void*)message2);
	if(rtn2 != 0)
	{
		perror("pthread_create error !");
		exit(1);
	}
	
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	
	printf("thread1 return %d\n", rtn1);
	printf("thread2 return %d\n", rtn2);

	return 0;
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
