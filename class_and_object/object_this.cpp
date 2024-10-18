#include<iostream>

using namespace std;

class Person
{
    int m_age;
};

void test01()
{
    Person p1;
    cout << "size of p1 is "<< sizeof(p1) << endl; //空对象的字节空间大小为1
}

void test02()
{
    Person p1;

}


//this，解决名称冲突，类似于python中的self;返回对象本身用*this,

class Student
{
public:
    Student(int age)
    {
        this->age = age;
    }

    int age;

    void show()
    {
        cout << "age is " << this->age << endl;
    }

    Student PersonAddAge(Student *stu)
    {
        this->age += stu->age;
        return *this;
    }
};

void test03()
{
    Student s1(18);
    s1.show();
}

void test04()
{
    Student s1(18);
    Student s2(20);
    s1.PersonAddAge(&s2).PersonAddAge(&s1).show();
    
}

int main()
{
    test04();

    return 0;
}

