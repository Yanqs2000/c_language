// vector数组和数组非常相似，称为单端数组，单端数据，支持在末尾插入和删除操作，其他位置效率低，支持动态扩展
// 动态扩展并不是在数组之后继续开辟，而是重新开辟一个更大的数组，将原数组内容复制到新数组，释放原数组空间
// v.begin指的是第一位，v.end指的是最后一位的下一个位置[v.begin, v.end)
#include <iostream>
#include <vector>

using namespace std;

void printvector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
}

// vector容器的构造
void test01()
{
    vector<int> v1; // 默认构造,无参构造
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);// 添加元素
    }
    printvector(v1);

    vector<int> v2(v1.begin(), v1.end()); // 用v1的迭代器区间构造v2

    vector<int> v3(10, 100); // 10个100,n个element的构造

    vector<int> v4(v3); // 拷贝构造
}

// vector容器的赋值
void test02()
{
    vector<int> v1;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
    }

    // 等号赋值
    vector<int> v2;
    v2 = v1;

    // assign赋值
    vector<int> v3;
    v3.assign(v1.begin() + 1, v1.end() - 1);
    printvector(v3);

    // n个element的赋值
    vector<int> v4;
    v4.assign(10, 100);
    printvector(v4);
}

// vector容器的容量和大小
// empty() 空 size() 元素个数 capacity() 容量 resize() 重新指定大小
void test03()
{
    vector<int> v1(10,100);
    vector<int> v2;
    vector<int> v3;
    for (int i = 0; i < 10; i++)
    {
        v3.push_back(i);
    }
    
    if (v2.empty())
    {
        cout << "v2为空" << endl;
    }
    else
    {
        cout << "v2不为空" << endl;
    }
    cout << "v3的大小为:" << v3.capacity()<< endl;
    cout << "v3的大小为:" << v3.size()<< endl;

    // 重新指定大小
    v3.resize(18);
    cout << "v3的大小为:" << v3.capacity()<< endl;
    printvector(v3);

    v3.resize(5);
    cout << "v3的大小为:" << v3.capacity()<< endl;
    printvector(v3);
}

// vector容器的插入和删除
// push_back() 尾部插入 pop_back() 尾部删除 
// insert  erase 需要迭代器(指针)来指向
// clear 删除容器中的所有元素
void test04()
{
    vector<int> v1;
    // 尾插
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(30);
    // 尾删
    v1.pop_back();
    printvector(v1);
    // insert
    v1.insert(v1.begin(),100);
    v1.insert(v1.begin(),2,1000);//在任意位置插入元素，只需v1.begin() + n 即可
    printvector(v1);

    // erase
    v1.erase(v1.begin()); // 提供迭代器
    v1.erase(v1.begin() + 1,v1.end()-1);// 提供区间
    printvector(v1);
}

// vector中的数据存取
// 成员函数at() 重载[] 获取第一个数据front() 获取最后一个数据back()
void test05()
{
    vector<int> v1;
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

// vector的互换,swap将两个容器内的元素进行互换
void test06()
{
    vector<int> v1, v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i + 10);
    }
    v1.swap(v2);
    printvector(v1);
    printvector(v2);
}

// vector预留空间
// reserve(n) 预留n个元素空间，如果n小于当前容量，则不改变容量
int main()
{
    test06();
    cout << "程序结束" << endl;
    return 0;
}