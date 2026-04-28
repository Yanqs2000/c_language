#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int findLeft(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return left;
    }

    int findRight(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] <= target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return left - 1;
    }

    vector<int> searchRange(vector<int> &nums, int target)
    {
        vector<int> location(2, -1);
        int leftBound = findLeft(nums, target);
        int rightBound = findRight(nums, target);

        // 判断 target 是否真的存在
        if (!(leftBound >= nums.size() || nums[leftBound] != target))
        {
            location[0] = leftBound;
            location[1] = rightBound;
        }
        return location;
    }
};

int main()
{
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;
    Solution solution;
    vector<int> location = solution.searchRange(nums, target);
    cout << "Target " << target << " is located at: [" << location[0] << ", " << location[1] << "]" << endl;
    return 0;
}
