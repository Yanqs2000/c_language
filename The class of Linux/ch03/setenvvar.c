#include <time.h>
int main(int argc,char *argv[])
{
	time_t  t1;
	char *t2;
	if(argc<2)
	{
		printf("usage:%s varname [value]\n",argv[0]);
		exit(0);
	}
	printf("before %s = %s\n",argv[1],getenv(argv[1]));
	if(argc==2)
	{
		t1=time(NULL);
		t2=ctime(&t1);
		setenv(argv[1],t2,1);
		printf("after %s = %s\n",argv[1],getenv(argv[1]));
	}
	else
	{
		setenv(argv[1],argv[2],1);
		printf("after %s = %s\n",argv[1],getenv(argv[1]));
	}	
}
