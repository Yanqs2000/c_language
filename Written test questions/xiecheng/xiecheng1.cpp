#include <iostream>
using namespace std;

using ll = long long;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int n, q;
        cin >> n >> q;

        vector<ll> a(n + 1);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];

        vector<int> x(q);
        int mx = n;
        for (int i = 0; i < q; ++i)
        {
            cin >> x[i];
            mx = max(mx, x[i]);
        }

        // 需要的二进制位数
        int B = 0;
        while ((1 << B) <= mx)
            ++B;
        if (B == 0)
            B = 1;
        int LIM = 1 << B;

        // 三种做法的代价估计
        long long cost_bruteforce = 1LL * n * q;

        long long cost_subset_enum = 0;
        for (int v : x)
        {
            cost_subset_enum += (1LL << __builtin_popcount((unsigned)v));
            // 防止估价过大溢出，同时避免无意义继续加
            if (cost_subset_enum > (long long)4e18 / 2)
                break;
        }

        long long cost_sos = 1LL * B * LIM;

        // 选择代价最小的方法
        if (cost_bruteforce <= cost_subset_enum && cost_bruteforce <= cost_sos)
        {
            // 做法1：暴力
            for (int k = 0; k < q; ++k)
            {
                ll ans = 0;
                int v = x[k];
                for (int i = 1; i <= n; ++i)
                {
                    if ((v & i) == i)
                        ans += a[i];
                }
                cout << ans << '\n';
            }
        }
        else if (cost_subset_enum <= cost_sos)
        {
            // 做法2：枚举每个查询的所有子集
            for (int k = 0; k < q; ++k)
            {
                int v = x[k];
                ll ans = 0;

                for (int sub = v; sub; sub = (sub - 1) & v)
                {
                    if (sub <= n)
                        ans += a[sub];
                }

                // sub = 0 也会是子集，但题目下标从 1 开始，所以不用加 a[0]
                cout << ans << '\n';
            }
        }
        else
        {
            // 做法3：SOS DP
            vector<ll> f(LIM, 0);

            for (int i = 1; i <= n; ++i)
            {
                f[i] = a[i];
            }

            for (int b = 0; b < B; ++b)
            {
                for (int mask = 0; mask < LIM; ++mask)
                {
                    if (mask & (1 << b))
                    {
                        f[mask] += f[mask ^ (1 << b)];
                    }
                }
            }

            for (int k = 0; k < q; ++k)
            {
                cout << f[x[k]] << '\n';
            }
        }
    }

    return 0;
}