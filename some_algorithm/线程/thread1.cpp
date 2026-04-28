#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
int turn = 0;
const int Loop = 10;

void printa()
{
    for(int i = 0; i < Loop;)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if(turn == 0)
        {
            std::cout << "a";
            turn = 1;
            i++;
        }
    }
}

void printb()
{
    for (int i = 0; i < Loop;)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (turn == 1)
        {
            std::cout << "b";
            turn = 2;
            i++;
        }
    }
}

void printc()
{
    for (int i = 0; i < Loop;)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (turn == 2)
        {
            std::cout << "c";
            turn = 0;
            i++;
        }
    }
}


int main()
{
    std::thread t1(printa);
    std::thread t2(printb);
    std::thread t3(printc);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "over" << std::endl;
    return 0;
}