#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<int, int>> tasks(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tasks[i].first >> tasks[i].second; // time, difficulty
    }

    // 按 time 升序；若 time 相同，则 difficulty 降序
    sort(tasks.begin(), tasks.end(), [](const pair<int, int> &a, const pair<int, int> &b)
         {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second; });

    // 对 difficulty 求严格递增 LIS
    vector<int> dp;
    for (auto &task : tasks)
    {
        int d = task.second;
        auto it = lower_bound(dp.begin(), dp.end(), d);
        if (it == dp.end())
        {
            dp.push_back(d);
        }
        else
        {
            *it = d;
        }
    }

    cout << dp.size() << '\n';
    return 0;
}