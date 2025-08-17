#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// 函数用于解决单个测试用例
void solve()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int max_val = 0;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
        if (a[i] > max_val)
        {
            max_val = a[i];
        }
    }

    long long max_reduction = 0;

    // O(N^2) 解法:
    // 外层循环固定区间的左端点 L_idx = s + 1
    // s 是区间 [L, R] 左边的最后一个元素的索引
    // s = -1 表示区间从数组开头 L_idx = 0 开始

    std::vector<int> counts_before(max_val + 2, 0);

    for (int s = -1; s < n; ++s)
    {
        // 1. 更新 counts_before
        // 当 s 从 s-1 增加到 s 时, a[s] 从 `interval` 区域移动到 `before` 区域
        if (s >= 0)
        {
            counts_before[a[s]]++;
        }

        // 对于固定的 s, 我们需要找到最优的 R_idx

        // 2. 初始化 counts_after 和 counts_interval
        // counts_after 存储 L_idx 之后所有元素的频率
        std::vector<int> counts_after(max_val + 2, 0);
        for (int i = s + 1; i < n; ++i)
        {
            counts_after[a[i]]++;
        }
        std::vector<int> counts_interval(max_val + 2, 0);

        long long current_gain = 0;
        long long current_loss = 0;

        // 3. 内层循环，从左到右扩展区间的右端点 R_idx
        for (int R_idx = s + 1; R_idx < n; ++R_idx)
        {
            int val = a[R_idx];

            // a[R_idx] 即将被移入 interval, 我们根据移动前的状态计算增益和损失的变化

            // 计算增益: a[R_idx] 与 before 区间的元素构成增益
            // 增益对数 = before 区间中值为 val+1 的元素个数
            if (val + 1 < counts_before.size())
            {
                current_gain += counts_before[val + 1];
            }

            // 计算损失变化:
            // 当 val = a[R_idx] 从 after 移入 interval
            // 损失的减少量: val 不再是 interval 中已有 val 元素的配对对象. 减少量为 counts_interval[val].
            // 损失的增加量: val 现在成为 interval 中的元素，需要和 after 中的 val 元素配对.
            //              它在 after 区域的同值伙伴有 counts_after[val] - 1 个.
            // 净损失变化 = (counts_after[val] - 1) - counts_interval[val]
            current_loss += (long long)(counts_after[val] - 1) - counts_interval[val];

            // 状态更新: 执行移动操作
            counts_after[val]--;
            counts_interval[val]++;

            // 更新最大减少量
            max_reduction = std::max(max_reduction, current_gain - current_loss);
        }
    }

    // 操作也可以不执行，此时减少量为 0
    std::cout << std::max(0LL, max_reduction) << std::endl;
}

int main()
{
    // 加速 C++ IO
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
