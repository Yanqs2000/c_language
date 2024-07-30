#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[])
{ 
    int sockfd, recvbytes; 
    char buf[100]; 
    struct hostent *host; 
    struct sockaddr_in serv_addr;

	//创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    { 
        perror("socket"); 
        exit(1); 
    }
    //设置服务器地址结构体
    serv_addr.sin_family=AF_INET; 
    serv_addr.sin_port=htons(3333); 
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(serv_addr.sin_zero),8);
    //向服务器发起连接 
    if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) 
    { 
        perror("connect"); 
        exit(1); 
    }
    //接收服务器端信息并显示
    if ((recvbytes=recv(sockfd, buf, 100, 0)) ==-1) 
    {
        perror("recv"); 
        exit(1); 
    } 
    buf[recvbytes] = '\0'; 	//设置字符串结尾
    printf("Received: %s",buf); 
    //关闭套接字
    close(sockfd); 
    return 0;
}
