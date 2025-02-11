// set容器，集合，关联式容器，用二叉树实现
// 所有元素都会在插入时自动排序,
// set容器，不允许重复元素；
// mulitset容器，允许有重复元素

#include <set>
#include <iostream>

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

class MyCompare
{
public:
    bool operator()(int v1, int v2) const
    {
        return v1 > v2;
    }
};

class MyComparePerson
{
public:
    bool operator()(const Person &p1, const Person &p2) const
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
};

void printSet(set<int> &s)
{
    for(set<int>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void printMulitset(multiset<int> &s)
{
    for(multiset<int>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void printSet_MyCompare(set<int, MyCompare> &s)
{
    for(set<int, MyCompare>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

void printSet_MyCompare_Person(set<Person, MyComparePerson> &s)
{
    for(set<Person, MyComparePerson>::iterator it = s.begin(); it != s.end(); it++)
    {
        cout << (*it).m_name << " " << (*it).m_age << " " << (*it).m_height << endl;
    }
}

// set容器构造和赋值
void test01()
{
    set<int> s1;
    
    // 只有insert的方法，无push_back等
    s1.insert(10);
    s1.insert(70);
    s1.insert(40);
    s1.insert(20);

    printSet(s1);
    
    // 拷贝构造
    set<int> s2(s1);
    printSet(s2);

    // 赋值
    set<int> s3;
    s3 = s1;
    printSet(s3);
}

// 大小和交换
void test02()
{
    set<int> s1, s2;
    
    s2.insert(6);
    s2.insert(5);
    s2.insert(4);
    s2.insert(1);

    if(s1.empty())
    {
        cout << "set is empty."<< endl;
        s1.insert(10);
        s1.insert(70);
        s1.insert(40);
        s1.insert(20);
        cout << "set size is: " << s1.size() << endl;
    }
    else
    {
        cout << "set size is: " << s1.size() << endl;
    }

    printSet(s1);
    printSet(s2);

    s1.swap(s2);

    printSet(s1);
    printSet(s2);
}

// 插入和删除
void test03()
{
    set<int> s1;
    s1.insert(6);
    s1.insert(5);
    s1.insert(4);
    s1.insert(1);

    set<int> s2(s1);

    set<int>::iterator it = s1.begin();
    s1.erase(it); // 用迭代器指定
    printSet(s1); // 用迭代器指定区间

    s1.erase(s1.begin(), --s1.end());
    printSet(s1);

    s2.erase(6); // 删除指定的元素
    printSet(s2);

    s2.clear();


}

// 查找和统计
void test04()
{
    set<int> s1;
    s1.insert(6);
    s1.insert(5);
    s1.insert(4);
    s1.insert(1);

    set<int>::iterator pos = s1.find(1);
    int count = s1.count(1);

    if(pos != s1.end())
    {
        cout << "found" << endl;
        cout << "count is " << count << endl;
    }
    else
    {
        cout << "not found" << endl;
    }
}

// mulitset容器
void test05()
{
    // 普通的set容器在insert时的返回是一个对组pair，bool负责判断是否成功
    set<int> s1;
    pair<set<int>::iterator, bool> ret = s1.insert(10);

    if(ret.second)
    {
        cout << "first insert is successful." << endl;
    }
    else
    {
        cout << "first insert is failed." << endl;
    }

    pair<set<int>::iterator, bool> ret2 = s1.insert(10);

    if(ret2.second)
    {
        cout << "second insert is successful." << endl;
    }
    else
    {
        cout << "second insert is failed." << endl;
    }
    printSet(s1);
    
    // mulitset容器只返回迭代器，因为无需返回唯一性的检查结果 
    multiset<int> m_s1;
    multiset<int>::iterator it = m_s1.insert(10);
    m_s1.insert(10);
    printMulitset(m_s1);
}

// 对组pair,成对出现的数据
void test06()
{
    // 构造的两种方式
    pair<int, string> p(1, "颜");
    pair<string, int> p1 = make_pair("祺", 2);

    cout << sizeof(p.first) << " "<< p.first << endl;
    cout << sizeof(p.second) << " "<< p.second << endl;
    cout << sizeof(p1.first) << " "<< p1.first << endl;
    cout << sizeof(p1.second) << " "<< p1.second << endl;
}

// 改变set容器的排序规则,利用仿函数来实现(内置数据类型)
void test07()
{
    set<int> s1;

    s1.insert(1);
    s1.insert(2);
    s1.insert(4);
    s1.insert(5);
    s1.insert(3);

    printSet(s1);

    // 指定排序规则
    set<int, MyCompare> s2;
 
    s2.insert(10);
    s2.insert(20);
    s2.insert(40);
    s2.insert(50);
    s2.insert(30);

    printSet_MyCompare(s2);

}

// 改变set容器的排序规则,利用仿函数来实现(自定义数据类型),需要指定排序规则
void test08()
{
    // 准备数据
    set<Person, MyComparePerson> List_Person;
    Person p1("刘备", 35, 175);
    Person p2("曹操", 45, 180);
    Person p3("孙权", 40, 170);
    Person p4("赵云", 25, 190);
    Person p5("张飞", 35, 160);
    Person p6("关羽", 35, 200);

    List_Person.insert(p1);
    List_Person.insert(p2);
    List_Person.insert(p3);
    List_Person.insert(p4);
    List_Person.insert(p5);
    List_Person.insert(p6);
    printSet_MyCompare_Person(List_Person);
}

int main()
{
    test08();
}