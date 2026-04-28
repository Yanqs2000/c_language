#include <iostream>
#include <string>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    getline(cin, s);
    getline(cin, t);

    int m = t.size();
    string firstHalf = t.substr(0, m / 2);
    string secondHalf = t.substr(m / 2);

    cout << s + secondHalf << '\n';
    cout << firstHalf << '\n';

    return 0;
}