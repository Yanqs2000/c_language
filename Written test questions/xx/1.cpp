#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

static const double EPS = 1e-12;

struct Point
{
    double x, y;
};

int n, kneed;
vector<Point> pts;

// 检查在一条轴上形成的区间，是否存在一个位置被至少 kneed 个区间覆盖
bool maxOverlapAtLeastK(vector<pair<double, int>> &events)
{
    sort(events.begin(), events.end(), [](const auto &a, const auto &b)
         {
             if (fabs(a.first - b.first) > EPS)
                 return a.first < b.first;
             return a.second > b.second; // 左端点(+1)先于右端点(-1)，保证闭区间端点重合时计入
         });

    int cur = 0;
    for (auto &e : events)
    {
        cur += e.second;
        if (cur >= kneed)
            return true;
    }
    return false;
}

// 检查半径 r 是否可行
bool check(double r)
{
    // 圆心在 x 轴上
    {
        vector<pair<double, int>> events;
        events.reserve(2 * n);

        for (const auto &p : pts)
        {
            if (fabs(p.y) > r + EPS)
                continue;
            double dx = sqrt(max(0.0, r * r - p.y * p.y));
            double L = p.x - dx;
            double R = p.x + dx;
            events.push_back({L, +1});
            events.push_back({R, -1});
        }

        if (!events.empty() && maxOverlapAtLeastK(events))
            return true;
    }

    // 圆心在 y 轴上
    {
        vector<pair<double, int>> events;
        events.reserve(2 * n);

        for (const auto &p : pts)
        {
            if (fabs(p.x) > r + EPS)
                continue;
            double dy = sqrt(max(0.0, r * r - p.x * p.x));
            double L = p.y - dy;
            double R = p.y + dy;
            events.push_back({L, +1});
            events.push_back({R, -1});
        }

        if (!events.empty() && maxOverlapAtLeastK(events))
            return true;
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    pts.resize(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> pts[i].x >> pts[i].y;
    }

    // 至少覆盖 ceil(n/2) 个点
    kneed = (n + 1) / 2;

    double left = 0.0, right = 300000.0; // 足够大的上界

    for (int it = 0; it < 70; ++it)
    { // 70 次足够达到 1e-6 精度要求
        double mid = (left + right) / 2.0;
        if (check(mid))
            right = mid;
        else
            left = mid;
    }

    cout << fixed << setprecision(10) << right << '\n';
    return 0;
}