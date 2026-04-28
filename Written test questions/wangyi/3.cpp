#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    double x;
    cin >> x;
    double left = 0, right = x >= 1 ? x : 1;
    double mid;

    for (int i = 0; i < 100; i++)
    {
        mid = (left + right) / 2;
        if (mid * mid > x)
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }

    cout << fixed << setprecision(2) << left << endl;
    return 0;
}