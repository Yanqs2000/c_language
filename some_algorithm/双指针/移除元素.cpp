#include<iostream>
#include<vector>

using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++)
        {
            if (val != nums[fastIndex])
            {
                nums[slowIndex++] = nums[fastIndex];
            }
        }
        return slowIndex;
    }
};

int main()
{
    vector<int> num = {0, 1, 2, 2, 3, 0, 4, 2};
    int val = 2;
    Solution sol;
    cout << sol.removeElement(num, val) << endl;
    return 0;
}