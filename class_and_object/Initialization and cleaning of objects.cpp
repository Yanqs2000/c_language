#include<iostream>
using namespace std;

class Person
{
public:   
    //1.构造函数 进行初始化操作 只调用一次 不写就是空实现 有点类似于python的self.__init__
    //1.构造函数可以重载,可以有参数，函数名与类名相同

    Person()//无参构造
    {
        cout << "Person的无参构造函数调用" << endl;
    }

    Person(int input) //有参构造
    {
        age = input;
        cout << "Person的有参构造函数调用" << endl;
    }

    Person(const Person &p) //拷贝构造
    {
        age = p.age;
        cout << "Person的拷贝构造函数调用 age:" << age << endl;
    }


    int age;

    //2.析构函数 对象在销魂前 进行清理操作 只调用一次 不可以有参数，不可以重载
    ~Person()
    {
        cout << "Person的析构函数调用" << endl;
    }
};

//调用
void test01() //创建对象时，会自动调用构造函数；对象销毁时，会自动调用析构函数
{
    //1.括号法
    Person p1; 
    Person p2(10);
    Person p3(p2);

    //2.显示法
    Person p4 = Person(10);
    Person p5 = Person(p4);

    //3.隐式法
    Person p6 = 10;
    Person p7 = p6;
}

int main()
{
    test01();

    return 0;
}