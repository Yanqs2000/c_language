#include <stdio.h>
#include "stuscore.h"
void  input(struct student  *d,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("please input %d  student-name:",i+1);
		scanf("%s",&(d[i].name));
		printf("please input %d  student-age:",i+1);
		scanf("%d",&(d[i].age));
		printf("please input %d  student-ch:",i+1);
		scanf("%f",&(d[i].ch));
		printf("please input %d  student-math:",i+1);
		scanf("%f",&(d[i].math));
	}
}

