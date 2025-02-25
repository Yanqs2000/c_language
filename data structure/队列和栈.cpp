// 用双链表作为底层数据结构实现队列和栈
#include <iostream>
#include <list>
#include <vector>

using namespace std;

template <typename T>
class MyQueue 
{
private:
    list<T> list;
public:
    void push(const T& val)
    {
        list.push_back(val);
    }

    void pop()
    {
        list.pop_front();
    }

    T& front()
    {
        return list.front();
    }

    T& back()
    {
        return list.back();
    }

    bool empty()
    {
        return list.empty();
    }

    int size()
    {
        return list.size();
    }
};

template <typename E>
class MyStack
{
private:
    list<int> list;
public:
    void push(const E& val)
    {
        list.push_back(val);
    }

    E pop()
    {
        E value = list.back();
        list.pop_back();
        return value;
    }

    E top() const
    {
        return list.back();
    }

    bool empty() const
    {
        return list.empty();
    }

    int size() const
    {

        return list.size();
    }
};

template <typename F>
class MyStack2
{
private:
    vector<T> vector;
public:
    void push(const F& val)
    {
        vector.push_back(val);
    }

    F pop()
    {
        F value = vector.back();
        vector.pop_back();
        return value;
    }

    F top() const
    {
        return vector.back();
    }

    bool empty() const
    {
        return vector.empty();
    }

    int size() const
    {
        return vector.size();
    }
};

int main()
{
    MyQueue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    cout << q.size() << endl;

    MyStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    while (stack.size() > 0) 
    {
        std::cout << stack.pop() << std::endl;
    }
}