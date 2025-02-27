#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;
class Person
{
public:
    Person(string name, int age)
    {
        this->m_name = name;
        this->m_age = age;
    }
    // 重载 == 让底层知道find如何对比Person数据类型
    bool operator==(const Person &p)
    {
        if(this->m_age == p.m_age && this->m_name == p.m_name)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    string m_name;
    int m_age;
};

class DaYuFive
{
public:
    bool operator()(int val)
    {
        return val > 5;
    }
};

class ageDaYuTen
{
public:
    bool operator()(Person &p)
    {
        if(p.m_age > 10)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

bool compareByAge(const Person &a, const Person &b) 
{
    return a.m_age < b.m_age;
}

// 查找find内置数据类型
void test01()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // find(beg, end, value) 返回迭代器
    vector<int>::iterator pos = find(v.begin(), v.end(), 5);
    if(pos == v.end())
    {
        cout << "not found" << endl;
    }
    else
    {
        cout << (*pos) << endl;
    }
    
}

// 查找find自定义数据类型
void test02()
{
    vector<Person> v;
    Person p1("Tom", 17);
    Person p2("Gary", 19);
    Person p3("Ryan", 10);
    Person p4("Jack", 15);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    vector<Person>::iterator pos = find(v.begin(), v.end(), p1);
    if(pos == v.end())
    {
        cout << "not found" << endl;
    }
    else
    {
        cout << "found" << endl;
        cout << "name: " << pos->m_name << " age: " << (*pos).m_age << endl;
    }
}

// 有条件的查找find_if--内置数据类型
void test03()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    // find_if(beg, end, pred) 返回迭代器
    
    for(vector<int>::iterator pos = v.begin(); pos != v.end(); pos++)
    {
        pos = find_if(pos, v.end(), DaYuFive());
        if(pos == v.end())
        {
            cout << "not found" << endl;
            break;
        }
        else
        {
            cout << (*pos) << endl;
        }
    }
}
    
// 有条件的查找find_if--自定义数据类型
void test04()
{
    vector<Person> v;
    Person p1("Tom", 17);
    Person p2("Gary", 19);
    Person p3("Ryan", 10);
    Person p4("Jack", 5);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);
    
    for(vector<Person>::iterator pos = v.begin(); pos != v.end(); pos++)
    {
        pos = find_if(pos, v.end(), ageDaYuTen());
        if(pos == v.end())
        {
            cout << "not found" << endl;
            break;
        }
        else
        {
            cout << "name: " <<(*pos).m_name << " age: " << pos->m_age << endl;
        }
    }
}    
    
// 查找重复相邻元素adjacent_find
void test05()
{
    vector<int> v;
    v.push_back(2);
    v.push_back(0);
    v.push_back(3);
    v.push_back(1);
    v.push_back(4);
    v.push_back(3);
    v.push_back(3);

    vector<int>::iterator it = adjacent_find(v.begin(), v.end());
    if(it == v.end())
    {
        cout << "not found" << endl;
    }
    else
    {
        cout << (*it) << endl;
    }
}

// 查找指定元素是否存在binary_search
void test06()
{
    vector<Person> v;
    Person p1("Tom", 17);
    Person p2("Gary", 17);
    Person p3("Ryan", 10);
    Person p4("Jack", 15);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    const Person target("Tom", 17);
    sort(v.begin(), v.end(), compareByAge);

    bool ret = binary_search(v.begin(), v.end(), target, compareByAge);
    if(ret)
    {
        cout << "found" << endl;
    }
    else
    {
        cout << "not found" << endl;
    }
}

// 统计内置数据类型count
void test07()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(20);

    int number = count(v.begin(), v.end(), 10);
    cout << number << endl;
}

// 统计自定义数据类型count
void test08()
{
    vector<Person> v;
    Person p1("Tom", 17);
    Person p2("Gary", 17);
    Person p3("Ryan", 10);
    Person p4("Jack", 15);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    const Person target("Tom", 17);

    int number = count(v.begin(), v.end(), target);
    
    cout << number << endl;

}

void test09()
{
    vector<Person> v;
    Person p1("Tom", 17);
    Person p2("Gary", 17);
    Person p3("Ryan", 11);
    Person p4("Jack", 15);
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    const Person target("Tom", 17);

    int number = count_if(v.begin(), v.end(), ageDaYuTen());
    
    cout << number << endl;
}

int main()
{
    test09();
    return 0;
}