#include <iostream>
#include <vector>
using namespace std;

/*
快速排序 1.以第一个数为基准，将比基准小的数交换到前边，将比基准大的数交换到后边
        2.对左右区间重复上述步骤，直到区间内只有一个数
        平均时间复杂度O(nlogn)，空间复杂度O(logn)
*/

void quickSort(vector<int> &nums, int begin, int end)
{
    int i, j, t, pivot;
    if (begin > end) //递归结束条件
        return;

    pivot = nums[begin]; //基准数
    i = begin;
    j = end;

    while(i != j)
    {
        // 从右向左找比基准数小的数（从右边开始找）
        while(nums[j] >= pivot && i < j)
            j--;
        // 从左向右找比基准数大的数（从左边开始找）
        while(nums[i] <= pivot && i < j)
            i++;
        if(i < j)
        {
            // 交换两个数
            t = nums[i];
            nums[i] = nums[j];
            nums[j] = t;
        }
    }
    // 最后将基准数归位
    nums[begin] = nums[i];
    nums[i] = pivot;
    for (int m = 0; m < nums.size(); m++)
        cout << nums[m] << " ";
    cout << endl;
    quickSort(nums, begin, i - 1);
    quickSort(nums, i + 1, end);
}

int main()
{
    vector<int> nums = {6, 3, 2, 4, 5, 7, 8, 10, 1, 0, 9};
    int len = nums.size();
    quickSort(nums, 0, len - 1);
    for(int i = 0; i < len; i++)
        cout << nums[i] << " ";
    cout << endl;
    return 0;
}