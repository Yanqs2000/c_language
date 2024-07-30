#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/socket.h>


int main() 
{ 
    int sockfd,client_fd;			//sock_fd-监听套接字；client_fd-连接套接字
    struct sockaddr_in my_addr;		//本机地址
    struct sockaddr_in remote_addr;	//客户端地址
int sin_size;
int val=1;
	//创建套接字
if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
{ 
        perror("socket"); 
exit(1); 
    }
//设置地址端口可重用
 
    setsockopt( sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&val, sizeof(val) );
	
//设置本地地址信息
    my_addr.sin_family=AF_INET; 				//协议族
    my_addr.sin_port=htons(3333); 		        //端口
    my_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); 	//地址
    bzero(&(my_addr.sin_zero),8); 				//填充0

	//绑定地址到套接字描述符上
if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) 
{ 
        perror("bind"); 
        exit(1); 
    }
    //在地址端口上监听
if (listen(sockfd, 10) == -1) 
{ 
    	perror("listen"); 
        exit(1); 
    } 
	while(1)
{
sin_size = sizeof(struct sockaddr_in);
//等待客户端连接，如果有客户端连接，则产生新的连接套接字 
if ((client_fd = accept(sockfd, (struct sockaddr *)&remote_addr,&sin_size)) == -1)
{
	perror("accept"); 
	exit(1); 
} 
//输出客户端IP地址
printf("received a connection from %s\n", inet_ntoa(remote_addr.sin_addr)); 
//向客户端发送欢迎信息
if (send(client_fd, "Hello, you are connected!\n", 26, 0) == -1) 
{   
	perror("send"); 
	close(client_fd); 
	exit(2); 
}
printf("Simulation processing start(5s).......\n");
sleep(5);
printf("Simulation processing stop.......\n");
//关闭连接套接字 
close(client_fd); 
}
   	//关闭监听套接字
   	close(sockfd); 
   	return 0;
}
