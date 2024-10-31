#include <stdio.h>          
#include <strings.h>         
#include <unistd.h>         
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>

#define PORT 1234   
#define BACKLOG 5   
#define MAXDATASIZE 1000  
void process_cli(int connfd, struct sockaddr_in client);

main() 
{ 
	int listenfd, connfd; 
	pid_t pid;
	struct sockaddr_in server; 
	struct sockaddr_in client; 
	int len; 	
	int opt = SO_REUSEADDR;
	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
	   	perror("socket");
	   	exit(1);
	}
	
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&server,sizeof(server));
	server.sin_family=AF_INET; 
	server.sin_port=htons(PORT); 
	server.sin_addr.s_addr = htonl(INADDR_ANY); 

	if (bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) 
	{ 
	   	perror("bind");
	   	exit(1); 
	}    

	if(listen(listenfd,BACKLOG) == -1)
	{  
	   perror("listen"); 
	   exit(1); 
	}

	len=sizeof(client); 
	while(1)
	{
		 if ((connfd = accept(listenfd,(struct sockaddr *)&client,&len))==-1) 
		 {
		   	perror("accept"); 
		   	exit(1); 
		 } 
		if ((pid=fork())>0) 
		{
		   	close(connfd);
		   	continue;
		}
		else if (pid==0) 
		{
		   	close(listenfd);
		   	process_cli(connfd, client);
		   	exit(0);     
		}
		else 
		{
		   	perror("fork");
		   	exit(0);
		}
	}
	close(listenfd);   
} 

void exchange(char *src,int num)
{
	char c;
	int i;
	src[num-1]=0;
	num=num-1;
	printf("%d\n",num);
	for(i=0;i<num;i++)
	{
		
		c=src[i];
		src[i]=src[num-1];
		src[num-1]=c;
		num=num-1;
		if(num<=i)
			break;
	}
}

void process_cli(int connfd, struct sockaddr_in client)
{
	int num;
	char exitflag=0;
	char recvbuf[MAXDATASIZE], sendbuf[MAXDATASIZE], cli_name[MAXDATASIZE];
	printf("got a connection from %s.\n",inet_ntoa(client.sin_addr) );
	num = recv(connfd, cli_name, MAXDATASIZE,0);
	if (num == -1) 
	{
	   	close(connfd);
	   	perror("recv");
	   	return;
	}
	cli_name[num - 1] = '\0';
	printf("%s client's name is %s.\n",inet_ntoa(client.sin_addr),cli_name);	
	while (num = recv(connfd, recvbuf, MAXDATASIZE,0)) 
	{
	   recvbuf[num] = '\0';
	   printf("%s:%s",cli_name, recvbuf);
	   if(strcmp(recvbuf,"bye")==0)
		exitflag=1;
	   exchange(recvbuf,num);
	   send(connfd,recvbuf,num,0); 
	   if(exitflag==1)
		break;
	}
	close(connfd);
	printf("client %s from %s  end.\n",cli_name,inet_ntoa(client.sin_addr));
}
