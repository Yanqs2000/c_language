#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

void solve()
{
    // 使用 long long 防止整数溢出
    long long n, m;
    std::cin >> n >> m;

    std::string s;
    std::cin >> s;

    // 1. 统计初始字符串中每个字符的出现次数
    std::vector<long long> s_counts(26, 0);
    for (char c : s)
    {
        s_counts[c - 'a']++;
    }

    // 用于累加最终字符串中所有字符的总数
    long long total_final_count = 0;

    // g_{i-1} 的值，在循环中传递
    long long prev_g = 0;

    // 2. 循环计算每个字母的最终次数
    for (int i = 0; i < 26; ++i)
    {
        // b_i = s_i - i*m
        long long b_i = s_counts[i] - static_cast<long long>(i) * m;

        // g_i = max(b_i, g_{i-1})
        long long current_g;
        if (i == 0)
        {
            current_g = b_i;
        }
        else
        {
            current_g = std::max(b_i, prev_g);
        }

        // f_i = g_i + i*m
        long long f_i = current_g + static_cast<long long>(i) * m;

        // 累加到总数
        total_final_count += f_i;

        // 为下一次迭代更新 prev_g
        prev_g = current_g;
    }

    // 3. 计算需要添加的字符数
    long long added_chars = total_final_count - n;

    std::cout << added_chars << std::endl;
}

int main()
{
    // 加速 C++ I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}
