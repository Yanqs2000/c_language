#include <iostream>
#include <stdexcept>
#include <ostream>
#include <memory>

using namespace std;

template <typename T>
class CycleArray
{
    // 动态数组
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
        // 将新数组的所有权给旧数组
        arr = move(newArr);
        // 重置start和end指针
        start = 0;
        end = count;
        size = newSize;
    }
public:
    // 默认构造函数(如果没有参数传入)
    CycleArray() : CycleArray(1) {}
    // 委托构造函数
    explicit CycleArray(int size) : start(0), end(0), count(0), size(size)
    {
        arr = make_unique<T[]>(size);
    }
    // 在数组头部添加元素，时间复杂度O(1)
    void addFirst(const T &value)
    {
        // 当数组满时，自动扩容为原本的2倍
        if(isFull())
        {
            resize(size * 2);
        }
        // start为闭区间, 先左移，再赋值
        start = (start - 1 + size) % size;
        arr[start] = value;
        count++;
    }

    // 删除数组头部元素
    void removeFirst()
    {
        if(isEmpty())
        {
            throw runtime_error("Array is empty");
        }
        // start为闭区间，先赋值，再右移
        arr[start] = T();
        start = (start + 1) % size;
        count--;
        // 当数组元素个数小于等于数组大小的一半时，自动缩容为原本的一半
        if(count > 0 && count <= size / 4)
        {
            resize(size / 2);
        }
    }

    // 在数组尾部添加元素，时间复杂度O(1)
    void addLast(const T &value)
    {
        // 当数组满时，自动扩容为原本的2倍
        if(isFull())
        {
            resize(size * 2);
        }
        // end为开区间，先赋值，再右移
        arr[end] = value;
        end = (end + 1) % size;
        count++;
    }

    // 删除数组尾部元素
    void removeLast()
    {
        if(isEmpty())
        {
            throw runtime_error("Array is empty");
        }
        // end为开区间，先左移，再赋值
        end = (end - 1 + size) % size;
        arr[end] = T();
        count--;
        // 当数组元素个数小于等于数组大小的一半时，自动缩容为原本的一半
        if(count > 0 && count <= size / 4)
        {
            resize(size / 2);
        }
    }

    // 获取数组头部元素
    T getFirst() const
    {
        if(isEmpty())
        {
            throw runtime_error("Array is empty");
        }
        return arr[start];
    }

    // 获取数组尾部元素
    T getLast() const
    {
        if(isEmpty())
        {
            throw runtime_error("Array is empty");
        }
        return arr[(end - 1 + size) % size];
    }

    bool isFull() const
    {
        return count == size;
    }

    int getSize() const
    {
        return size;
    }

    bool isEmpty() const
    {
        return count == 0;
    }

    void printCycleArray() const
    {
        for (int i = 0; i < count; i++)
        {
            cout << arr[(start + i) % size] << " ";
        }
        cout << endl;
    }
};

int main()
{
    CycleArray<int> arr(5);
    arr.addFirst(1);
    arr.addFirst(2);
    arr.addFirst(3);
    arr.addFirst(4);
    arr.addFirst(5);
    arr.printCycleArray();
    cout << arr.getSize() << endl;
}