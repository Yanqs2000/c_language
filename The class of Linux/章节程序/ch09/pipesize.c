//输出PIPE_BUF的大小，Linux内核2.9.130以前一个缓冲区，之后为16个缓冲区。
#include<stdio.h>
#include <linux/limits.h>
int main() 
{
    printf("PIPE_BUF %d(bytes)\n",PIPE_BUF);
    return 0;
}
