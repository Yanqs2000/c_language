// 链表，由节点组成，每个节点包含数据域和指针域
// 数组是一段连续的线性空间，而链表则是由节点组成，每个节点包含数据部分和指向下一个节点的指针，
// 数据域部分：存储数据元素，指针域存储下一个节点的地址，最后一个节点的指针为空。
// 优点：可以对任意位置进行快速添加和删除元素
// 缺点：容器的遍历元素，没有数组快，占用空间大，因为每个节点除了数据域，还包含一个指针域
// STL中的链表是一个双向链表，每一个节点包含了前一个节点和后一个节点的指针，最后一个节点的后指针指向第一个节点，形成一个环。
// push_front(),pop_front(),push_back(),pop_back(),
// 迭代器：begin(),end(),insert()
// 重要性质：插入、删除、都不会引起原有迭代器（指针）的失效，在vector中不成立

#include <iostream>
#include <list>

using namespace std;

// 降序
bool MyCompare(int a, int b)
{
    return  a > b;
} 

void printList(const list<int> &l) 
{
    for (list<int>::const_iterator it = l.begin(); it != l.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
        
}

// 构造list
void test01()
{
    list<int> l1;

    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);

    list<int> l2(l1.begin(), l1.end());
    list<int> l3(10,100);

    printList(l1);
    printList(l2);
    printList(l3);
}

// 赋值
void test02()
{
    list<int> l1;

    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);

    list<int> l2;
    l2 = l1;

    list<int> l3;
    l3.assign(l1.begin(), l1.end());

    printList(l2);
}

// 交换
void test03()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_front(100);

    list<int> l2;
    l2.assign(10,100);

    printList(l1);
    printList(l2);

    l1.swap(l2);
    printList(l1);
    printList(l2);
}

// list容器大小操作
void test04()
{
    list<int> l1;
    l1.assign(10,100);

    list<int> l2;

    for (size_t i = 0; i < 4; i++)
    {
        l2.push_back(i * 10);
        l2.push_front(i * 2);
    }
    
    if(!l1.empty() && !l2.empty())
    {
        cout << "l1 size " << l1.size() << endl;
        cout << "l2 size " << l2.size() << endl;
    }

    l1.resize(20,1000);
    printList(l1);
    l1.resize(2);
    printList(l1);
}

//插入和删除
void test05()
{
    list<int> l1;
    // 头插和尾插
    l1.push_back(12);
    l1.push_back(13);
    l1.push_back(14);
    l1.push_back(1);
    l1.push_front(100);
    l1.push_front(200);
    printList(l1);

    // 头删和尾删
    l1.pop_back();
    l1.pop_front();
    printList(l1);

    // 插入
    l1.insert(l1.begin(),1000);// list链表的位置只能用迭代器
    list<int>::iterator it = l1.begin(); //这个it指向1000的位置
    l1.insert(++it,99);
    printList(l1); 

    // 删除
    it = l1.begin(); //这个it指向新链表的首位置
    l1.erase(++it);
    printList(l1);

    // 移除
    l1.remove(10); // 删除所有匹配的值
    printList(l1);

    // 清空
    l1.clear();

}

// 数据存取，list不支持[]、at方式，它是非连续的
void test06()
{
    list<int> l1;
    l1.push_back(10);
    l1.push_back(20);
    l1.push_back(30);

    printList(l1);

    cout << "last element: " << l1.back() << endl;
    cout << "first element:" << l1.front() << endl;
}

// list反转和排序
void test07()
{
    list<int> l1;
    l1.push_back(1);
    l1.push_back(4);
    l1.push_front(5);
    l1.push_back(7);

    // 反转
    printList(l1);
    l1.reverse();
    printList(l1);

    if(true)
    {
        l1.sort(MyCompare);
        printList(l1);
    }
    else
    {
        l1.sort(); // 默认从小到大，非连续内存（不支持随机访问迭代器）不能用标准算法，容器有自带的函数
        printList(l1);

        l1.reverse(); // sort加reverse,从大到小
        printList(l1);
    }
}

int main()
{
    test05();
    
    return 0;
}