#include <stdio.h> 
#include <unistd.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>       
#include <time.h>       
#include <fcntl.h>       

#define PORT 1234   
#define MAXDATASIZE 100   

void process(FILE *fp, int sockfd);
char* getMessage(char* sendline,int len, FILE* fp);

int main(int argc, char *argv[]) 
{ 
	int sockfd;   
	struct hostent *he;         
	struct sockaddr_in server; 	
	if (argc !=2) 
	{       
	   	printf("Usage: %s <IP Address>\n",argv[0]); 
	   	exit(1); 
	} 	
	if ((he=gethostbyname(argv[1]))==NULL)
	{ 
	  	printf("gethostbyname() error\n"); 
	  	exit(1); 
	} 	
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1)
	{  
	   	perror("socket"); 
	   	exit(1); 
	} 	
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET; 
	server.sin_port = htons(PORT); 
	server.sin_addr = *((struct in_addr *)he->h_addr);  	
	if(connect(sockfd, (struct sockaddr *)&server,sizeof(server))==-1)
	{ 
	   perror("connect"); 
	   exit(1); 
	} 	
	process(stdin,sockfd);	
	close(sockfd);     
}


void writefile(int fd,char *str) 
{
	time_t t1;
	struct tm *t2;
	char wtext[100];
	t1=time(NULL);
	t2=localtime(&t1);
	sprintf(wtext,"%d-%d-%d-%d:%d:%d",t2->tm_year+1900,t2->tm_mon+1,t2->tm_mday,t2->tm_hour,t2->tm_min,t2->tm_sec);
	sprintf(wtext,"%s	%s\n",wtext,str);
	write(fd,wtext,strlen(wtext));
}
	
void process(FILE *fp, int sockfd)
{
	char	sendline[MAXDATASIZE], recvline[MAXDATASIZE];
	int num;
	int fd;
	time_t  t1;
	struct tm *t2;
	char cname[30];
	char tmp[100];
	printf("Connected to server. \n");
	printf("Input client's name : ");
	if ( fgets(cname, 30, fp) == NULL) 
	{
	  	printf("\nExit.\n");
	  	return;
	}
	send(sockfd, cname, strlen(cname),0);	
	cname[strlen(cname)-1]=0;
	fd=open(cname,O_WRONLY|O_CREAT|O_APPEND,0644);
	if(fd==-1)
	{
		perror("open");
	}
	writefile(fd,"connection success");
	while (getMessage(sendline, MAXDATASIZE, fp) != NULL) 
	{
	   	send(sockfd, sendline, strlen(sendline),0);	   	
		sendline[strlen(sendline)-1]=0;
		sprintf(tmp,"%s	:	%s",cname,sendline);
		writefile(fd,tmp);
	   	if ((num = recv(sockfd, recvline, MAXDATASIZE,0)) == 0) 
	   	{
	   	   	printf("Server terminated.\n");
	   	   	return;
	   	}	   	
	   	recvline[num]='\0'; 
	   	printf("Server Message: %s\n",recvline); 
		sprintf(tmp,"server	:	%s",recvline);
		writefile(fd,tmp);
		if(strcmp(sendline,"bye")==0)
			break;
	}
	printf("\nExit.\n");
	writefile(fd,"close connection");
} 

char* getMessage(char* sendline,int len, FILE* fp) 
{
	printf("Input string to server:");
	return(fgets(sendline, MAXDATASIZE, fp));
}


