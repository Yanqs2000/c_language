#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
int cur = 1;
const int MAX = 10;

void printOdd()
{
    while(true)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if(cur > MAX) return;
        if(cur % 2 == 1) {
            std::cout << cur++ << std::endl;
        }
    }
}

void printEven()
{
    while (true)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (cur > MAX)
            return;
        if (cur % 2 == 0)
        {
            cur = cur + 10;
            std::cout << cur << std::endl;
            cur = cur - 10;
            cur++;
        }
    }
}

int main()
{
    std::thread t1(printOdd);
    std::thread t2(printEven);

    t1.join();
    t2.join();

    std::cout << "over" << std::endl;
    return 0;
}
