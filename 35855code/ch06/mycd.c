#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char *argv[])
{
  char *p;
  if(argc==1)
  {
	printf("before:\n");
	system("pwd");
	chdir(getenv("HOME"));
	printf("after:\n");
	system("pwd");
  }
  else 
  {
printf("before:\n");
	system("pwd");
	if(chdir(argv[1])==-1)
		perror("chdir");
	printf("after:\n");
	system("pwd");
  }
}

/*
[root@bogon home]# ./mycd 
before:
/home
after:
/root
[root@bogon home]# ./mycd  /tmp
before:
/home
after:
/tmp

*/
