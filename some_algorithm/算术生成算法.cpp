#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

using namespace std;

// accumulate计算总和
void test01()
{
    vector<int> v;
    for (int i = 0; i <= 100; i++)
    {
        v.push_back(i);
    }
    int result = accumulate(v.begin(), v.end(), 0);
    cout << result << endl;
}

// fill填充值
void test02()
{
    vector<int> v;
    for (int i = 0; i <= 100; i++)
    {
        v.push_back(i);
    }

    fill(v.begin(), v.end(), 1000);

    int result = accumulate(v.begin(), v.end(), 0);
    cout << result << endl;
}

int main()
{
    test02();
}