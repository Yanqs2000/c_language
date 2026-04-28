#include <iostream>
#include <vector>
using namespace std;

/*
归并排序：
1.把长度为n的输入序列分成两个长度为n/2的子序列，对两个子序列分别采用归并排序
2.将两个排序好的子序列合并成一个最终的排序序列
平均时间复杂度：O(nlogn)，空间复杂度：O(n), 稳定性：稳定
*/


void merge(vector<int> &inputNums, vector<int> &outputNums, int start, int mid, int end)
{
    int i = start, j = mid + 1, k = start;
    while (i <= mid && j <= end)
    {
        if (inputNums[i] <= inputNums[j])
            outputNums[k++] = inputNums[i++];
        else
            outputNums[k++] = inputNums[j++];
    }
    while (i <= mid)
        outputNums[k++] = inputNums[i++];
    while (j <= end)
        outputNums[k++] = inputNums[j++];

    // 把临时数组拷回原数组
    for (int t = start; t <= end; t++)
        inputNums[t] = outputNums[t];
}

void mergeSort(vector<int> &nums, vector<int> &nums_out, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        mergeSort(nums, nums_out, start, mid);
        mergeSort(nums, nums_out, mid + 1, end);
        merge(nums, nums_out, start, mid, end);
    }
}

int main()
{
    vector<int> nums = {38, 27, 43, 3, 9, 82, 10};
    vector<int> temp(nums.size()); // 临时数组

    mergeSort(nums, temp, 0, nums.size() - 1);

    cout << "排序结果: ";

    for(vector<int>::iterator it = nums.begin(); it != nums.end(); it++)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}