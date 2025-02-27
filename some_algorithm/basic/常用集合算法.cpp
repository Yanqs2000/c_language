#include<iostream>
#include<set>
#include<vector>
#include<algorithm>

using namespace std;

// 前提，必须是有序序列
// set_intersection求交集
// set_union求并集
// set_difference求差集
void test01()
{
    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 10; i++)
    {
        v1.push_back(i);
        v2.push_back(i * 2);
    }

    // 交集
    vector<int> v3;
    v3.resize(min(v1.size(), v2.size()));
    vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
    for (vector<int>::iterator it = v3.begin(); it != itEnd; it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    // 并集
    vector<int> v4;
    v4.resize(v1.size() + v2.size());
    vector<int>::iterator itEnd_2 = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin());
    for (vector<int>::iterator it = v4.begin(); it != itEnd_2; it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    // 差集
    vector<int> v5;
    vector<int> v6;
    v5.resize(max(v1.size(), v2.size()));
    v6.resize(max(v1.size(), v2.size()));

    vector<int>::iterator itEnd_3 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v5.begin());
    vector<int>::iterator itEnd_4 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v6.begin());
    for (vector<int>::iterator it = v5.begin(); it != itEnd_3; it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;

    for (vector<int>::iterator it = v6.begin(); it != itEnd_4; it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;
}

int main()
{
    test01();
}