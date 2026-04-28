#include <iostream>
#include <deque>

using namespace std;

class MyStack
{
private:
    deque<int> d; // 使用deque作为底层容器
public:
    void push(int x)
    {
        d.push_back(x); // 在队尾添加元素
    }

    void pop()
    {
        if(!d.empty())
        {
            d.pop_back(); // 移除队尾元素
        }
    }

    int top()
    {
        if(!d.empty())
        {
            return d.back(); // 返回队尾元素
        }
    }

    bool empty()
    {
        return d.empty(); // 判断栈是否为空
    }

    int size()
    {
        return d.size(); // 返回栈的大小
    }
};

class MyQueue
{
private:
    deque<int> d; // 使用deque作为底层容器
public:
    void push(int x)
    {
        d.push_back(x); // 在队尾添加元素
    }
    void pop()
    {
        if(!d.empty())
        {
            d.pop_front(); // 移除队头元素
        }
    }

    int front()
    {
        if(!d.empty())
        {
            return d.front(); // 返回队头元素
        }
    }
    int back()
    {
        if(!d.empty())
        {
            return d.back(); // 返回队尾元素
        }
    }

    bool empty()
    {
        return d.empty(); // 判断队列是否为空
    }

    int size()
    {
        return d.size(); // 返回队列的大小
    }
};


int main()
{
    return 0;
}