//删除消息队列
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
    key = ftok("/tmp",1);
    if(key == -1){ 
        perror("ftok failed");
        exit(0);
    }
    msqid = msgget(key,0644);
    if(msqid == -1){ 
        perror("msgget failed");
        exit(1);        
    }
    rtn = msgctl(msqid,IPC_RMID,NULL);
    if(rtn == -1){ 
        perror("msgctl failed");
        exit(3);
    }
    return 0;
}
