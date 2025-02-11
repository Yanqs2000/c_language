// map中所有元素都是pair
// pair中的第一个元素为key(键值)，起到索引作用，第二个元素为value(实值)
// 所有元素会根据元素的键值自动排序
// 属于关联式容器，底层结构是用二叉树实现
// map和mulitmap,是否允许容器中有重复的key值元素
#include <map>
#include <iostream>

using namespace std;

class Person
{
public:
    Person(string name, int age)
    {
        this->m_age = age;
        this->m_name = name;
    }
    string m_name;
    int m_age;
};

class Information
{
public:
    Information(string phone_number, string work_number)
    {
        this->m_phone_number = phone_number;
        this->m_work_number = work_number;
    }
    string m_phone_number;
    string m_work_number;
};

class MyCompare
{
public:
    // 作比较时,比较的是key的大小，因此mycompare中函数重载（）的类型为Person
    bool operator()(const Person &p1, const Person &p2) const
    {
        return p1.m_age > p2.m_age;
    }
};

void printMap(map<int, int> &m)
{
    for(map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key: " << (*it).first << " ";//first表示key值
        cout << "value: " << (*it).second << endl;//second表示value
    }
}

void printMap_Person_Information(map<Person, Information, MyCompare> &m)
{
    for(map<Person, Information, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
    {
        cout << "key: " << (*it).first.m_age << " " << (*it).first.m_name << " ";
        cout << "value: " << (*it).second.m_phone_number << " " << (*it).second.m_work_number << endl;//second表示value
    }
}

// 构造
void test01()
{
    map<int, int> m;     // 默认构造
    map<int, int> m2(m); // 拷贝构造
    map<int, int> m3;
    m3 = m;              // 赋值

    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(3, 20));
    m.insert(pair<int, int>(9, 30));
    m.insert(pair<int, int>(8, 40));
    m.insert(pair<int, int>(5, 90));

    printMap(m);
}

// 大小和交换
void test02()
{
    map<int, int> m;

    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(3, 20));
    m.insert(pair<int, int>(9, 30));
    m.insert(pair<int, int>(8, 40));
    m.insert(pair<int, int>(5, 90));

    map<int, int> m2;

    m2.insert(pair<int, int>(10, 1));
    m2.insert(make_pair(30, 2));
    m2.insert(pair<int, int>(90, 3));
    m2.insert(pair<int, int>(80, 4));
    m2.insert(pair<int, int>(50, 9));

    if(m.empty())
    {
        cout << "empty" << endl;
    }
    else
    {
        cout << "not empty" << endl;
        cout << m.size() << endl;
    }

    m.swap(m2);

    printMap(m);
    printMap(m2);
}

// 删除和插入
void test03()
{
    map<int, int> m;

    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(3, 20));
    m.insert(map<int, int>::value_type(4, 30));
    m[6] = 40;
    m.insert(pair<int, int>(9, 30));
    m.insert(pair<int, int>(8, 40));
    m.insert(pair<int, int>(5, 90));

    map<int, int> m2;

    m2.insert(pair<int, int>(10, 1));
    m2.insert(make_pair(30, 2));
    m2.insert(pair<int, int>(90, 3));
    m2.insert(pair<int, int>(80, 4));
    m2.insert(pair<int, int>(50, 9));

    // 删除
    m2.erase(m.begin()); // 按照迭代器删除
    m2.erase(3); // 按照key删除
    m.erase(m.begin(), m.end());
    m2.clear();  // 清空
}

// 查找和统计
void test04()
{
    map<int, int> m;

    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(3, 20));
    m.insert(map<int, int>::value_type(4, 30));
    m[6] = 40;
    m.insert(pair<int, int>(6, 100));
    m.insert(pair<int, int>(9, 30));
    m.insert(pair<int, int>(8, 40));
    m.insert(pair<int, int>(5, 90));

    map<int, int> m2;

    m2.insert(pair<int, int>(10, 1));
    m2.insert(make_pair(30, 2));
    m2.insert(pair<int, int>(90, 3));
    m2.insert(pair<int, int>(80, 4));
    m2.insert(pair<int, int>(50, 9));

    // 查找
    map<int, int>::iterator pos = m.find(6); // 利用key值查找元素

    if(pos != m.end())
    {
        cout << "already find " << (*pos).first << " " << (*pos).second << endl;
    }
    else
    {
        cout << "not found" << endl;
    }

    // 统计
    int count = m.count(6); //查找key值的个数
    cout << count << endl;
}

// 自定义排序规则
void test05()
{
    Person p1("Tom", 18);
    Person p2("Gary", 10);
    Person p3("Lina", 12);
    Information I1("138", "ox12");
    Information I2("134", "re15");
    Information I3("138", "ex12");

    map<Person, Information, MyCompare> m;
    m.insert(make_pair(p1, I1));
    m.insert(make_pair(p2, I2));
    m.insert(make_pair(p3, I3));

    printMap_Person_Information(m);
}

int main()
{
    test05();
    return 0;
}