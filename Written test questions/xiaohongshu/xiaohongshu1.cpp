#include <iostream>
#include <vector>
#include <algorithm>

// 使用一个函数来处理每个测试用例，使代码更清晰
void solve()
{
    int n;
    long long d; // d 和数组元素的值可能较大，使用 long long
    std::cin >> n >> d;
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
    }

    // 步骤 1 & 2: 排序
    std::sort(a.begin(), a.end());

    if (n == 0)
    {
        std::cout << 0 << std::endl;
        return;
    }

    // 步骤 3: 贪心计算最大有效子集的大小 S_max
    int s_max = 1;
    long long last_kept = a[0];

    for (int i = 1; i < n; ++i)
    {
        if (a[i] > last_kept + d)
        {
            s_max++;
            last_kept = a[i];
        }
    }

    // 步骤 4: 结合奇偶性约束得出最终答案
    if ((n - s_max) % 2 == 0)
    {
        std::cout << s_max << std::endl;
    }
    else
    {
        std::cout << s_max - 1 << std::endl;
    }
}

int main()
{
    // 提高C++的I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
