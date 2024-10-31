#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define  MAXLINE   4096
int parse(char *, char * * );
int main(void)
{
   pid_t  pid;
   char *rt;
   char   buf[MAXLINE];
   int    status;
   char  *args[64];
   int    argnum = 0;

   while (1) 
   {
   	printf("%% ");  //print prompt
   	rt=fgets(buf, MAXLINE, stdin);
	if(rt==NULL)
	{
		printf("fgets error\n");
		exit(1);
	}
	if(!strcmp(buf,"\n"))  //deal with enter only
        {	
	  	printf("%% ");  //print prompt
	  	continue;       //end loop this time
      	}
      	if (buf[strlen(buf) - 1] == '\n')
          	buf[strlen(buf) - 1] = 0;        //replace newline with null

      	argnum=parse(buf, args);  //analyze user input to get argnum and args

      	if((strcmp(args[0],"logout")==0)||(strcmp(args[0],"exit")==0))//exit shell
	  exit(0);
      	else  //execute other command
         {
             if ((pid = fork()) < 0) //fork 
              {
                  printf("fork error,please reput command\n"); 
     	          continue;       //end loop this time
              } 
              else if (pid == 0) 
                   {//child
                       execvp(*args, args);
		       printf("couldn't execute: %s\n", buf);
 	               exit(127);
		   }
             //parent
             if ((pid = waitpid(pid, &status, 0)) < 0)
                  printf("waitpid error\n");
          }
   }
   exit(0);
}

int parse (char *buf, char **args)
{
     int num=0;
     while (*buf != '\0')
     {
            while((* buf ==' ')||(* buf == '\t'||(*buf == '\n')))
                *buf++ = '\0'; //��ѭ���Ƕ�λ��������ÿ���ַ����ĵ�һ���ǿյ��ַ�
            *args++ = buf;   //���ҵ��ķǿ��ַ��� ���θ�ֵ��args��i�ݡ�
  	    ++num;
            
            while ((*buf!='\0')&&(* buf!=' ')&&(* buf!= '\t') && (*buf!= '\n'))//��������ĸ�������ƶ���ֱ����λ���ǿ��ַ�����ĵ�һ���ո�
                buf ++;
     }
    *args = '\0';
    return num;
}


