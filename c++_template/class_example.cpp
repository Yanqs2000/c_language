#include <iostream>
using namespace std;

template<class NameType, class AgeType>
class Person
{
public:
    Person(NameType name, AgeType age)
    {
        this->name = name;
        this->age = age;
    }
    
    NameType name;
    AgeType age;

    void showPerson()
    {
        cout << "name: " << this->name << " age: " << this->age << endl;
    }
};

void test01()
{
    Person<string, int> p1("Tom", 18);
    p1.showPerson();
}


int main()
{
    test01();
    return 0;
}