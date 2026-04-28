#include <iostream>
#include <list>

using namespace std;

class MyStack
{
private:
    list<int> l; // 使用list作为底层容器
public:
    void push(int x)
    {
        l.push_back(x); // 在链表尾部添加元素
    }

    void pop()
    {
        if(!l.empty())
        {
            l.pop_back(); // 移除链表尾部元素
        }
    }

    int top()
    {
        if(!l.empty())
        {
            return l.back(); // 返回链表尾部元素
        }
    }
};

int main()
{
    return 0;
}