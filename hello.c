#include <stdio.h>
#include <string.h>  // 为了使用 strlen 函数

int main() 
{
    char str[] = "hello";
    
    // 打印数组的大小（包括终止符 '\0'）
    printf("Size of array: %zu\n", sizeof(str));
    
    // 打印字符串的长度（不包括终止符 '\0'）
    printf("Length of string: %zu\n", strlen(str));
    
    return 0;
}