#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
union semun{
   int val;
   struct semid_ds *buf;
   unsigned short *array;
   struct seminfo *_buf;
};

int P(int semid,int semnum)
{
   struct sembuf sops={semnum,-1,SEM_UNDO};
   return (semop(semid,&sops,1));
}
int V(int semid,int semnum)
{
   struct sembuf sops={semnum,+1,SEM_UNDO};
   return (semop(semid,&sops,1));
}
int main(int argc,char **argv)
{
    int key,rt;
    int semid,ret;
    union semun arg;//semctl第4个参数，表示信号量
    struct sembuf semop;//信号量操作
    int flag;

    if(argc>2 || (argc==2 && strcmp("del",argv[1])!=0))
    {
	printf("usage:%s\n",argv[0]);
	printf("usage:%s del\n",argv[0]);
       return -1;
    }
    key = ftok("/tmp",0x66);
    if(key<0)
    {
      perror("ftok key error");
      return -1;
    }
    
    semid = semget(key,3,IPC_CREAT|0600);//创建3个信号量，或打开
    printf("semid %d\n",semid);
    if(semid == -1)
    {
       perror("create semget error");
       return ;
    }

    if(argc == 1)
    {
       arg.val = 1;
       //对0号信号量设置初值
       ret=semctl(semid,0,SETVAL,1);   
       if(ret < 0)
       {
           perror("ctl sem error");
           rt=semctl(semid,0,IPC_RMID);//删除信号量集
	    if(rt==-1)
		perror("semctl");
	    else
           	printf("semaphore %d deleted!\n",semid);
           return -1;
       }    

	//取0号信号量的值
    	ret=semctl(semid,0,GETVAL,arg);
    	printf("after semctl setval sem[0].val=[%d]\n",ret);  
    	system("date");

    	printf("P operate begin\n");

    	flag = P(semid,0);

    	if(flag)
    	{
        	perror("P operate error");
        	return -1;
    	}
    	printf("P operate end\n");
    	ret = semctl(semid,0,GETVAL,arg);
    	printf("after P sem[0].val=[%d]\n",ret);   
    	system("date");

    	printf("waiting for 5 seconds\n");
    	sleep(5);

    	printf("V operate begin\n");
    	if(V(semid,0)<0)
    	{
        	perror("V operate error");
        	return -1;
    	} 
    	printf("V operate end\n");

    	ret = semctl(semid,0,GETVAL,arg);
    	printf("after V sem[0].val=[%d]\n",ret);
    	system("date");
    	}
    else if(argc==2) 
    {
	if(strcmp("del",argv[1])==0)
    	{
       	rt=semctl(semid,0,IPC_RMID);  //删除信号量集  
		if(rt==-1)
			perror("semctl");
		else
           		printf("semaphore %d deleted!\n",semid);  
     	} 
    	
     }
    return 0;
}
