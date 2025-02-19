#include <iostream>
#include <stdexcept>
#include <ostream>

using namespace std;

template <typename T>
class CycleArray
{
    unique_ptr<T[]> arr;
    int start;
    int end;
    int count;
    int size;

    // 自动扩缩容辅助函数
    void resize(int newSize)
    {
        // 创建新的数组
        unique_ptr<T[]> newArr = make_unique<T[]>(newSize);
        // 将旧数组中的元素复制到新数组中
        for (int i = 0; i < count; i++)
        {
            newArr[i] = arr[(start + i) % size];
        }
        arr = move(newArr);
        // 重置start和end指针
        start = 0;
        end = count;
        size = newSize;
    }
};