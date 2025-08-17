#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

// 使用 long long 以免在求和过程中发生溢出
using ll = long long;

// 定义一个很大的数来模拟负无穷
const ll INF = 2e18; // 2*10^18, 足够大

// 全局变量K
ll K;

// 解决问题的核心分治函数
ll solve(int l_bound, int r_bound, const std::vector<ll> &S)
{
    // 递归基：区间无效
    if (l_bound > r_bound)
    {
        return 0;
    }
    // 递归基：区间只包含一个元素 [i, i]
    // 此时峰值为 a[i] = S[i] - S[i-1]
    if (l_bound == r_bound)
    {
        return (S[l_bound] - S[l_bound - 1] == K) ? 1 : 0;
    }

    // 分（Divide）
    int mid = l_bound + (r_bound - l_bound) / 2;
    ll count = solve(l_bound, mid, S) + solve(mid + 1, r_bound, S);

    // 治（Conquer）：处理跨越中点的区间 [i, j] (l_bound <= i <= mid < j <= r_bound)

    // --- Part 1: 峰值在左半部分 [i, mid] ---

    // 预计算右半部分 [mid+1, r_bound] 的前缀最大值
    std::vector<ll> right_peaks;
    ll max_r = -INF;
    for (int j = mid + 1; j <= r_bound; ++j)
    {
        max_r = std::max(max_r, S[j]);
        right_peaks.push_back(max_r);
    }

    // 从 mid 遍历到 l_bound，计算左侧峰值
    ll max_l = -INF;
    for (int i = mid; i >= l_bound; --i)
    {
        max_l = std::max(max_l, S[i]);
        // 如果左侧峰值满足条件
        if (max_l - S[i - 1] == K)
        {
            // 在 right_peaks 中查找有多少个峰值 <= max_l
            // std::upper_bound 返回第一个大于 max_l 的元素的迭代器
            auto it = std::upper_bound(right_peaks.begin(), right_peaks.end(), max_l);
            count += (it - right_peaks.begin());
        }
    }

    // --- Part 2: 峰值在右半部分 (mid, j] ---

    // 预计算左半部分 [l_bound, mid] 的前缀最大值
    std::vector<ll> left_peaks;
    max_l = -INF;
    for (int i = l_bound; i <= mid; ++i)
    {
        max_l = std::max(max_l, S[i]);
        left_peaks.push_back(max_l);
    }

    // 使用双指针和频率表
    std::map<ll, int> s_counts;
    int i_ptr = l_bound; // 左指针
    max_r = -INF;
    // 遍历所有可能的右端点 j
    for (int j = mid + 1; j <= r_bound; ++j)
    {
        max_r = std::max(max_r, S[j]);

        // 移动左指针，将所有满足 left_peak < max_r 的 S[i-1] 加入频率表
        while (i_ptr <= mid && left_peaks[i_ptr - l_bound] < max_r)
        {
            s_counts[S[i_ptr - 1]]++;
            i_ptr++;
        }

        // 此时，对于当前 j，峰值是 max_r
        // 激活条件为 max_r - S[i-1] == K，即 S[i-1] == max_r - K
        // 在频率表中查找满足条件的 S[i-1] 的数量
        if (s_counts.count(max_r - K))
        {
            count += s_counts.at(max_r - K);
        }
    }

    return count;
}

int main()
{
    // 提高C++ I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n >> K;

    // 使用1-based索引，方便与前缀和公式 S[i] - S[l-1] 对齐
    std::vector<ll> S(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        ll a_i;
        std::cin >> a_i;
        S[i] = S[i - 1] + a_i;
    }

    // 调用分治函数解决问题
    std::cout << solve(1, n, S) << std::endl;

    return 0;
}
