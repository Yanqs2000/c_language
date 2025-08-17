#include <iostream>
#include <vector>
#include <deque>

// C++标准库的输入输出较慢，对于大数据量，可以使用此函数加速
void fast_io()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
}

int main()
{
    fast_io();

    int n, m;
    std::cin >> n >> m;

    std::vector<int> scores(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> scores[i];
    }

    // 单调队列，存储的是数组的下标
    std::deque<int> max_dq; // 维护窗口最大值，队内元素对应值单调递减
    std::deque<int> min_dq; // 维护窗口最小值，队内元素对应值单调递增

    long long current_sum = 0;
    long long max_final_score = -1; // 因为分数非负，所以最终成绩也非负
    int best_start_index = -1;

    for (int i = 0; i < n; ++i)
    {
        // --- 1. 更新窗口内的元素 ---

        // a. 更新总和
        current_sum += scores[i];

        // b. 更新最大值队列：从队尾移除所有比当前元素小的元素
        while (!max_dq.empty() && scores[max_dq.back()] <= scores[i])
        {
            max_dq.pop_back();
        }
        max_dq.push_back(i);

        // c. 更新最小值队列：从队尾移除所有比当前元素大的元素
        while (!min_dq.empty() && scores[min_dq.back()] >= scores[i])
        {
            min_dq.pop_back();
        }
        min_dq.push_back(i);

        // --- 2. 当窗口形成后，进行计算和比较 ---
        if (i >= m - 1)
        {
            // a. 移除滑出窗口的旧元素
            // 检查队首元素是否已经不在当前窗口内 [i - m + 1, i]
            if (max_dq.front() <= i - m)
            {
                max_dq.pop_front();
            }
            if (min_dq.front() <= i - m)
            {
                min_dq.pop_front();
            }

            // b. 获取当前窗口的最大值和最小值
            int max_val = scores[max_dq.front()];
            int min_val = scores[min_dq.front()];

            // c. 计算最终成绩
            // (我们只比较分子部分 Sun - Max - Min 即可)
            long long current_final_score = current_sum - max_val - min_val;

            // d. 比较并更新最优解
            if (current_final_score > max_final_score)
            {
                max_final_score = current_final_score;
                // 当前窗口的起始下标是 i - m + 1 (0-based)
                // 题目要求1-based，所以是 i - m + 2
                best_start_index = (i - m + 1) + 1;
            }

            // e. 为下一次滑动做准备，减去将要滑出窗口的元素
            current_sum -= scores[i - m + 1];
        }
    }

    std::cout << best_start_index << std::endl;

    return 0;
}
