//thread_mutex.c
//用互斥锁实现多线程的同步互斥
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int count = 0;

void *thread_fun();

int main(int argc, char **argv)
{
	int rtn1, rtn2;
	pthread_t thread_id1;
	pthread_t thread_id2;
	
	rtn1 = pthread_create(&thread_id1, NULL, &thread_fun, NULL);
	rtn2 = pthread_create(&thread_id2, NULL, &thread_fun, NULL);
	
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	
	pthread_exit(0);
}

void *thread_fun()
{
	pthread_mutex_lock(&mutex);
	count++;
	sleep(1);
	printf("count = %d\n", count);
	pthread_mutex_unlock(&mutex);
}
