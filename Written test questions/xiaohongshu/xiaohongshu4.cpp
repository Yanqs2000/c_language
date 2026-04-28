#include <iostream> // 引入输入输出流库

// 函数用于判断一个整数n是否为“好数”
// 返回true表示是好数，false表示不是好数
bool isGoodNumber(int n)
{
    // 特殊情况：n = 1。根据定义，1没有质因子，其质因子之和为0（偶数），所以1不是好数。
    if (n == 1)
    {
        return false;
    }

    // 计数器，记录本质不同奇质因子的数量
    int count_distinct_odd_prime_factors = 0;

    // 步骤1: 处理质因子2
    // 如果n是偶数，说明2是它的一个本质不同质因子。
    // 但是2是偶数，不会影响所有质因子和的奇偶性，所以我们不需要将它加入到“奇质因子”的计数中。
    // 我们只是将n中所有的因子2都除掉，以便后续只处理奇数因子。
    if (n % 2 == 0)
    {
        while (n % 2 == 0)
        {
            n /= 2;
        }
    }

    // 步骤2: 处理奇质因子
    // 从3开始，只检查奇数（步长为2），直到i*i大于n。
    // i*i <= n 这种写法比 i <= sqrt(n) 更优，可以避免浮点数运算和精度问题。
    for (int i = 3; i * i <= n; i += 2)
    {
        // 如果i能整除n，说明i是n的一个本质不同质因子（且是奇数）
        if (n % i == 0)
        {
            count_distinct_odd_prime_factors++; // 找到一个奇质因子，计数器加1
            // 循环将n中所有i的倍数都除掉，确保i只被统计一次（本质不同质因子）
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }

    // 步骤3: 处理剩余的n
    // 经过上述循环，如果n最终仍然大于1，说明剩下的n本身是一个质数。
    // 因为所有因子2已经被处理，所以这个剩余的质数必定是奇数。
    if (n > 1)
    {
        count_distinct_odd_prime_factors++; // 将这个最后的奇质数也计入
    }

    // 判断最终结果：如果本质不同奇质因子的数量是奇数，则原数是好数，否则不是。
    return (count_distinct_odd_prime_factors % 2 == 1);
}

int main()
{
    // 优化C++标准流的输入输出，提高程序运行效率
    // std::ios_base::sync_with_stdio(false) 取消C++流与C标准流的同步
    // std::cin.tie(NULL) 解除cin和cout的绑定，cin不再等待cout flush
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;         // 测试用例的数量
    std::cin >> T; // 读取测试用例数量

    // 循环处理每个测试用例
    while (T--)
    {
        int n;         // 待判断的整数
        std::cin >> n; // 读取整数n
        if (isGoodNumber(n))
        {
            std::cout << "YES\n"; // 如果是好数，输出YES
        }
        else
        {
            std::cout << "NO\n"; // 如果不是好数，输出NO
        }
    }

    return 0; // 程序正常退出
}
