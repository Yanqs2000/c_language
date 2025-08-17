#include <iostream>
#include <string>
#include <vector>

void solve()
{
    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    // 如果Plog数量小于等于1，不可能发生互评
    if (n <= 1)
    {
        std::cout << 0 << std::endl;
        return;
    }

    // 获取第一个Plog的属性
    char first_char_type = s[0];

    // 计算第一个连续块的长度
    int first_block_length = 0;
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == first_char_type)
        {
            first_block_length++;
        }
        else
        {
            // 遇到第一个不同的字符，第一个块结束
            break;
        }
    }

    // 总评价数 = 总Plog数 - 永远不会被移除的Plog数（即第一个块的长度）
    long long total_reviews = n - first_block_length;

    std::cout << total_reviews << std::endl;
}

int main()
{
    // 为了提高 cin/cout 的效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}
