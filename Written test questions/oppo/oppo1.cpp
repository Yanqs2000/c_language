#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;

    long long sum = 0;

    for (int i = 1; i <= n; ++i)
    {
        int a;
        cin >> a;

        if (i % 3 == 0)
        {
            sum += a;
        }
    }

    if (sum % 3 == 0)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    return 0;
}
