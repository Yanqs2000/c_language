#include <iostream>
#include <vector>

using namespace std;
const void printVector(const vector<int> &vec)
{
    for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}   


class Solution{
public:
    int removeNum(vector<int> &nums, int target)
    {
        int slow = 0;
        for(int fast = 0; fast < nums.size(); fast++)
        {
            if(nums[fast] != target)
            {
                nums[slow++] = nums[fast];
            }
        }
        return slow;
    }
};


int main()
{
    Solution s;
    vector<int> nums = {0,1,2,2,3,0,4,2};
    int target = 2;
    int newLength = s.removeNum(nums, target);
    cout << "New length: " << newLength << endl;
    nums.resize(newLength); // 调整 vector 大小以反映新长度
    printVector(nums);
    return 0;
} 
