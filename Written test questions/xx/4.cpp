#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int N = 100000 + 5;
const double EPS = 1e-12;

int n;
pair<double, double> p[N];

bool check_axis(double r, bool on_x_axis, int need)
{
    vector<double> L, R;
    L.reserve(n);
    R.reserve(n);

    for (int i = 0; i < n; ++i)
    {
        double x = p[i].first;
        double y = p[i].second;

        // d: 点到对应坐标轴的距离
        // center: 该点在坐标轴方向上的投影坐标
        double d = on_x_axis ? fabs(y) : fabs(x);
        double center = on_x_axis ? x : y;

        if (d > r + EPS)
            continue;

        double len = sqrt(max(0.0, r * r - d * d));
        L.push_back(center - len);
        R.push_back(center + len);
    }

    int m = (int)L.size();
    if (m < need)
        return false;

    sort(L.begin(), L.end());
    sort(R.begin(), R.end());

    int j = 0;
    int mx = 0;

    for (int i = 0; i < m; ++i)
    {
        // 闭区间 [L, R]：只有 R < 当前点 时，才算彻底离开
        while (j < m && R[j] < L[i] - EPS)
            ++j;
        mx = max(mx, i - j + 1);
    }

    return mx >= need;
}

bool check(double r, int need)
{
    return check_axis(r, true, need) || check_axis(r, false, need);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> p[i].first >> p[i].second;
    }

    // 题面写的是 [n/2]，通常按向下取整
    int need = n / 2;

    // 如果你提交的平台样例/数据明显要求“至少一半向上取整”，改成这行：
    // int need = (n + 1) / 2;

    if (need == 0)
    {
        cout << fixed << setprecision(10) << 0.0 << '\n';
        return 0;
    }

    double l = 0.0, r = 300000.0;
    // 坐标范围 1e5，最大两点距离不会超过约 2.83e5，300000 足够

    for (int it = 0; it < 70; ++it)
    {
        double mid = (l + r) / 2.0;
        if (check(mid, need))
            r = mid;
        else
            l = mid;
    }

    cout << fixed << setprecision(10) << r << '\n';
    return 0;
}