#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#define PORT 8080
#define IP "192.168.1.207" // 服务器端IP地址
#define MAXLINE 100

// gcc -o netudpserver.exe netudpserver.c -lws2_32

int main() 
{
    int sockfd;         
    struct sockaddr_in server; 
    struct sockaddr_in client; 
    int sin_size; 
    int num;
    char msg[MAXLINE];  
    char sbuf[MAXLINE] = "Welcome to my server.";

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
#endif

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) // 创建套接字
    {
#ifdef _WIN32
        printf("socket creation error: %d\n", WSAGetLastError());
#else
        perror("socket");
#endif
        exit(1);
    }

    // 服务器端地址
    memset(&server, 0, sizeof(server)); // 用 memset 代替 bzero
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
    {
#ifdef _WIN32
        printf("bind error: %d\n", WSAGetLastError());
#else
        perror("bind");
#endif
        exit(1);
    }

    sin_size = sizeof(struct sockaddr_in);

    while (1)
    {
        num = recvfrom(sockfd, msg, sizeof(msg) - 1, 0, (struct sockaddr *)&client, &sin_size);
        if (num < 0)
        {
#ifdef _WIN32
            printf("recvfrom error: %d\n", WSAGetLastError());
#else
            perror("recvfrom");
#endif
            exit(1);
        }
        msg[num] = '\0';
        printf("You got a message (%s) from %s\n", msg, inet_ntoa(client.sin_addr));

        strcpy(sbuf, msg);
        sendto(sockfd, sbuf, strlen(sbuf), 0, (struct sockaddr *)&client, sin_size);

        if (!strcmp(msg, "quit"))
            break;
    }

#ifdef _WIN32
    closesocket(sockfd);
    WSACleanup(); // 清理Winsock资源
#else
    close(sockfd);
#endif

    return 0;
}

