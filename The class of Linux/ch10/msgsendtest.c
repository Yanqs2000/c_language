//·¢ËÍÏûÏ¢
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
    if(argc != 2){
        printf("sendmsg needs a string.exa $sendmsg \"123456\"\n");
        exit(0);
    }
    if(key == -1){ 
        perror("ftok failed");
        exit(2);
    }
    msqid = msgget(key,0600);
    if(msqid == -1){ 
        perror("msgget failed");
        exit(3);        
    }
    msginfo.mtype = 1;
    memcpy(&msginfo.mtext,argv[1],strlen(argv[1]) + 1);
    rtn = msgsnd(msqid,(pmymsg)&msginfo,strlen(msginfo.mtext) + 1,0); 
    if(rtn == -1){ 
        perror("msgsnd failed");
        exit(4);
    }
    printf("you send a message\"%s\" to msq %d\n",argv[1],msqid);
    return 0;
}
