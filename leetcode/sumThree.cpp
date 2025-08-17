#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void printVector(vector<vector<int>> &nums)
{
    for (vector<vector<int>>::iterator it = nums.begin(); it != nums.end(); it++)
    {
        for(vector<int>::iterator iter = it->begin(); iter != it->end(); iter++)
        {
            cout << *iter << " ";
        }
        cout << endl;
    }
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if(nums[i] > 0)
            {
                return result;
            }
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            int left = i + 1;
            int right = nums.size() - 1;
            while(left < right)
            {
                if(nums[i] + nums[left] + nums[right] > 0) right--;
                else if(nums[i] + nums[left] + nums[right] < 0) left++;
                else
                {
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                    while(left < right && nums[right] == nums[right - 1])
                    {
                        right--;
                    }
                    while(left < right && nums[left] == nums[left + 1])
                    {
                        left++;
                    }
                    right--;
                    left++;
                }
            }
        }
        return result;
    }
};

int main()
{
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    Solution sol;
    vector<vector<int>> result = sol.threeSum(nums);
    printVector(result);
}