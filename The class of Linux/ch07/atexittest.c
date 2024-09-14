#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
void func(); 
int main(int argc,char* argv[]) 
{
    char buf[8]; 
    strcpy(buf,"hello world\n");
    atexit(func);
    return(0);
}
void func()
{
    printf("func()\n");
}
