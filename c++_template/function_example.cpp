#include <iostream>
using namespace std;

int x = 10;
int y = 100; 

void swapint(int &a, int &b) 
{
    int temp = a;
    a = b;
    b = temp;
}

void swapdouble(double &a, double &b)
{
    double temp = a;
    a = b;
    b = temp;
}

//函数模板
template <typename T> //声明一个模板，告诉编译器，T是一个通用数据类型

void myswap(T &a, T &b) //T代表任意类型
{
    T temp = a;
    a = b;
    b = temp;
}

//1.自动类型推导，必须推导出一致的数据类型T才可以使用
void test01()
{
    int a = 1, b = 2;
    double c = 1.1, d = 2.2;
    myswap(a, b);
    cout << "a = " << a << " b = " << b << endl;
    myswap(c, d);
    cout << "c = " << c << " d = " << d << endl;
}

//2.模板必须要确定出T的类型才可以使用(必须使用指定类型，否则报错)
template <class T>
void test02()
{
    cout << "test02" << endl;
}

void test03(int *a, int *b)
{
    cout << *a + *b << endl;
}

int main()
{
    //test01();
    //test02<int>();
    test03(&x, &y);
    return 0;
}