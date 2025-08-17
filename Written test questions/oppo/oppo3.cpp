#include <iostream>
#include <vector>
#include <numeric>

void solve()
{
    int n, q;
    std::cin >> n >> q;

    std::vector<int> p(n + 1);
    p[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        int val;
        std::cin >> val;
        p[i] = (p[i - 1] + (val % 2)) % 2;
    }

    std::vector<long long> prefix_ones(n + 2, 0);
    for (int i = 0; i <= n; ++i)
    {
        prefix_ones[i + 1] = prefix_ones[i] + p[i];
    }

    for (int k = 0; k < q; ++k)
    {
        int l, r;
        std::cin >> l >> r;

        long long total_elements = (long long)r - (l - 1) + 1;
        long long odd_count = prefix_ones[r + 1] - prefix_ones[l - 1];
        long long even_count = total_elements - odd_count;
        long long result = odd_count * even_count;
        std::cout << result << "\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();

    return 0;
}
