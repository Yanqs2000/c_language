//thread_rdwr.c
//“读者—写者”问题
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define NUM 100

void ReadFile(int id);
void WriteFile(int id);
void RandomSleep();
void *Reader(void *id);
void *Writer(void *id);

int ReaderNum=0, WriterNum=0;
pthread_rwlock_t rwlock;

int main()
{
	int id[NUM];
	int i;
	pthread_t readthread[NUM], writethread[NUM];
	pthread_rwlock_init(&rwlock, NULL);
	
	srand(time(NULL));
	for(i=0; i<NUM; i++)
	{	
		id[i] = i;
		pthread_create(&readthread[i], NULL, Reader, (void *)&id[i]);
		pthread_create(&writethread[i], NULL, Writer, (void *)&id[i]);
	}
	
	for(i=0; i<NUM; i++)
	{
		pthread_join(readthread[i], NULL);
		pthread_join(writethread[i], NULL);
	}

	pthread_exit(0);
}

void *Reader(void *id)
{
	RandomSleep();
	pthread_rwlock_rdlock(&rwlock);
	ReaderNum++;
	ReadFile(*((int *)id));
	ReaderNum--;
	pthread_rwlock_unlock(&rwlock);	
}

void *Writer(void *id)
{
	RandomSleep();
	pthread_rwlock_wrlock(&rwlock);
	WriterNum++;
	WriteFile(*((int *)id));
	WriterNum--;
	pthread_rwlock_unlock(&rwlock);	
}

void RandomSleep()
{
    struct timespec tv;
    tv.tv_sec = 0;
    tv.tv_nsec = (long)(rand()*1.0/RAND_MAX * 999999999);
    nanosleep(&tv, NULL);
}

void ReadFile(int id)
{
  printf("Reader ID: %d; Reader Num: %d; Writer Num %d\n", id, ReaderNum, WriterNum);
  RandomSleep();
}

void WriteFile(int id)
{
  printf("Writer ID: %d; Reader Num: %d; Writer Num %d\n", id, ReaderNum, WriterNum);
  RandomSleep();
}
