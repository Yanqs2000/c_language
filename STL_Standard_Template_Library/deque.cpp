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

int main()
{
    test01();
}