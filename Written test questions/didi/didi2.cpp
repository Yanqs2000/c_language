#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>

// 使用 long long 防止数值溢出
using ll = long long;

void solve()
{
    int n;
    ll m;
    std::cin >> n >> m;

    std::map<ll, ll> counts;
    ll total_sum = 0;
    for (int i = 0; i < n; ++i)
    {
        ll a;
        std::cin >> a;
        counts[a]++;
        total_sum += a;
    }

    while (m > 0 && counts.size() > 1)
    {
        auto it_min = counts.begin();
        auto it_max = std::prev(counts.end());

        ll min_val = it_min->first;
        ll min_count = it_min->second;
        ll max_val = it_max->first;
        ll max_count = it_max->second;

        if (max_val - min_val <= 1)
        {
            break;
        }

        ll ops_to_merge;

        // 如果只有两类箱子堆，无法合并到下一级
        if (counts.size() == 2)
        {
            // 将ops_to_merge设为一个比m大的数，触发下面的直接计算逻辑
            ops_to_merge = m + 1;
        }
        else
        {
            auto it_next_min = std::next(it_min);
            ll next_min_val = it_next_min->first;
            ll ops_to_raise_min = (next_min_val - min_val) * min_count;

            auto it_next_max = std::prev(it_max);
            ll next_max_val = it_next_max->first;
            ll ops_to_lower_max = (max_val - next_max_val) * max_count;

            ops_to_merge = std::min(ops_to_raise_min, ops_to_lower_max);
        }

        // 如果剩余操作不足以完成下一次合并，则直接计算最终状态
        if (m < ops_to_merge)
        {
            ll increase_per_min_pile = m / min_count;
            ll decrease_per_max_pile = m / max_count;

            ll final_min_val = min_val + increase_per_min_pile;
            ll final_max_val = max_val - decrease_per_max_pile;

            // 如果最小值赶上了最大值，说明已经平均化
            if (final_min_val >= final_max_val)
            {
                if (total_sum % n == 0)
                {
                    std::cout << 0 << std::endl;
                }
                else
                {
                    std::cout << 1 << std::endl;
                }
            }
            else
            {
                std::cout << final_max_val - final_min_val << std::endl;
            }
            return;
        }

        // 执行一次合并操作
        m -= ops_to_merge;

        // 判断是“填谷”还是“削峰”，或者两者同时发生
        ll next_min_val = std::next(it_min)->first;
        ll ops_to_raise_min = (next_min_val - min_val) * min_count;

        ll next_max_val = std::prev(it_max)->first;
        ll ops_to_lower_max = (max_val - next_max_val) * max_count;

        if (ops_to_raise_min <= ops_to_lower_max)
        {
            counts.erase(it_min);
            counts[next_min_val] += min_count;
        }

        if (ops_to_lower_max <= ops_to_raise_min)
        {
            counts.erase(it_max);
            counts[next_max_val] += max_count;
        }
    }

    // 循环结束后，如果map非空，则其中的差值就是答案
    if (counts.empty())
    {
        std::cout << 0 << std::endl;
    }
    else
    {
        std::cout << counts.rbegin()->first - counts.begin()->first << std::endl;
    }
}

int main()
{
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
