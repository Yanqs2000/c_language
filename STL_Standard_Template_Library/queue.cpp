// queue 是一种先进先出的数据结构，队尾back()只能进数据push()，队头front()只能出数据pop()，只有队尾和队头才能被访问到
// 不允许被遍历
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class Person
{
public:
    // 构造函数
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }
    string m_name;
    int m_age;
};


void test01()
{
    queue<Person> q;

    Person p1("yanqs",24);
    Person p2("yan",23);
    Person p3("qs",22);

    q.push(p1);
    q.push(p2);
    q.push(p3);

    while (!q.empty())
    {
        cout << "name: " << q.front().m_name << " age: " << q.front().m_age << endl;
        cout << "name: " << q.back().m_name << " age: " << q.back().m_age << endl;
        q.pop();
        // 只剩最后一个时，front和back是同一个元素
    } 
}

int main()
{
    test01();
    return 0;
}