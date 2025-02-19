#include <iostream>  // 包含输入输出流库

using namespace std;

int main() 
{
    int* p = NULL;
    int a = 0;
    p = &a;
    cout << &a << endl;
    cout << p << endl;
    cout << *p << endl;
    return 0;

}
