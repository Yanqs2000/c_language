//���PIPE_BUF�Ĵ�С��Linux�ں�2.9.130��ǰһ����������֮��Ϊ16����������
#include<stdio.h>
#include <linux/limits.h>
int main() 
{
    printf("PIPE_BUF %d(bytes)\n",PIPE_BUF);
    return 0;
}
