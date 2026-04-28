#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    // 加速输入输出
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a[i];
    }

    // 如果数组只有一个元素，差值为0
    if (n == 1)
    {
        std::cout << 0 << std::endl;
        return 0;
    }

    // 情况一：不进行任何交换
    int max_diff = a[0] - a[n - 1];

    // 情况二：交换第一个和最后一个元素
    max_diff = std::max(max_diff, a[n - 1] - a[0]);

    // 对于 n > 2 的情况，考虑与中间元素交换
    if (n > 2)
    {
        // 找到中间部分 a[1]...a[n-2] 的最大值和最小值
        int min_middle = a[1];
        int max_middle = a[1];
        for (int i = 2; i < n - 1; ++i)
        {
            min_middle = std::min(min_middle, a[i]);
            max_middle = std::max(max_middle, a[i]);
        }

        // 情况三：将中间部分的最大值换到首位
        max_diff = std::max(max_diff, max_middle - a[n - 1]);

        // 情况四：将中间部分的最小值换到末尾
        max_diff = std::max(max_diff, a[0] - min_middle);
    }

    // 另外，我们也可以将数组中任意一个元素 a[i] 换到首位或末尾
    // 换言之，新的首元素可以是任意一个 a[i]，而尾元素不变 (或变为 a[0])
    // 新的尾元素可以是任意一个 a[i]，而首元素不变 (或变为 a[n-1])
    // 以下循环是一种更直接的暴力枚举思路，同样能得到正确结果

    // 尝试将任意元素 a[i] (i>0) 换到首位
    for (int i = 1; i < n; ++i)
    {
        // 交换 a[0] 和 a[i]
        int new_first = a[i];
        // 如果 i 是最后一个元素的索引，那么交换后 a[0] 会到末尾
        int new_last = (i == n - 1) ? a[0] : a[n - 1];
        max_diff = std::max(max_diff, new_first - new_last);
    }

    // 尝试将任意元素 a[i] (i<n-1) 换到末尾
    for (int i = 0; i < n - 1; ++i)
    {
        // 交换 a[n-1] 和 a[i]
        int new_last = a[i];
        // 如果 i 是第一个元素的索引，那么交换后 a[n-1] 会到首位
        int new_first = (i == 0) ? a[n - 1] : a[0];
        max_diff = std::max(max_diff, new_first - new_last);
    }

    std::cout << max_diff << std::endl;

    return 0;
}
