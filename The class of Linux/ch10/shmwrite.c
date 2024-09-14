//创建共享内存，向共享内存中写入数据
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define SHMSIZE 4096

int main(int argc,char * argv[])
{
	int shmid;
	key_t key;
	void * shmptr;
	key = ftok("/tmp",1);
	if(argc != 2){
		printf("shmsrv needs a string. $shmsrv \"123456\"\n");
		exit(1);
	}
	if(key == -1){
		perror("ftok failed");
		exit(1);
	}

	shmid = shmget(key,SHMSIZE,IPC_CREAT | IPC_EXCL | 0600);
	if(shmid == -1){
		perror("shmget failed");
		exit(1);
	}
	printf("%d\n",shmid);
	shmptr = shmat(shmid,0,0);
	if(shmptr == (void *) -1){
		perror("shmat error");
		exit(1);
	}
	memcpy(shmptr,argv[1],strlen(argv[1]) + 1);
	if(shmdt(shmptr) == -1){
		perror("shmdt failed");
		exit(1);
	}
	return 0;
}
