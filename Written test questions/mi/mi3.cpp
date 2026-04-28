#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// 检查是否可以通过不超过 k 次修改，使得最大相邻高度差 <= x
bool check(long long x, int n, int k, const vector<long long> &h)
{
    if (n <= 1)
    {
        return true;
    }

    // dp[i] 表示处理前 i 座山（0到i-1），并保留第 i 座山（h[i-1]）的高度不变，所需的最少修改次数。
    // 使用 1-based 索引 dp[1...n] 对应 0-based 数组 h[0...n-1]
    vector<int> dp(n + 1, 0);

    for (int i = 1; i <= n; ++i)
    {
        // 初始情况：修改第 i 座山之前的所有山（1 到 i-1），共 i-1 次修改
        dp[i] = i - 1;

        // 尝试从之前某个保留高度的山 j 转移过来
        for (int j = 1; j < i; ++j)
        {
            // h[i-1] 和 h[j-1] 是它们的实际高度
            // 检查从 h[j-1] 到 h[i-1] 是否可能，需要跨越 i-j 个间隔
            if (abs(h[i - 1] - h[j - 1]) <= (long long)(i - j) * x)
            {
                // 如果可能，则总修改次数为：
                // dp[j] (处理1到j的最小修改数) + (i - j - 1) (修改j和i之间的所有山)
                dp[i] = min(dp[i], dp[j] + (i - j - 1));
            }
        }
    }

    // 计算最终所需的最小操作数
    // 初始为 n，代表可以修改所有的山
    int min_ops = n;
    for (int i = 1; i <= n; ++i)
    {
        // 如果第 i 座山是最后一座不被修改的山，
        // 则总修改次数为 dp[i]（处理1到i）+ (n - i)（修改i之后的所有山）
        min_ops = min(min_ops, dp[i] + (n - i));
    }

    return min_ops <= k;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<long long> h(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> h[i];
    }

    if (n <= 1)
    {
        cout << 0 << endl;
        return;
    }

    // 二分查找答案
    long long low = 0, high = 1e9 + 7; // 耐久度的可能范围
    long long ans = high;

    while (low <= high)
    {
        long long mid = low + (high - low) / 2;
        if (check(mid, n, k, h))
        {
            // 如果 mid 可行，尝试更小的答案
            ans = mid;
            high = mid - 1;
        }
        else
        {
            // 如果 mid 不可行，需要更大的耐久度
            low = mid + 1;
        }
    }
    cout << ans << endl;
}

int main()
{
    // 加速输入输出
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}