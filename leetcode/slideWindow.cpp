#include<deque>
#include<algorithm>
#include<vector>
#include<iostream>

using namespace std;
// 暴力解法超时
class Solution
{
public:
    int getDequeMax(const deque<int> &deq1)
    {
        deque<int>::const_iterator it = max_element(deq1.begin(), deq1.end());
        return *it;
    }

    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        deque<int> deq1;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums.size() == 0)
            {
                return result;
            }
            deq1.push_back(nums[i]);

            if (deq1.size() == k)
            {
                result.insert(result.begin() + i - 2, getDequeMax(deq1));
                deq1.pop_front();
            }
        }
        return result;
    }
};

// 单调队列
class Solution1
{
private:
    // 实现单调队列
    class MyDeque
    {
    public:
        deque<int> que;
        // 当需要弹出的元素和队列元素相等时，才会弹出元素
        void pop(int value)
        {
            if (!que.empty() && value == que.front())
            {
                que.pop_front();
            }
        }
        // 如果push的元素大于入口元素（back），则将入口元素弹出，
        // 直到push的数值小于等于back元素
        void push(int value)
        {
            while (!que.empty() && value > que.back())
            {
                que.pop_back();
            }
            que.push_back(value);
        }
        int front()
        {
            return que.front();
        }
    };

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        MyDeque que;
        vector<int> result;
        for (int i = 0; i < k; i++)
        {
            que.push(nums[i]);
        }
        for (int i = k; i < nums.size(); i++)
        {
            result.push_back(que.front());
            que.pop(nums[i - k]);
            que.push(nums[i]);
        }
        result.push_back(que.front());
        return result;
    }
};

int main()
{
    Solution1 s;
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> nums1 = {-7, -8, 7, 5, 7, 1, 6, 0};
    vector<int> result = s.maxSlidingWindow(nums1, 4);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
}