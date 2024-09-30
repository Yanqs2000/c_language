#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>
#endif

#define PORT 8080
#define MAXLINE 100

// gcc -o netudpclient.exe netudpclient.c -lws2_32

int main(int argc, char *argv[]) 
{ 
    int fd, numbytes;   
    char buf[MAXLINE]; 
    char sendbuf[MAXLINE] = "hello";
    struct hostent *he; // 储存IP地址         
    struct sockaddr_in server, reply; // 服务器端和客户端的地址结构

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }
#endif

    if (argc != 2) 
    {  
        printf("Usage: %s <IP Address> \n", argv[0]);
        // 作为客户端使用时，argv[1]表示的是对方服务器端的IP地址
        exit(1); 
    }

    if ((he = gethostbyname(argv[1])) == NULL)
    { 
        printf("gethostbyname() error\n"); 
        exit(1); 
    }

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) // 创建套接字, AF_INET 表示使用IPv4协议，SOCK_DGRAM 表示使用UDP协议
    { 
        printf("socket error\n"); 
        exit(1); 
    }

    // 初始化服务器端地址结构
    memset(&server, 0, sizeof(server)); // 用 memset 代替 bzero
    server.sin_family = AF_INET; 
    server.sin_port = htons(PORT);  
    server.sin_addr = *((struct in_addr *)he->h_addr);

    // 发送消息到服务器端
    sendto(fd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));

    while (1) 
    {
        int len = sizeof(struct sockaddr_in);

        if ((numbytes = recvfrom(fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&reply, &len)) == -1)
        { 
#ifdef _WIN32
            printf("recvfrom error: %d\n", WSAGetLastError());
#else
            perror("recvfrom");
#endif
            exit(1); 
        }

        // 检查消息是否来自正确的服务器
        if (len != sizeof(struct sockaddr) || memcmp((const void *)&server, (const void *)&reply, len) != 0) 
        {
            printf("Receive message from other server.\n");
            continue;
        }

        // 打印服务器消息
        buf[numbytes] = '\0';
        printf("Server Message: %s\n", buf); 
        printf("next sending input:");
        fgets(sendbuf, sizeof(sendbuf), stdin);
        sendbuf[strlen(sendbuf) - 1] = '\0'; // 去除换行符
        sendto(fd, sendbuf, strlen(sendbuf), 0, (struct sockaddr *)&server, sizeof(struct sockaddr));

        // 客户端退出标志
        if (strcmp(sendbuf, "quit") == 0)    
            break;
    }

#ifdef _WIN32
    closesocket(fd);
    WSACleanup(); // 清理 Winsock
#else
    close(fd);
#endif

    return 0;
}

