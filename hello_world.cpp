#include <iostream>  // 包含输入输出流库
#include <stdio.h>

using namespace std;

int main() 
{
    unsigned int x = 0x12345678;
    char *c = (char*)&x;

    if (*c == 0x12) 
	{
        printf("Big Endian\n");
    } 
	else if (*c == 0x78) 
	{
        printf("Little Endian\n");
    } 
	else 
	{
        printf("Unknown Endian\n");
    }
    printf("x = %x\n", x);
    return 0;

}
