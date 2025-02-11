#include <iostream>

using namespace std;
//动态多态是面向对象编程中多态性的一种形式，通常通过继承和虚函数来实现。它允许程序在运行时决定执行哪个函数
//1.通过基类指针或引用调用虚函数时，会根据指针指向的对象来确定调用哪个函数
//2.如果对象是派生类对象，则调用派生类的函数，如果对象是基类对象，则调用基类的函数
//3.在基类中声明虚函数，在派生类中重写该函数

//动态多态满足条件
//1.有继承关系
//2.子类重写父类中的虚函数

class Animal 
{
public:
    virtual void speak() 
    {
        cout << "Animal speaks" << endl;
    }
};

class Cat :public Animal
{
public:
    void speak()
    {
        cout << "Cat speaks" << endl;
    }
};

//执行说话的函数
void doSpeak(Animal &animal)
{
    animal.speak();
}

void test01()
{
    Cat cat;
    doSpeak(cat);
}

int main()
{
    test01();
    return 0;
}