#include <iostream>
#include <vector>


void func2()
{
    static int x = 0;
    x++;
    std::cout << "This is func2" << "x is " << x << std::endl;
}

class Solution
{
public:
    static int count;
    static void func()
    {
        std::cout << "Count: " << count << std::endl;
    }
    Solution() {
        count++;
    }
};
int Solution::count = 0;
int main()
{
    Solution s1;
    Solution s2;
    Solution::func(); // 输出 Count: 2
    func2(); // 输出 This is func2 x is 1
    func2(); // 输出 This is func2 x is 2

    return 0;
}