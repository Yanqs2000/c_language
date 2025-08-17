#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;

    bool seen[26] = {false};

    for (char c : s)
    {
        seen[c - 'A'] = true;
    }

    int ascii_sum = 0;
    for (int i = 0; i < 26; ++i)
    {
        if (!seen[i])
        {
            ascii_sum += ('A' + i);
        }
    }
    std::cout << ascii_sum << std::endl;
    return 0;
}
