#include <iostream>
#include <string>

using namespace std;

class Myprint
{
public:
    // 重载函数调用运算符()
    void operator()(string test)
    {
        cout << test << endl;
    }
};

class Person
{
public:
    string m_name;
    int m_age;

    Person(string name, int age)
    {
        this->m_age = age;
        this->m_name = name;
    }

    bool operator==(Person &p)
    {
        if(this->m_age == p.m_age)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // 不会利用成员函数重载<<运算符，因为无法实现cout在左侧
    // 只能利用全局函数重载左移运算符
};

// 当运算符重载为成员函数时，调用形式为a.operator<<(b)，其中a是调用对象，b是参数。
// 全局函数重载：当运算符重载为全局函数时，调用形式为operator<<(a, b)，其中a和b是参数

ostream& operator<<(ostream &cout, Person &p)
{
    cout << "name: " << p.m_name << " age: " << p.m_age << endl;
    return cout;
}

void test01()
{
    Myprint my;
    my("hello world!");//由于使用起来非常像函数调用，因此称为仿函数。
}

void test02()
{
    Person p1("Tom", 18);
    Person p2("Ryan", 18);

    if(p1 == p2)
    {
        cout << "The age is same." << endl;
    }
    else
    {
        cout << "The age is different." << endl;
    }
}

void test03()
{
    Person p1("Tom", 18);
    Person p2("Ryan", 18);
    cout << p1 << p2 << endl;
}

int main()
{
    test03();
}
