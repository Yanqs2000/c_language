#include <iostream>

int main()
{
    int a = 0x1234;
    std::cout << std::hex << a << std::endl; // 输出 1234
    std::cout << std::dec << a << std::endl; // 输出 4660

    char *p = (char*)&a;

    if(*p == 0x34)
    {
        std::cout << "Little Endian" << std::endl;
    }
    else
    {
        std::cout << "Big Endian" << std::endl;
    }


    return 0;
}