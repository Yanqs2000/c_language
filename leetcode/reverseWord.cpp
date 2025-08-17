#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
// 采用快慢指针的方法
class Solution
{
public:
    // 去除多余空格，并且在每个单词之间添加一个空格
    // fast指针是读指针，负责读出数据，slow指针是写指针
    // 多多注意边界条件
    void extraWords(string &s)
    {
        int slow = 0;
        for (int fast = 0; fast < s.size(); fast++)
        {
            if (s[fast] != ' ')
            {
                if (slow != 0)
                {
                    s[slow] = ' ';
                    slow++;
                }

                while (fast < s.size() && s[fast] != ' ')
                {
                    s[slow] = s[fast];
                    slow++;
                    fast++;
                }
            }
        }
        s.resize(slow);
    }
    // 采用左闭右闭的方式
    void reverseWord(string &s, int start, int end)
    {
        for (int i = 0; i < (end - start) / 2 + 1; i++)
        {
            swap(s[start + i], s[end - i]);
        }
    }

    string reverseWords(string s)
    {
        extraWords(s);
        reverseWord(s, 0, s.size() - 1);

        int start = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                reverseWord(s, start, i - 1);
                start = i + 1;
            }
            else if (i == s.size() - 1)
            {
                reverseWord(s, start, i);
            }
        }
        return s;
    }
};

int main()
{
    string s = " the  sky is blue";
    Solution sol;
    cout << sol.reverseWords(s) << endl;
}