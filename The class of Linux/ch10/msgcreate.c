//创建消息队列
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include"mymsg.h"

int main(int argc,char * argv[]) 
{
    int rtn;
    int msqid;
    key_t key;
    mymsg msginfo;
    key = ftok("/tmp",1);
    if(key == -1){ 
        perror("ftok failed");
        exit(1);
    }
    msqid = msgget(key,IPC_CREAT | IPC_EXCL | 0644);
    if(msqid == -1){ 
        perror("msgget failed");
        exit(2);        
    }
    return 0;
}
