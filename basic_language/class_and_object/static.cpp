#include<iostream>
using namespace std;

class student
{
public:
    //静态成员变量、类内声明、类外初始化操作
    //所有对象都共享一份数据
    static int count;
    int age;


    student()
    {
        
    }

    student(int age_1)
    {
        age = age_1;
    }


    //静态成员函数，所有对象共享一个函数，静态成员函数只能访问静态成员变量
    static void func01()
    {
        count = 1000;
        cout<< count <<"static void func01调用"<<endl;
    }
    void func02()
    {
        cout<< age <<endl;
        cout<<"void func02调用"<<endl;
    }
};

int student::count = 100;

void test01()
{
    student s1;
    cout<<"s1 count: "<<s1.count<<endl;
    student s2;
    s2.count = 200;
    cout<<"s1 count: "<<s1.count<<endl;
}

void test02()
{
    //静态变量通过对象进行访问
    student p2;
    cout <<p2.count<<endl;
    
    //静态变量通过类名进行访问
    cout << student::count << endl;
}

void test03()
{
    //静态成员函数通过对象进行访问
    student p3(10);
    p3.func02();

    //静态成员函数通过类名进行访问
    student::func01();
}


int main()
{
    
    //test01();
    test03();
    return 0;
}