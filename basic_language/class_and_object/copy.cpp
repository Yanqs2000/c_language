#include <iostream>
#include <cstring>

using namespace std;

// 场景：学生类中有一个姓名指针，需要在堆区维护字符串
// 先演示默认拷贝构造带来的浅拷贝问题
class StudentShallow
{
public:
    char* name;
    int age;

    StudentShallow(const char* n, int a)
    {
        age = a;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        cout << "StudentShallow 构造函数" << endl;
    }

    void show() const
    {
        cout << "姓名: " << name << ", 年龄: " << age
             << ", name地址: " << static_cast<void*>(name) << endl;
    }

    ~StudentShallow()
    {
        cout << "StudentShallow 析构函数，准备释放: "
             << static_cast<void*>(name) << endl;
        delete[] name;
    }
};

// 再演示自定义拷贝构造实现深拷贝
class StudentDeep
{
public:
    char* name;
    int age;

    StudentDeep(const char* n, int a)
    {
        age = a;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        cout << "StudentDeep 构造函数" << endl;
    }

    // 拷贝构造函数：重新开辟空间复制内容
    StudentDeep(const StudentDeep& other)
    {
        age = other.age;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        cout << "StudentDeep 拷贝构造函数" << endl;
    }

    void show() const
    {
        cout << "姓名: " << name << ", 年龄: " << age
             << ", name地址: " << static_cast<void*>(name) << endl;
    }

    ~StudentDeep()
    {
        cout << "StudentDeep 析构函数，准备释放: "
             << static_cast<void*>(name) << endl;
        delete[] name;
    }
};

void testShallowCopy()
{
    cout << "========== 具体类中的浅拷贝 ==========" << endl;
    StudentShallow s1("Tom", 20);
    StudentShallow s2 = s1; // 默认拷贝构造：浅拷贝

    cout << "拷贝前：" << endl;
    s1.show();
    s2.show();

    cout << "可以看到两个对象中的 name 地址相同，说明它们指向同一块堆区内存。" << endl;
    cout << "如果让两个对象正常析构，就会发生重复释放。" << endl;

    // 为了避免演示时程序崩溃，这里手动断开 s2 的指针
    s2.name = nullptr;
}

void testDeepCopy()
{
    cout << "========== 具体类中的深拷贝 ==========" << endl;
    StudentDeep s1("Jerry", 22);
    StudentDeep s2 = s1; // 调用拷贝构造函数：深拷贝

    cout << "拷贝后：" << endl;
    s1.show();
    s2.show();

    cout << "修改 s2 的姓名首字母后，再观察两个对象：" << endl;
    s2.name[0] = 'M';
    s1.show();
    s2.show();

    cout << "可以看到两个对象中的 name 地址不同，且修改 s2 不会影响 s1。" << endl;
}

int main()
{
    testShallowCopy();
    cout << endl;
    testDeepCopy();
    return 0;
}