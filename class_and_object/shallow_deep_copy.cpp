#include<iostream>
using namespace std;

//深拷贝和浅拷贝

class Person
{
public:   
    //1.构造函数 进行初始化操作 只调用一次 不写就是空实现 有点类似于python的self.__init__
    //1.构造函数可以重载,可以有参数，函数名与类名相同

    Person()//无参构造
    {
        cout << "Person的无参构造函数调用" << endl;
    }

    Person(int age, int height) //有参构造
    {
        m_age = age;
        m_height = new int(height);//在堆区开辟空间
        cout << "Person的有参构造函数调用" << endl;
    }

    //2.析构函数 对象在销魂前 进行清理操作 只调用一次 不可以有参数，不可以重载
    ~Person()
    {
        if (m_height != NULL)
        {
            delete m_height;
            m_height = NULL;
        }
    
        cout << "Person的析构函数调用" << endl;
    }

    int m_age;
    int *m_height; //指针类型
};

//调用
void test01() //创建对象时，会自动调用构造函数；对象销毁时，会自动调用析构函数
{
    Person p2(18,170);
    Person p1(p2); //浅拷贝，两者的内存地址是同一个，p1和p2指向同一个地址，当p1销毁时，p2也会销毁，所以需要深拷贝
    cout << "p2的年龄为：" << p2.m_age << "，身高为：" << *p2.m_height << endl;

}

int main()
{
    test01();

    return 0;
}