#include "stuscore.h"

#define   N   3
struct  student    data[N];

void  input(struct student  *d,int n);
void  calculate(struct student  *d,int n);
void  output(struct student  *d,int n);

int main()
{
	input(data,N);
	calculate(data,N);
	output(data,N);
}
