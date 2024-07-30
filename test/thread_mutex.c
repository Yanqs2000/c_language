//thread_mutex_ticket.c
//�û�����ʵ�ֶ��̵߳�ͬ������
//Ӧ������Ʊ
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //����һ��������
int ticket = 2; //�����߳�����Ʊ��

void *thread_func() 
{
	pthread_mutex_lock(&mutex); //������
	char input[10];
	printf("please:\n");
	scanf("%s", input);
	if (ticket > 0) //����Ʊ
	{ 
		if(strcmp(input, "buy") == 0)
		{
			int num = 1; //�����1��Ʊ
			if (num > ticket) 
			{
				num = ticket;
			}
			ticket -= num;
			sleep(2); //�������̻߳���
			printf("thread %d get %d ticket,remain %d ticket\n", (int)pthread_self(), num, ticket);
			pthread_mutex_unlock(&mutex); //�ͷ���
			if(ticket == 0)
			{
				return NULL;
			}
		}
		else 
		{
			sleep(2); //�������̻߳���
			pthread_mutex_unlock(&mutex); //�ͷ���
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
    pthread_mutex_destroy(&mutex); //������
    printf("process over\n");
    return 0;
}