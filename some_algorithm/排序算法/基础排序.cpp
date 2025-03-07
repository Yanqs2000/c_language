#include<iostream>
#include<vector>

using namespace std;

// 选择排序，遍历一遍数组，找到最小值，交换到前面
void sort(vector<int>& arr)
{
    int n = arr.size();
    for(int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        bool isSorted = false;

        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
                isSorted = true;
            }
        }
        swap(arr[i], arr[minIndex]);

        if (!isSorted)
        {
            cout << "提前结束算法" << endl;
            break;
        }
    }
}

// 冒泡排序，重复遍历数组，每次将最大的元素移动到数组末尾
void bubbleSort(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertSort(vector<int> &nums)
{
    int n = nums.size();
    // 维护[0, sortedIndex]是有序数组
    int sortedIndex = 0;
    while (sortedIndex < n)
    {
        // 将nums[sortedIndex]插入到有序数组[0，sortedIndex]中
        for(int i = sortedIndex; i > 0; i--)
        {
            if(nums[i] < nums[i - 1])
            {
                swap(nums[i], nums[i - 1]);
            }
            else
            {
                break;
            }
        }
        sortedIndex++;
    }
    
}


int main()
{
    vector<int> arr = {5, 1, 3, 4, 6};
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    insertSort(arr);
    //bubbleSort(arr);

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}