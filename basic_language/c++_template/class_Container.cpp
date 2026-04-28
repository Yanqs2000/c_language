#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// 基类模板 Container
template <typename T>
class Container
{
protected:
    vector<T> data; // 用于存储元素

public:
    // 添加元素
    void add(const T &value)
    {
        data.push_back(value);
    }

    // 删除指定下标的元素
    void remove(int index)
    {
        if (index >= 0 && index < data.size())
        {
            data.erase(data.begin() + index);
        }
        else
        {
            cout << "删除失败：下标越界" << endl;
        }
    }

    // 获取当前元素个数
    int size() const
    {
        return data.size();
    }

    // 重载 [] 运算符，实现访问元素
    T &operator[](int index)
    {
        if (index < 0 || index >= data.size())
        {
            throw out_of_range("下标越界");
        }
        return data[index];
    }

    // const 版本，支持常对象访问
    const T &operator[](int index) const
    {
        if (index < 0 || index >= data.size())
        {
            throw out_of_range("下标越界");
        }
        return data[index];
    }

    // 输出所有元素
    void display() const
    {
        for (const auto &x : data)
        {
            cout << x << " ";
        }
        cout << endl;
    }
};

// 派生类模板 SortedContainer
template <typename T>
class SortedContainer : public Container<T>
{
public:
    // 重写 add，使插入后自动排序
    void add(const T &value)
    {
        this->data.push_back(value);
        sort(this->data.begin(), this->data.end());
    }
};

int main()
{
    cout << "普通 Container<int>:" << endl;
    Container<int> c;
    c.add(5);
    c.add(2);
    c.add(8);
    c.display(); // 5 2 8

    c.remove(1);
    c.display(); // 5 8

    cout << "c[1] = " << c[1] << endl;

    cout << "\n自动排序 SortedContainer<int>:" << endl;
    SortedContainer<int> sc;
    sc.add(5);
    sc.add(2);
    sc.add(8);
    sc.add(1);
    sc.display(); // 1 2 5 8

    cout << "sc[2] = " << sc[2] << endl;

    cout << "\nSortedContainer<string>:" << endl;
    SortedContainer<string> s;
    s.add("pear");
    s.add("apple");
    s.add("orange");
    s.display(); // apple orange pear

    return 0;
}