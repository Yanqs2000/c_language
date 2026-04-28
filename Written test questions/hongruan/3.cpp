#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k, n;
    while (cin >> k >> n)
    {
        unordered_map<int, int> cnt;
        for (int i = 0; i < n; ++i)
        {
            int x;
            cin >> x;
            cnt[x]++;
        }

        int ans = -1;
        for (const auto &p : cnt)
        {
            if (p.second >= k && p.second > ans)
            {
                ans = p.second;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}