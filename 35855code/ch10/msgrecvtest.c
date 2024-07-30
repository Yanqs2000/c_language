//接收消息
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
        exit(0);
    }
    msqid = msgget(key,0644);
    if(msqid == -1){ 
        perror("msgget failed");
        exit(2);        
    }
    //recv msg from message queue   
    rtn = msgrcv(msqid,(pmymsg)&msginfo,512,1,0);
    if(rtn == -1){ 
        perror("msgrcv failed");
        exit(3);
    }
    printf("%s\n",msginfo.mtext);
    return 0;
}
