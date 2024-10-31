#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h> 


int main(int argc, char *argv[]) 
{ 
	int fd, numbytes;   
	char buf[100]; 
	char sendbuf[20]="hello";
	struct hostent *he;         
	struct sockaddr_in server,reply; 

	if (argc !=2) 
{  
		printf("Usage: %s <IP Address> \n",argv[0]); 
		exit(1); 
	} 
	if ((he=gethostbyname(argv[1]))==NULL)
	{ 
		printf("gethostbyname() error\n"); 
		exit(1); 
	} 
	if ((fd=socket(AF_INET, SOCK_DGRAM, 0))==-1)
	{ 
		printf("socket"); 
		exit(1); 
	} 
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET; 
	server.sin_port = htons(3333);  
	server.sin_addr = *((struct in_addr *)he->h_addr);   
sendto(fd, sendbuf, strlen(sendbuf),0,(struct sockaddr *)&server,
sizeof(struct sockaddr)); 
	while (1) 
	{

		int len;
		len= sizeof(struct sockaddr_in);
if ((numbytes=recvfrom(fd,buf,100,0,
(struct sockaddr *)&reply,&len)) == -1)
		{ 
			perror("recvfrom"); 
			exit(1); 
		} 

		//check if server is right
if (len != sizeof(struct sockaddr) || memcmp((const void *)&server, 
(const void *)&reply,len) != 0) 
		{
			printf("Receive message from other server.\n");
			continue;
		}
		//printf message from server
		buf[numbytes]='\0';
		printf("Server Message: %s\n",buf); 
		printf("input:");
		fgets(sendbuf,sizeof(sendbuf),stdin);
		sendbuf[strlen(sendbuf)-1]='\0';
sendto(fd, sendbuf, strlen(sendbuf),0,(struct sockaddr *)&server,
sizeof(struct sockaddr)); 
	     if(strcmp(sendbuf,"quit")==0)	
		break;
	}
	close(fd); 
	return 0;
}
