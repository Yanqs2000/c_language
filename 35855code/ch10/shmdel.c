//É¾³ý¹²ÏíÄÚ´æ
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
    key = ftok("/tmp",1);
    shmid = shmget(key,SHMSIZE,SHM_R |SHM_W);
    if(shmid == -1){ 
        perror("shmget failed");
        exit(1);
    }
    if(shmctl(shmid,IPC_RMID,NULL) == -1){ 
        perror("shmctl failed");
        exit(1);
    }

    return 0;
}
