#include <iostream>
using namespace std;

class shape{
public:
    virtual float Area() = 0;

    virtual ~shape()
    {
        // 如果 shape 类自身有需要清理的资源，会在这里进行
        // 对于这个例子，它只是为了支持多态删除
        cout << "shape destructor called." << endl;
    }
};

class square : public shape{
public:
    square(float x) : length(x) {}
    float Area() override 
    { 
        return length * length; 
    }
    
    ~square() override
    { // 派生类的析构函数也可以加 override 关键字，让编译器检查是否正确覆盖
        cout << "square destructor called." << endl;
    }
private:
    float length;
};

class Circle : public shape{
public:
    Circle(float r = 3) : radius(r) {}
    float Area() override 
    { 
        return 3.14f * radius * radius; 
    }
    ~Circle() override
    {
        cout << "Circle destructor called." << endl;
    }
private:
    float radius;
};

int main()
{
    Circle ob1;
    shape *s1 = new square(5);
    
    shape &s2 = ob1;
    cout << s1->Area() << " ";
    cout << s2.Area() << endl;
    cout << "-----------" << endl;
    delete s1;
    cout << "-----------" << endl;
    return 0;
}
