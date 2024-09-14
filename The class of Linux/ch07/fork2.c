#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

main()
{
        pid_t id;
        int  i;

        id=fork();

        if(id<0)
        {
       	perror("fork");
        	exit(1);
        }
       else if(id==0)
        {
       	for(i=0;i<10;i++)
                 {
                 	printf("I am child, my pid=  %d\n",getpid());
                  	sleep(1);
                 }
        }
       else
       {    
		for(i=0;i<10;i++)
                {
              	printf("I am parent, my pid=  %d\n",getpid());
              	sleep(1);
                 }
        }
      printf("%d print this sentence\n",getpid());
}

/*
[root@bogon 7]# gcc fork2.c -o fork2
[root@bogon 7]# ./fork2
I am child, my pid=  8849
I am parent, my pid=  8848
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
I am parent, my pid=  8848
I am child, my pid=  8849
8848 print this sentence
[root@bogon 7]# 8849 print this sentence

[root@bogon 7]# ps -la
F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S     0  8848 26255  0  75   0 -   384 -      pts/1    00:00:00 fork2
1 S     0  8849  8924  0  78   0 -   384 -      pts/1    00:00:00 fork2
4 R     0  8926  8904  0  77   0 -  1119 -      pts/2    00:00:00 ps


*/
