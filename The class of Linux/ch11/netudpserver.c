#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/socket.h>


int main() 
{ 
int sockfd;         //Ì×½Ó×ÖÃèÊö·û
	struct sockaddr_in server; 
	struct sockaddr_in client; 
	int sin_size; 
	int num;
	char msg[100];  
	char sbuf[100]="Welcome to my server.";

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  
	{
		perror("socket");
		exit(1);
	}

	bzero(&server,sizeof(server));
	server.sin_family=AF_INET; 
	server.sin_port=htons(3333); 
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	if (bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) 
	{ 
		perror("bind");
		exit(1); 
	}    

	sin_size=sizeof(struct sockaddr_in); 
	while (1)   
	{
num=recvfrom(sockfd,msg,100,0,
(struct sockaddr *)&client, &sin_size); 
		if (num < 0)
{
			perror("recvfrom"); 
			exit(1); 
		} 
		msg[num] = '\0';
		printf("You got a message (%s) from %s\n",msg,inet_ntoa(client.sin_addr) ); 
		strcpy(sbuf,msg);
		sendto(sockfd,sbuf,strlen(sbuf),0,(struct sockaddr *)&client,sin_size); 
		if (!strcmp(msg,"quit")) break;
	} 
	close(sockfd);   // close listenfd
	return 0;
}
