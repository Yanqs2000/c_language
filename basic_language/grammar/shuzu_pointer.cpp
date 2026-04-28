#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int (*p)[10] = &a; // 定义一个指向数组的指针，指向数组a
    cout << *((*p) + 1) << endl; // 输出数组a的地址
    
    
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> *pv = &v; // 定义一个指向vector的指针，指向vector v
    cout << (*pv)[4] << endl; // 输出vector v的第三个元素

    // 顶层const == 常量指针，指针本身是常量，不能修改指针的值（地址），但可以修改指针指向的内容
    int b = 100;
    int* const p1 = &b;
    cout << *p1 << endl; // 输出100
    b = 200; // 可以修改指针指向的内容
    cout << *p1 << endl; // 输出200

    // 底层const == 指针常量，指针指向的内容是常量，不能修改指针指向的内容，但可以修改指针的值（地址）
    int c = 300;
    int const *p2 = &b;
    cout << *p2 << endl; // 输出200
    p2 = &c; // 可以修改指针的值（地址）
    cout << *p2 << endl; // 输出300
    
    return 0;
}