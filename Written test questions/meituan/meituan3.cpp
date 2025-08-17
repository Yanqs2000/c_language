#include <iostream>
#include <vector>

using namespace std;

// 定义长整型
typedef long long ll;

// 模数
const int M = 998244353;
// 预处理数组的最大大小，n 最大为 10^6
const int MAX_N = 1000000;

// 预处理的前缀和数组
// variance_sum[i] 存储 n=i 时的方差
vector<ll> variance_sum(MAX_N + 1, 0);

// 快速幂函数，用于计算 (base^exp) % mod
ll power(ll base, ll exp)
{
    ll res = 1;
    base %= M;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % M;
        base = (base * base) % M;
        exp /= 2;
    }
    return res;
}

// 模逆元函数，用于计算 a^(-1) mod M
ll modInverse(ll n)
{
    return power(n, M - 2);
}

// 预处理函数
void precompute()
{
    variance_sum[0] = 0;
    // 从 k=1 开始计算级数和
    // 注意 k=1 时，项为 (2*1-2)/(2*1-1)^2 = 0
    for (int k = 1; k <= MAX_N; ++k)
    {
        // 计算第 k 项: (2k-2) / (2k-1)^2
        ll term_num = (2LL * k - 2 + M) % M;
        if (term_num == 0)
        {
            // k=1 时分子为 0，该项为 0
            if (k > 0)
            {
                variance_sum[k] = variance_sum[k - 1];
            }
            continue;
        }

        ll term_den = 2LL * k - 1;
        ll inv_den = modInverse(term_den);
        ll inv_den_sq = (inv_den * inv_den) % M;

        ll term_k = (term_num * inv_den_sq) % M;

        // 更新前缀和数组
        if (k > 0)
        {
            variance_sum[k] = (variance_sum[k - 1] + term_k) % M;
        }
        else
        {
            variance_sum[k] = term_k;
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    // 从预计算的数组中直接获取结果
    cout << variance_sum[n] << endl;
}

int main()
{
    // 禁用 C++ 标准流与 C 标准流的同步，加快 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 执行预处理
    precompute();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}
