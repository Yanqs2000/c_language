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

	//�����׽���
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    { 
        perror("socket"); 
        exit(1); 
    }
    //���÷�������ַ�ṹ��
    serv_addr.sin_family=AF_INET; 
    serv_addr.sin_port=htons(3333); 
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    bzero(&(serv_addr.sin_zero),8);
    //��������������� 
    if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) 
    { 
        perror("connect"); 
        exit(1); 
    }
    //���շ���������Ϣ����ʾ
    if ((recvbytes=recv(sockfd, buf, 100, 0)) ==-1) 
    {
        perror("recv"); 
        exit(1); 
    } 
    buf[recvbytes] = '\0'; 	//�����ַ�����β
    printf("Received: %s",buf); 
    //�ر��׽���
    close(sockfd); 
    return 0;
}
