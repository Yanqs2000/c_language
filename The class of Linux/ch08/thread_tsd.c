//thread_tsd.c
//线程私有数据编程实例
#include<stdio.h>
#include<string.h>
#include<pthread.h>

pthread_key_t key;

void *thread2_fun(void *arg)
{
	int tsd=5;
	
	printf("thread2 is running, thread2's id is:%u\n", pthread_self());
	pthread_setspecific(key, (void*)tsd);
	printf("thread2 returns %d\n", pthread_getspecific(key));
}

void *thread1_fun(void *arg)
{
	int tsd = 10;
	pthread_t thread2;
	
	printf("thread1 is running, thread1's id is:%u\n",pthread_self());
	pthread_setspecific(key, (void*)tsd);
	pthread_create(&thread2, NULL, &thread2_fun, NULL);
	sleep(3);
	printf("thread1 returns %d\n", pthread_getspecific(key));
}

int main()
{

	pthread_t thread1;
	
	printf("beginning.....\n");
	pthread_key_create(&key, NULL);
	pthread_create(&thread1, NULL, &thread1_fun, NULL);
	sleep(5);
	pthread_key_delete(key);
	printf("--------end--------\n");
	
	pthread_exit(0);

}
