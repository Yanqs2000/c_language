#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<ctime>

using namespace std;

void printVector(vector<int> &v)
{
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << (*it) << " ";
    }
    cout << endl;
}

class PrintVector
{
public:
    void operator()(int val) const
    {
        cout << val << " ";
    }
};

class greater02
{
public:
    bool operator()(int val)
    {
        return val > 0;
    }
};

// copy
void test01()
{
    vector<int> v;
    vector<int> v1;
    v.push_back(2);
    v.push_back(3);
    v.push_back(1);
    v.push_back(0);
    v1.resize(v.size());
    printVector(v);
    sort(v.begin(), v.end(), greater());
    copy(v.begin(), v.end(), v1.begin());
    for_each(v1.begin(), v1.end(), PrintVector());
}

// replace替换
void test02()
{
    vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(1);
    v.push_back(0);
    printVector(v);
    replace(v.begin(), v.end(), 2, 20);
    printVector(v);
}

// replace_if符合条件的替换成指定元素
// swap互换
void test03()
{
    vector<int> v;
    vector<int> v1;
    v.push_back(2);
    v.push_back(3);
    v.push_back(1);
    v.push_back(0);
    printVector(v);
    v1.resize(v.size());
    copy(v.begin(), v.end(), v1.begin());
    replace_if(v1.begin(), v1.end(), greater02(), 20);
    printVector(v1);
    v1.swap(v);
    printVector(v1);
}
int main()
{
    test03();
}