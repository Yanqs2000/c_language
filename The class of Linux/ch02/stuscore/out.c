#include <stdio.h>
#include "stuscore.h"
void  output(struct student  *d,int n)
{
	int i;
	printf("name	age	ch	math	sum	ave\n");
	for(i=0;i<n;i++)
	{
		printf("%s	%d	%.2f	%.2f	%.2f	%.2f\n",d[i].name,d[i].age,d[i].ch,d[i].math,d[i].sum,d[i].ave);
	}
}

