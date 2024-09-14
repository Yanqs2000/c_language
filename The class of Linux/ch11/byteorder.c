#include <stdio.h>
int main()
{
	int i=0x41424344;
	char* pAddress=(char*)&i;
	int j;
	printf("int Address:%x Value:%x\n",&i,i);
	printf("-------------------------------\n");
	for(j=0;j<=3;j++)
	{
		printf("char Address:%x Value:%c\n",pAddress,*pAddress);
		pAddress++;
	}
}
