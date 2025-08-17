#include <iostream>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    int last_digit = n % 10;
    int first_digit = n;

    while (first_digit >= 10)
    {
        first_digit /= 10; 
    }

    if (first_digit == last_digit)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}
