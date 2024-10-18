#include<iostream>

using namespace std;
//继承
class Base
{
public:
    void header()
    {
        cout<<"This is header"<<endl;
    }
    void footer()
    {
        cout<<"This is footer"<<endl;
    }
    void left()
    {
        cout<<"This is left"<<endl;
    }
    void right()
    {
        cout<<"This is right"<<endl;
    }

};

class java: public Base
{
public:
    void content()
    {
        cout<<"This is java"<<endl;
    }
};

class python: public Base
{
public:
    void content()
    {
        cout<<"This is python"<<endl;
    }
};


void test01()
{
    java j;
    j.header();
    j.left();
    j.content();
    j.right();
    j.footer();

    python p;
    p.header();
    p.left();
    p.content();
    p.right();
    p.footer();
}

int main()
{
    test01();
    return 0;
}