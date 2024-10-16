// 设计一个圆类，求周长
#include<iostream>
using namespace std;

const double PI = 3.1415926;

//类的名称
class Circle
{
    //访问权限
public:
    //属性
    int m_r;//圆的半径
    //行为
    double calculate()
    {
        return 2 * PI * m_r;
    }
};

//设计一个学生类，有姓名和学号属性，行为：赋值和显示学号
class Student
{
public:
    //属性
    string name;
    string id;
    //行为
    void set_name_id(string name1, string id1)
    {
        name = name1;
        id = id1;
    }
    void show_name_id()
    {
        cout << "姓名：" << name << "学号：" << id << endl;
    }
    void get_age1()
    {
        get_age();
    }

private:
    //私有属性
    int age = 18;

    //私有行为
    void get_age()
    {
        cout << "年龄：" << age << endl;
    }
};


//设计一个立方体类
class Cube
{
public:
    //属性

    //行为
    void set_length_width_height(int set_length, int set_width, int set_height)
    {
        length = set_length;
        width = set_width;
        height = set_height;
    }
    void show_length_width_height()
    {
        cout << "长：" << length << "宽：" << width << "高：" << height << endl;
    }

    int calculate_area()
    {
        return 2 * (length * width + length * height + width * height);
    }
    int calculate_volume()
    {
        return length * width * height;
    }
    //利用成员函数判断
    bool isSameByClass(Cube &C)
    {
        if(calculate_area() == C.calculate_area() && calculate_volume() == C.calculate_volume())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
private:
    //私有属性
    int length;
    int width;
    int height;
};


bool isSame(Cube &C1, Cube &C2)
{
    if(C1.calculate_area() == C2.calculate_area() && C1.calculate_volume() == C2.calculate_volume())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    //创建对象
    Cube C1;
    C1.set_length_width_height(10, 20, 30);
    C1.show_length_width_height();
    cout << "表面积：" << C1.calculate_area() << endl;
    cout << "体积：" << C1.calculate_volume() << endl;

    Cube C2;
    C2.set_length_width_height(20, 10, 30);
    C2.show_length_width_height();
    cout << "表面积：" << C2.calculate_area() << endl;
    cout << "体积：" << C2.calculate_volume() << endl;

    bool a = isSame(C1, C2);
    cout << "result a:" << a << endl;

    bool b = C1.isSameByClass(C2);
    cout << "result b:" << b << endl;
    return 0;
}