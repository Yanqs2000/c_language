//thread_mutex_ticket.c
//用互斥锁实现多线程的同步互斥
//应用于抢票
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //定义一个互斥锁
int ticket = 2; //三个线程抢的票数

void *thread_func() 
{
	pthread_mutex_lock(&mutex); //抢到锁
	char input[10];
	printf("please:\n");
	scanf("%s", input);
	if (ticket > 0) //仍有票
	{ 
		if(strcmp(input, "buy") == 0)
		{
			int num = 1; //随机抢1张票
			if (num > ticket) 
			{
				num = ticket;
			}
			ticket -= num;
			sleep(2); //给其他线程机会
			printf("thread %d get %d ticket,remain %d ticket\n", (int)pthread_self(), num, ticket);
			pthread_mutex_unlock(&mutex); //释放锁
			if(ticket == 0)
			{
				return NULL;
			}
		}
		else 
		{
			sleep(2); //给其他线程机会
			pthread_mutex_unlock(&mutex); //释放锁
			if(ticket == 0)
			{
				return NULL;
			}
		}
	}
	else
	{
		printf("no more ticket\n");
		return NULL;
	}
}

int main()
{
    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, &thread_func,NULL);
    pthread_create(&tid2, NULL, &thread_func,NULL);
    pthread_create(&tid3, NULL, &thread_func,NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_mutex_destroy(&mutex); //销毁锁
    printf("process over\n");
    return 0;
}