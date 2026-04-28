#include <iostream>
 
class Animal
{
public:
    int age;
    Animal(int age): age(age) {}
    virtual void speak() = 0; // 纯虚函数，Animal 是抽象类 
    virtual ~Animal() {} // 虚析构函数，确保派生类对象被正确销毁
};

class Dog : public Animal
{
public:
    Dog(int age): Animal(age) {}
    void speak() override
    {
        std::cout << "Woof! I am " << age << " years old." << std::endl;
    }
    ~Dog() override
    {
        std::cout << "Dog destructor called." << std::endl;
    }
};

class Cat : public Animal
{
public:
    Cat(int age): Animal(age) {}
    void speak() override
    {
        std::cout << "Meow! I am " << age << " years old." << std::endl;
    }
    ~Cat() override
    {
        std::cout << "Cat destructor called." << std::endl;
    }
};

class AnimalFactory
{
public:
    virtual Animal* createAnimal(int age) = 0; // 纯虚函数，AnimalFactory 是抽象工厂类
    virtual ~AnimalFactory() {} // 虚析构函数，确保派生类对象被正确销毁
};

class DogFactory : public AnimalFactory
{
public:
    Animal* createAnimal(int age) override
    {
        return new Dog(age);
    }
    ~DogFactory() override
    {
        std::cout << "DogFactory destructor called." << std::endl;
    }
};

class CatFactory : public AnimalFactory
{
public:
    Animal* createAnimal(int age) override
    {
        return new Cat(age);
    }
    ~CatFactory() override
    {
        std::cout << "CatFactory destructor called." << std::endl;
    }
};

int main()
{
    AnimalFactory* dogFactory = new DogFactory();
    Animal* myDog = dogFactory->createAnimal(5);
    myDog->speak();

    AnimalFactory* catFactory = new CatFactory();
    Animal* myCat = catFactory->createAnimal(3);
    myCat->speak();

    delete myDog; // 通过基类指针删除对象，确保调用正确的析构函数
    delete myCat; // 通过基类指针删除对象，确保调用正确的析构函数
    delete dogFactory; // 删除工厂对象
    delete catFactory; // 删除工厂对象

    return 0;
}