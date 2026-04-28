#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 使用一个很大的值表示无穷大，代表某个状态不可达
const long long INF = 1e18;

// 定义设施结构体，方便管理
struct Facility
{
    int a, b;
};

int main()
{
    // 提高 I/O 效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<Facility> facilities(n);
    int p_total = 0; // 所有正 a_i 的和
    int n_total = 0; // 所有负 a_i 绝对值的和

    for (int i = 0; i < n; ++i)
    {
        cin >> facilities[i].a >> facilities[i].b;
        if (facilities[i].a > 0)
        {
            p_total += facilities[i].a;
        }
        else if (facilities[i].a < 0)
        {
            n_total += -facilities[i].a;
        }
        // a_i = 0 的设施除了增加成本外没有用，可以忽略
    }

    // DP 数组的偏移量，使得负数索引可以映射到正数
    int offset = n_total;
    int dp_size = p_total + n_total + 1;
    vector<long long> dp(dp_size, INF);

    // 初始状态：净电力为0的总花费为0 (不建造任何东西)
    dp[offset] = 0;

    // 遍历每一个设施，更新DP数组
    for (const auto &fac : facilities)
    {
        int a = fac.a;
        int b = fac.b;

        if (a > 0)
        {
            // 对于发电设施 (a > 0)，从后往前遍历
            for (int p = dp_size - 1; p >= a; --p)
            {
                if (dp[p - a] != INF)
                {
                    dp[p] = min(dp[p], dp[p - a] + b);
                }
            }
        }
        else if (a < 0)
        {
            // 对于耗电设施 (a < 0)，从前往后遍历
            // 循环条件 p < dp_size + a 等价于 p <= dp_size - 1 + a，即 p <= dp_size - |a| - 1
            for (int p = 0; p < dp_size + a; ++p)
            {
                // p - a 等价于 p + |a|
                if (dp[p - a] != INF)
                {
                    dp[p] = min(dp[p], dp[p - a] + b);
                }
            }
        }
    }

    // 最终结果是净电力为1的状态
    long long result = dp[offset + 1];

    if (result == INF)
    {
        // 如果值仍为无穷大，说明无法凑成净电力1
        cout << -1 << endl;
    }
    else
    {
        cout << result << endl;
    }

    return 0;
}
