#include<iostream>
#include<vector>

using namespace std;

void genNext(int* next, const string& pattern)
{
    next[0] = 0;
    int j = 0; // 前缀末尾位置指针，也是最长相等前后缀的长度

    // 后缀末尾位置i从1开始，因为后缀不能包含首字母
    for (int i = 1; i < pattern.size(); i++)
    {
        // 前后缀不相同的情况
        // 连续回退是一个过程，直到找到一个相等的前后缀 
        while (pattern[i] != pattern[j] && j > 0)
        {
            j = next[j - 1];
        }

        if (pattern[i] == pattern[j])
        {
            j++; 
        }
        next[i] = j;
    }
}

int main()
{
    string text = "aabaabaaf";
    string pattern = "aabaaf";


}