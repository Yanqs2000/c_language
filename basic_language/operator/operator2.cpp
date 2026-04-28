#include <iostream>
#include <memory>
using namespace std;

class Test
{
public:
    int a;
    int b;

    Test(int a, int b) : a(a), b(b) {}

    bool operator==(const Test &other)
    {
        return this->a == other.a && this->b == other.b;
    }

    bool operator>(const Test &other)
    {
        return this->a > other.a && this->b > other.b;
    }
};


class Person
{
public:
    int age;
    // 默认构造函数
    Person(int age): age(age) {}

    // 拷贝构造函数
    Person(const Person &p)
    {
        this->age = p.age;
    }

    ~Person(){}
    void setAge(int age)
    {
        this->age = age;
    }

    void print()
    {
        cout << "age: " << age << endl;
    }

};

void test()
{
    // unique_ptr<int> p1(new int(10));
    unique_ptr<int> p1 = make_unique<int>(10); // 推荐使用make_unique创建unique_ptr对象 
    cout << *p1 << endl;

    vector<int> v(100, 1);
    vector<int> &&v2 = std::move(v);

    Person p3(20);

    Person &s1 = p3; // 引用s1绑定到p3
    Person p4 = p3; // 调用拷贝构造函数
}

int main()
{
    Test t1(1, 2);
    Test t2(2, 3);
    cout << (t1 == t2) << endl; // 输出0，表示t1和t2不相等
    cout << (t1 > t2) << endl;  // 输出0，表示

    return 0;
}