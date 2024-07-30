#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
char buf[] = "a write to stdout\n";
void func1();
void func2();
int main(int argc,char* argv[])
{
    int var = 0;
    pid_t pid;
    if(write(STDOUT_FILENO, buf, strlen(buf)) < 0){
        perror("write error");
    }
    atexit(func1);
    atexit(func2);
    exit(0);
}
void func1()
{
    printf("func1()\n");
}
void func2()
{
    printf("func2()\n");
}
