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

// sort()
void test01()
{
    vector<int> v;
    v.push_back(2);
    v.push_back(3);
    v.push_back(1);
    v.push_back(0);

    printVector(v);
    sort(v.begin(), v.end(), greater());
    printVector(v);
}

// random shuffle
void test02()
{
    srand((unsigned int)time(NULL));

    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    
    random_shuffle(v.begin(), v.end());
    printVector(v);
}

// merge合并
void test03()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v_target;
    
    for (int i = 10; i > 0; i--)
    {
        v1.push_back(i);
        v2.push_back(i + 1);
    }

    v_target.resize(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin(), greater());
    for_each(v_target.begin(), v_target.end(), PrintVector());
}

// reverse
void test04()
{
    vector<int> v1;
    vector<int> v2;
    vector<int> v_target;
    
    for (int i = 10; i > 0; i--)
    {
        v1.push_back(i);
        v2.push_back(i + 1);
    }

    v_target.resize(v1.size() + v2.size());
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v_target.begin(), greater());
    for_each(v_target.begin(), v_target.end(), PrintVector());
    cout << endl;
    reverse(v_target.begin(), v_target.end());
    for_each(v_target.begin(), v_target.end(), PrintVector());
}

int main()
{
    test04();
}