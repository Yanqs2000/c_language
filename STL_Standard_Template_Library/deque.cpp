// 双端数组，可以对头端进行插入和删除操作，效率快，双端扩展

#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

void printdeque(const deque<int> &d)
{
    for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)// 只读迭代器
    {
        cout << *it << " ";
    }
    cout << endl;
}

// deque容器构造
void test01()
{
    deque<int> d1;
    for (int i = 0; i < 10; i++)
    {
        d1.push_back(i);
    }
    printdeque(d1);

    deque<int> d2(d1.begin() + 1, d1.end());
    printdeque(d2);
    
    deque<int> d3(10, 100);

    deque<int> d4(d3);
}

// deque容器赋值操作
void test02()
{
    deque<int> d;
    for (int i = 0; i < 10; i++)
    {
        d.push_back(i);
    }

    deque<int> d2;
    d2 = d;

    deque<int> d3;
    deque<int> d4;
    d3.assign(d.begin(), d.end());
    d4.assign(10, 100);
}

// deque容器大小操作
// 没有capacity这个属性
void test03()
{
    deque<int> d;
    for(int i = 0; i < 10; i++)
    {
        d.push_back(i);
    }
    if(d.empty())
    {
        cout << "d is empty" << endl;
    }
    else
    {
        cout << "d is not empty" << endl;
        cout << "the size of d is " << d.size() << endl;
    }
    d.resize(15,1);
    cout << "the size of d is " << d.size() <<endl;
    printdeque(d);
}

// deque容器插入和删除
void test04()
{
    deque<int> d;
    d.push_back(100);
    d.push_front(10);
    printdeque(d);
    d.pop_back();
    printdeque(d);

    d.insert(d.begin(),1000);
    d.insert(d.begin() + 1, 2, 10000);
    printdeque(d);

    // 按照区间进行插入
    deque<int> de;
    de.push_back(1);
    de.push_back(2);
    de.push_back(3);

    d.insert(d.begin(), de.begin(), de.end() - 1);

    //删除
    deque<int> d1 = de;
    deque<int>::iterator it = d1.begin();
    it++;
    d1.erase(it);
    d1.erase(d1.begin() + 1, d1.end());
    printdeque(d1);
}

// deque数据存取
void test05()
{
    deque<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }
    for (int j = 0; j < v1.size(); j++)
    {
        cout << v1.at(j) << " ";
        cout <<v1[j] << " ";
    }
    cout << endl;
    cout << v1.front() << " ";
    cout << v1.back() << " ";
    cout << endl;
}

//排序算法
void test06()
{
    deque<int> d;
    d.push_back(10);
    d.push_back(1);
    d.push_back(10);
    d.push_front(3);
    d.push_front(22);
    d.push_front(1);
    printdeque(d);
    sort(d.begin(),d.end());
    printdeque(d);
}

void test07()
{
    
}
int main()
{
    test06();
    test07();
}