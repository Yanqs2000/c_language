#include<iostream>
#include<vector>
#include<algorithm>//标准算法的头文件

using namespace std;

void myPrint(int val)
{
    cout << val << endl;
}

//vector存放int类型
void test01()
{
    //vector容器，数组
    vector<int> v;

    //向容器中添加数据
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    //通过迭代器访问容器中的数据
    vector<int>::iterator itBegin = v.begin(); //起始迭代器，指向容器中第一个元素(指针)
    vector<int>::iterator itEnd = v.end(); //结束迭代器，指向容器中最后一个元素的下一个位置(指针)

    //第一种遍历方式
    while(itBegin != itEnd)
    {
        cout << *itBegin << endl;
        itBegin++;
    }

    //第二种遍历方式
    for(vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << endl;
    }

    //第三种遍历方式(回调函数)
    for_each(v.begin(), v.end(), myPrint);
}

//vector存放自定义数据类型
class Person
{
public:
    Person(string name, int age)
    {
        this->m_Name = name;
        this->m_Age = age;
    }

    string m_Name;
    int m_Age;
};

//vector存放Person数据类型
void test02()
{
    //定义容器
    vector<Person> v;

    Person p1("张三", 18);
    Person p2("李四", 19);
    Person p3("王五", 20);
    Person p4("赵六", 21);
    
    //将数据类型Person放入容器
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    //通过迭代器访问容器中的数据
    for(vector<Person>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "姓名：" << (*it).m_Name << " 年龄：" << (*it).m_Age << endl;//解引用之后用.方式
        cout << "姓名：" << it->m_Name   << " 年龄：" << it->m_Age   << endl;//指针用->
    }
}

//vector存放Person的指针数据类型
void test03()
{
    //定义容器
    vector<Person*> v;

    Person p1("张三", 18);
    Person p2("李四", 19);
    Person p3("王五", 20);
    Person p4("赵六", 21);
    
    //将数据类型Person放入容器
    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);

    //通过迭代器访问容器中的数据
    for(vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
    {
        //it是一个指针，指向的是Person*类型，是地址，所以需要解引用两次
        cout << "姓名：" << (**it).m_Name << " 年龄：" << (**it).m_Age << endl;//解引用之后用.方式
        cout << "姓名：" << (*it)->m_Name   << " 年龄：" << (*it)->m_Age   << endl;//指针用->
    }
}

//容器的容器(vector中存放vector,二维数组plus)
void test04()
{
    vector <vector<int>> v;
    //创建小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    //往小容器中添加数据
    for(int i = 0; i < 4; i++)
    {
        v1.push_back(i + 1);
        v2.push_back(i + 2);
        v3.push_back(i + 3);
    }
    //将小容器放入大容器
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);

    //通过迭代器访问容器中的数据
    for(vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
    {
        for(vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
        {
            cout << *vit << " ";  
        }
        cout << endl;
    }
}


int main() 
{
    test04();
}