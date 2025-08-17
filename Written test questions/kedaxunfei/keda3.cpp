#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <algorithm>
#include <cmath>

// 全局素数列表，用于快速分解质因数
std::vector<int> primes;
// 筛法上限, sqrt(10^9) 约 31622，取 32000
const int SIEVE_LIMIT = 32000;

// 埃氏筛法，预计算 SIEVE_LIMIT 内的素数
void sieve()
{
    // 避免重复执行筛法
    if (!primes.empty())
        return;
    std::vector<bool> is_prime(SIEVE_LIMIT + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int p = 2; p * p <= SIEVE_LIMIT; ++p)
    {
        if (is_prime[p])
        {
            for (int i = p * p; i <= SIEVE_LIMIT; i += p)
                is_prime[i] = false;
        }
    }
    for (int p = 2; p <= SIEVE_LIMIT; ++p)
    {
        if (is_prime[p])
        {
            primes.push_back(p);
        }
    }
}

// 快速分解质因数函数
void factorize(long long n, std::map<long long, int> &factors)
{
    factors.clear();
    for (int p : primes)
    {
        // 优化：当 p^2 > n 时，n最多只有一个大于p的质因子
        if ((long long)p * p > n)
            break;
        if (n % p == 0)
        {
            int count = 0;
            while (n % p == 0)
            {
                n /= p;
                count++;
            }
            factors[p] = count;
        }
    }
    // 如果 n 还有剩余，那么它本身是一个质数
    if (n > 1)
    {
        factors[n] = 1;
    }
}

void solve()
{
    int n;
    std::cin >> n;
    std::vector<std::map<long long, int>> a_factors(n);
    std::map<long long, int> total_lcm_factors;

    // 步骤 1: 读入、分解质因数，并计算整个数组LCM所需的质因子及其最高次幂
    for (int i = 0; i < n; ++i)
    {
        long long val;
        std::cin >> val;
        factorize(val, a_factors[i]);
        for (auto const &[p, k] : a_factors[i])
        {
            if (total_lcm_factors.find(p) == total_lcm_factors.end() || k > total_lcm_factors[p])
            {
                total_lcm_factors[p] = k;
            }
        }
    }

    // 特殊情况：如果所有数都是1，LCM是1，任何单个元素[1]都是最短的有效子数组
    if (total_lcm_factors.empty())
    {
        std::cout << 1 << "\n";
        return;
    }

    // 步骤 2: 预处理，找出每个元素能满足哪些LCM的质因子要求
    int total_reqs = total_lcm_factors.size();
    std::vector<std::vector<long long>> satisfies(n);
    for (int i = 0; i < n; ++i)
    {
        for (auto const &[p, k] : a_factors[i])
        {
            // total_lcm_factors.at(p) 比 total_lcm_factors[p] 稍快且在不存在时会报错，这里逻辑上p必存在
            if (k >= total_lcm_factors.at(p))
            {
                satisfies[i].push_back(p);
            }
        }
    }

    // 步骤 3: 滑动窗口寻找最短子数组
    std::map<long long, int> req_counts; // 窗口内满足各个质因子要求的元素个数
    int satisfied_count = 0;             // 已满足的要求种类数
    int min_len = n + 1;
    int l = 0;

    for (int r = 0; r < n; ++r)
    {
        // 将右端点 r 的元素加入窗口
        for (long long p : satisfies[r])
        {
            if (req_counts[p] == 0)
            {
                satisfied_count++;
            }
            req_counts[p]++;
        }

        // 当窗口满足所有要求时，尝试收缩左边界
        while (satisfied_count == total_reqs)
        {
            min_len = std::min(min_len, r - l + 1);

            // 将左端点 l 的元素移出窗口
            for (long long p : satisfies[l])
            {
                req_counts[p]--;
                if (req_counts[p] == 0)
                {
                    satisfied_count--;
                }
            }
            l++;
        }
    }

    std::cout << min_len << "\n";
}

int main()
{
    // 提高C++ I/O效率
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // 全局只执行一次筛法
    sieve();

    int t;
    std::cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
