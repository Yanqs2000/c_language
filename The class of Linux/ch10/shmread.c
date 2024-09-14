//从共享内存中读取数据
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
    char buf[SHMSIZE];
    key = ftok("/tmp",1);
    shmid = shmget(key,SHMSIZE,SHM_R |SHM_W);
    if(shmid == -1){ 
        perror("shmget failed");
        exit(1);
    }
    shmptr = shmat(shmid,0,0);
    if(shmptr == (void *) -1){ 
        perror("shmat error");
        exit(2);
    }
    memcpy(buf,shmptr,strlen(shmptr) + 1);
    printf("%s\n",buf);
    if( shmdt(shmptr) == -1){ 
        perror("shmdt failed");
        exit(3);
    }
    return 0;
}
