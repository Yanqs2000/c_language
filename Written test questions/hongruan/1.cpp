#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    int k, n;
    cin >> k >> n;

    unordered_map<int, int> freq;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        freq[x]++;
    }

    int ans = -1;
    for (const auto &p : freq)
    {
        if (p.second >= k)
        {
            ans = max(ans, p.second);
        }
    }

    cout << ans << endl;
    return 0;
}