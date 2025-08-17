#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 使用 long long 来存储经验值，因为 a[i] 很大，n 也很大，总经验值可能超过 int 范围
using ll = long long;

const ll INF = -1e18; // 使用一个足够小的负数表示不可达状态

int main()
{
    // 提高cin/cout效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    // dp[k] 表示当前考虑完的怪物后，击败数量模10余k的最大经验值
    // 使用滚动数组思想，dp 表示 dp[i], prev_dp 表示 dp[i-1]
    vector<ll> dp(10, INF);
    vector<ll> prev_dp(10, INF);

    // 初始化：dp[0][0] = 0
    // 对应到滚动数组，即在循环开始前，prev_dp[0] = 0
    prev_dp[0] = 0;

    // 遍历每个怪物 i (从1到n)
    for (int i = 1; i <= n; ++i)
    {
        // 遍历所有可能的余数 k (从0到9)
        for (int k = 0; k < 10; ++k)
        {
            // 决策1: 放走第 i 个怪物
            // 状态从 prev_dp[k] 转移，击败数余数不变
            ll choice_release = prev_dp[k] + i;

            // 决策2: 击败第 i 个怪物
            // 状态从 prev_dp[prev_k] 转移，其中 prev_k 是击败前余数
            int prev_k = (k - 1 + 10) % 10;
            ll choice_attack = prev_dp[prev_k] + a[i - 1] + (ll)k * a[i - 1];

            // 当前状态 dp[i][k] 的最优解
            dp[k] = max(choice_release, choice_attack);
        }
        // 更新 prev_dp 以供下一次迭代使用
        prev_dp = dp;
    }

    // 最终结果是所有 dp[n][k] 中的最大值
    ll max_exp = 0;
    for (int k = 0; k < 10; ++k)
    {
        max_exp = max(max_exp, dp[k]);
    }

    cout << max_exp << endl;

    return 0;
}
