#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    vector<int> p(n);
    for (int i = 0; i < p.size(); ++i)
    {
        p[i] = i;
    }
    //iota(p.begin(), p.end(), 0);

    string ans = "";
    bool first = true;

    sort(p.begin(), p.end());

    do
    {
        string s = "";
        for (int i = 0; i < n; ++i)
        {
            s += a[p[i]];
        }

        for (int i = 0; i < (int)s.size(); ++i)
        {
            string t = s.substr(0, i) + s.substr(i + 1);
            if (first || t < ans)
            {
                ans = t;
                first = false;
            }
        }
    } while (next_permutation(p.begin(), p.end()));

    cout << ans << '\n';
    return 0;
}