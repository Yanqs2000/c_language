#include <iostream>
#include <vector>
#include <queue>     // 包含 priority_queue
#include <algorithm> // 包含 std::sort, std::reverse, std::copy

/**
 * 使用小顶堆查找数据集中最大的TopN个元素。
 *
 * @param data 输入的数据vector。
 * @param n    要查找的最大的元素数量。
 * @return 包含TopN个最大元素的vector，按降序排列。
 */
std::vector<int> findTopNLargest(const std::vector<int> &data, int n)
{
    // --- 1. 参数验证 ---
    if (data.empty() || n <= 0)
    {
        std::cout << "----------------------------------------------\n";
        std::cout << "错误：输入数据为空或N值无效 (N 必须大于 0)。\n";
        return {}; // 返回空vector
    }

    // 如果N大于数据总数，则返回所有数据（已排序）
    if (n >= data.size())
    {
        std::cout << "----------------------------------------------\n";
        std::cout << "N (" << n << ") 大于或等于数据总数 (" << data.size() << ")，返回所有数据并排序。\n";
        std::vector<int> allData = data;
        std::sort(allData.begin(), allData.end(), std::greater<int>()); // 降序排序
        return allData;
    }

    std::cout << "----------------------------------------------\n";
    std::cout << "开始查找数组 [";
    for (size_t i = 0; i < data.size(); ++i)
    {
        std::cout << data[i] << (i == data.size() - 1 ? "" : ", ");
    }
    std::cout << "] 中最大的 " << n << " 个元素。\n";

    // --- 2. 初始化小顶堆 ---
    // std::priority_queue<Type, Container, Compare>
    // 默认是 std::less<Type> (大顶堆)，所以要改为 std::greater<Type> (小顶堆)
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;

    // --- 3. 遍历数据 ---
    for (size_t i = 0; i < data.size(); ++i)
    {
        int currentNum = data[i];
        std::cout << "\n--- 处理元素 " << currentNum << " (" << i + 1 << "/" << data.size() << ") ---\n";

        // 如果堆未满（即堆中元素数量小于N）
        if (minHeap.size() < n)
        {
            minHeap.push(currentNum); // 直接加入堆
            std::cout << "  堆未满，直接加入 " << currentNum << "。当前堆大小: " << minHeap.size() << "\n";
            // C++ 的 priority_queue 没有直接打印内部元素的便捷方法，下面的打印是模拟
            // printHeap(minHeap); // 实际操作时，不能直接打印内部顺序
        }
        else
        {
            // 如果堆已满（即堆中元素数量等于N）
            // 比较当前元素与堆顶元素（小顶堆的最小值）
            int heapTop = minHeap.top(); // 获取堆顶元素（不移除）
            std::cout << "  堆已满 (大小: " << minHeap.size() << ")，堆顶元素是 " << heapTop << "。\n";

            if (currentNum > heapTop)
            {
                // 如果当前元素比堆顶元素大，说明当前元素有资格成为TopN之一
                minHeap.pop();            // 移除堆顶
                minHeap.push(currentNum); // 加入当前元素
                std::cout << "  " << currentNum << " > " << heapTop << " (堆顶)，移除堆顶元素 " << heapTop
                          << "，并加入 " << currentNum << "。\n";
                // std::cout << "  堆更新后: "; printHeap(minHeap); // 实际操作时，不能直接打印内部顺序
            }
            else
            {
                // 如果当前元素不比堆顶元素大（小于或等于），则忽略它
                std::cout << "  " << currentNum << " <= " << heapTop << " (堆顶)，忽略当前元素 " << currentNum
                          << "。堆保持不变。\n";
            }
        }
    }

    // --- 4. 遍历结束后，堆中就是最大的N个元素 ---
    std::cout << "\n----------------------------------------------\n";
    std::cout << "所有元素处理完毕。小顶堆中最终的元素。\n";

    // 将堆中的元素取出放入vector列表中
    std::vector<int> result;
    while (!minHeap.empty())
    {
        result.push_back(minHeap.top()); // top() 获取堆顶元素
        minHeap.pop();                   // pop() 移除堆顶元素
    }

    // 因为是从小到大取出的，如果需要按从大到小显示，需要反转vector
    std::reverse(result.begin(), result.end());

    return result;
}

// 辅助函数，用于打印vector
void printVector(const std::vector<int> &vec)
{
    std::cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << (i == vec.size() - 1 ? "" : ", ");
    }
    std::cout << "]";
}

int main()
{
    // 示例数据
    std::vector<int> data1 = {3, 2, 8, 5, 1, 9, 4, 7, 6, 10, 0, 15, 12, 11};
    int n1 = 3;
    std::vector<int> topN1 = findTopNLargest(data1, n1);
    std::cout << "最终结果：数组 ";
    printVector(data1);
    std::cout << " 中最大的 " << n1 << " 个元素是: ";
    printVector(topN1);
    std::cout << "\n\n";

    std::vector<int> data2 = {10, 20, 5, 15, 25, 30};
    int n2 = 2;
    std::vector<int> topN2 = findTopNLargest(data2, n2);
    std::cout << "最终结果：数组 ";
    printVector(data2);
    std::cout << " 中最大的 " << n2 << " 个元素是: ";
    printVector(topN2);
    std::cout << "\n\n";

    std::vector<int> data3 = {1, 2, 3, 4, 5};
    int n3 = 5; // N等于数据长度
    std::vector<int> topN3 = findTopNLargest(data3, n3);
    std::cout << "最终结果：数组 ";
    printVector(data3);
    std::cout << " 中最大的 " << n3 << " 个元素是: ";
    printVector(topN3);
    std::cout << "\n\n";

    std::vector<int> data4 = {1, 2, 3};
    int n4 = 10; // N大于数据长度
    std::vector<int> topN4 = findTopNLargest(data4, n4);
    std::cout << "最终结果：数组 ";
    printVector(data4);
    std::cout << " 中最大的 " << n4 << " 个元素是: ";
    printVector(topN4);
    std::cout << "\n\n";

    std::vector<int> data5 = {}; // 空数据
    int n5 = 3;
    std::vector<int> topN5 = findTopNLargest(data5, n5);
    std::cout << "最终结果：数组 ";
    printVector(data5);
    std::cout << " 中最大的 " << n5 << " 个元素是: ";
    printVector(topN5);
    std::cout << "\n\n";

    std::vector<int> data6 = {100, 50, 200}; // N=1
    int n6 = 1;
    std::vector<int> topN6 = findTopNLargest(data6, n6);
    std::cout << "最终结果：数组 ";
    printVector(data6);
    std::cout << " 中最大的 " << n6 << " 个元素是: ";
    printVector(topN6);
    std::cout << "\n\n";

    return 0;
}
