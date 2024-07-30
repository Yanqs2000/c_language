#include <time.h>
int main()
{
	time_t nowtime;
	char *nowtime2;
	struct tm  *nowtime3;
	time(&nowtime);
	printf("%ld\n",nowtime);
	nowtime2=ctime(&nowtime);
	printf("%s",nowtime2);
	nowtime3=localtime(&nowtime);
	printf("%d-%d-%d:%d:%d:%d\n",nowtime3->tm_year+1900,nowtime3->tm_mon+1,nowtime3->tm_mday,nowtime3->tm_hour,nowtime3->tm_min,nowtime3->tm_sec);
}
