// stack是一种先进后出的数据结构，栈容器，栈底在上，栈顶在下，栈不能有遍历，因为外界只能通过栈顶访问元素
// push()向栈顶添加元素，pop()删除栈顶元素，top()返回栈顶元素，empty()判断栈是否为空，size()返回栈的大小
#include <iostream>
#include <stack>

using namespace std;

void test01()
{
    stack<int> a;

    a.push(10);
    a.push(20);
    a.push(30);

    // 只要栈不为空，查看栈顶，并且执行出栈操作
    while(!a.empty())
    {
        cout << a.top() << endl;
        a.pop();
    }

    cout << "size is " << a.size() << endl;
}

int main()
{
    test01();
}