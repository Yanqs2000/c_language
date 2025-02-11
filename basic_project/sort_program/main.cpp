// 将person自定义数据类型进行排序，person中属性有姓名、年龄、身高
// 排序规则：按照年龄进行升序，相同则按照身高进行降序

#include<iostream>
#include <list>
#include <string>

using namespace std;

class Person
{
public:
    Person(string name, int age, int height)
    {
        this->m_name = name;
        this->m_age = age;
        this->m_height = height;
    }
    
    string m_name;
    int m_age;
    int m_height;


};

void printList(const list<Person> &l)
{
    for (list<Person>::const_iterator it = l.begin(); it != l.end(); it++)
    {
        cout << (*it).m_name << " ";
        cout << (*it).m_age << " ";
        cout << (*it).m_height << " ";
        cout << endl;
    }
    cout << endl;
}

bool MyComparePerson(Person &p1, Person &p2)
{
    if(p1.m_age == p2.m_age)
    {
        return p1.m_height > p2.m_height;
    }
    else
    {
        return p1.m_age < p2.m_age;
    }
}

void MySort()
{
    // 准备数据
    list<Person> List_Person;
    Person p1("刘备", 35, 175);
    Person p2("曹操", 45, 180);
    Person p3("孙权", 40, 170);
    Person p4("赵云", 25, 190);
    Person p5("张飞", 35, 160);
    Person p6("关羽", 35, 200);

    List_Person.push_back(p1);
    List_Person.push_back(p2);
    List_Person.push_back(p3);
    List_Person.push_back(p4);
    List_Person.push_back(p5);
    List_Person.push_back(p6);

    cout << "----------排序前----------" << endl;
    printList(List_Person);

    // 排序
    List_Person.sort(MyComparePerson);

    cout << "----------排序后----------" << endl;
    printList(List_Person);

}


int main()
{
    MySort();
}

