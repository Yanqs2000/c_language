#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// 定义一个结构体来存储专家的信息，包括其概率和原始编号
struct Expert
{
    double prob; // 概率
    int id;      // 原始编号
};

// 定义一个结构体来存储每个NPU组的信息，包括其内部的最大概率和组的编号
struct NpuGroup
{
    double max_prob; // 组内最大概率
    int group_id;    // 组的编号
};

// 主函数
int main()
{
    // 提高I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, p, k;
    std::cin >> n >> m >> p >> k;

    // --- 1. 错误条件检查 ---
    // 条件1: n 必须能被 m 整除
    // 条件2: 要求选择的 p 个NPU不能超过总共 m 个
    if (m == 0 || n % m != 0 || p > m)
    {
        std::cout << "error" << std::endl;
        return 0;
    }

    int group_size = n / m;

    // 条件3: 限定的 p 个 NPU 包含的专家总数必须足够选出 k 个
    if (static_cast<long long>(p) * group_size < k)
    {
        std::cout << "error" << std::endl;
        return 0;
    }

    // --- 2. 读取输入并分组处理 ---
    std::vector<Expert> all_experts(n);
    for (int i = 0; i < n; ++i)
    {
        all_experts[i].id = i;
        std::cin >> all_experts[i].prob;
    }

    std::vector<NpuGroup> groups;
    groups.reserve(m); // 预分配空间

    // --- 3. 找出每个组的最大概率作为代表 ---
    for (int i = 0; i < m; ++i)
    {
        int start_index = i * group_size;
        double current_max_prob = 0.0;
        // 在当前组内寻找最大概率
        for (int j = 0; j < group_size; ++j)
        {
            if (all_experts[start_index + j].prob > current_max_prob)
            {
                current_max_prob = all_experts[start_index + j].prob;
            }
        }
        groups.push_back({current_max_prob, i});
    }

    // --- 4. 选择概率代表值最大的 p 个 NPU 组 ---
    // 使用 lambda 表达式对组按最大概率降序排序
    std::sort(groups.begin(), groups.end(), [](const NpuGroup &a, const NpuGroup &b)
              { return a.max_prob > b.max_prob; });

    // --- 5. 从选定的 p 个组中收集所有专家 ---
    std::vector<Expert> candidate_experts;
    for (int i = 0; i < p; ++i)
    {
        int selected_group_id = groups[i].group_id;
        int start_index = selected_group_id * group_size;
        for (int j = 0; j < group_size; ++j)
        {
            candidate_experts.push_back(all_experts[start_index + j]);
        }
    }

    // --- 6. 从候选专家中选出概率最高的 k 个 ---
    // 对候选专家按概率降序排序
    // 更高效的方式是使用 std::partial_sort，但对于本题数据量，std::sort 足够快
    std::sort(candidate_experts.begin(), candidate_experts.end(), [](const Expert &a, const Expert &b)
              {
        if (a.prob != b.prob) {
             return a.prob > b.prob;
        }
        // 如果概率相同，可以按ID排序以保证稳定性（非必需，但为良好实践）
        return a.id < b.id; });

    // --- 7. 整理并输出最终结果 ---
    std::vector<int> final_expert_ids;
    final_expert_ids.reserve(k);
    for (int i = 0; i < k; ++i)
    {
        final_expert_ids.push_back(candidate_experts[i].id);
    }

    // 按题目要求，输出的编号需要从小到大排序
    std::sort(final_expert_ids.begin(), final_expert_ids.end());

    // 格式化输出
    for (int i = 0; i < final_expert_ids.size(); ++i)
    {
        std::cout << final_expert_ids[i] << (i == final_expert_ids.size() - 1 ? "" : " ");
    }
    std::cout << std::endl;

    return 0;
}
