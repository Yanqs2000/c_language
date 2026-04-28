#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

// 函数用于解决单个测试用例
void solve()
{
    int n;
    std::cin >> n;

    // 使用 map 按点赞数 'a' 对 Plog 进行分组。
    // map 会自动按键（点赞数）排序。
    std::map<int, std::vector<int>> plogs_by_like;

    // 临时 vector 用于读取 'a' 值
    std::vector<int> a_values(n);
    for (int i = 0; i < n; ++i)
    {
        std::cin >> a_values[i];
    }
    // 读取 'c' 值并填充 map
    for (int i = 0; i < n; ++i)
    {
        int c;
        std::cin >> c;
        plogs_by_like[a_values[i]].push_back(c);
    }

    long long total_clutter = 0;

    // 遍历 map 以处理连续的点赞数块
    auto it = plogs_by_like.begin();
    while (it != plogs_by_like.end())
    {
        // 找到当前连续块的开始和结束
        auto block_start_it = it;
        auto block_end_it = it;
        auto next_it = std::next(it);
        while (next_it != plogs_by_like.end() && next_it->first == block_end_it->first + 1)
        {
            block_end_it = next_it;
            next_it++;
        }

        // it 更新为下一个块的起始点或 map 的末尾
        it = next_it;

        // 处理当前块
        // 'active_clutters' 存储每个活跃收藏夹的当前最大杂乱度
        std::vector<long long> active_clutters;

        for (auto current_it = block_start_it;; ++current_it)
        {
            // 获取当前点赞数对应的杂乱度列表
            std::vector<int> &current_c = current_it->second;
            // 按降序排序，方便选取最大/最小
            std::sort(current_c.rbegin(), current_c.rend());

            // 也将当前活跃杂乱度按降序排序
            std::sort(active_clutters.rbegin(), active_clutters.rend());

            std::vector<long long> next_active_clutters;
            int prev_count = active_clutters.size();
            int curr_count = current_c.size();

            if (curr_count > prev_count)
            {
                // 需要开启的新收藏夹数量
                int to_start = curr_count - prev_count;
                // 'prev_count' 个已有收藏夹继续
                // 将最大的活跃杂乱度与最大的新杂乱度配对
                for (int i = 0; i < prev_count; ++i)
                {
                    next_active_clutters.push_back(std::max((long long)current_c[i], active_clutters[i]));
                }
                // 新收藏夹使用剩余的最小杂乱度值
                for (int i = 0; i < to_start; ++i)
                {
                    next_active_clutters.push_back(current_c[prev_count + i]);
                }
            }
            else if (curr_count < prev_count)
            {
                // 需要终止的收藏夹数量
                int to_terminate = prev_count - curr_count;
                // 贪心策略：终止当前杂乱度最小的收藏夹
                for (int i = 0; i < to_terminate; ++i)
                {
                    total_clutter += active_clutters.back();
                    active_clutters.pop_back();
                }
                // 剩下的 'curr_count' 个杂乱度最高的收藏夹继续
                for (int i = 0; i < curr_count; ++i)
                {
                    next_active_clutters.push_back(std::max((long long)current_c[i], active_clutters[i]));
                }
            }
            else
            { // curr_count == prev_count
                // 所有收藏夹都继续
                for (int i = 0; i < curr_count; ++i)
                {
                    next_active_clutters.push_back(std::max((long long)current_c[i], active_clutters[i]));
                }
            }
            // 更新活跃杂乱度列表以进行下一步
            active_clutters = next_active_clutters;

            // 如果已处理完块中的最后一个点赞数，则退出循环
            if (current_it == block_end_it)
                break;
        }

        // 一个块结束时，所有剩余的活跃收藏夹都必须终止
        // 将它们的最终杂乱度计入总和
        for (long long clutter : active_clutters)
        {
            total_clutter += clutter;
        }
    }

    std::cout << total_clutter << std::endl;
}

int main()
{
    // 加速 I/O
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
