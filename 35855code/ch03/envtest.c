#include <stdio.h>
#include <stdlib.h>
main()
{
	char *val;
	val=getenv("USER");
	printf("USER1=%s\n",val);
	setenv("USER","hehe",1);
	val=getenv("USER");
	printf("USER2=%s\n",val);

	putenv("AGE=20");
	val=getenv("AGE");
	printf("AGE1=%s\n",val);

	unsetenv("AGE");
	val=getenv("AGE");
	printf("AGE2=%s\n",val);
    
       return 0;
}
