#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

// 普通函数
void print01(int val)
{
    cout << val << endl;
}

// 仿函数，函数对象
class Print02
{
public:
    void operator()(int val)
    {
        cout << val << " ";
    }
};

// 常用遍历算法 for_each(begin，end,function)
void test01()
{
    vector<int> v;
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    for_each(v.begin(), v.end(), Print02());
}

// 仿函数，函数对象
class Trans
{
public:
    int operator()(int val)
    {
        return pow(val, 2);
    }
};


// 常用遍历算法,将容器搬到另一个容器中，transform(begin1, end1, begin2, function)
void test02()
{
    vector<int> v_origin;
    vector<int> v_target;

    for (int i = 0; i < 10; i++)
    {
        v_origin.push_back(i);
    }

    v_target.resize(v_origin.size());

    transform(v_origin.begin(), v_origin.end(), v_target.begin(), Trans());
    for_each(v_target.begin(), v_target.end(), Print02());
    
}
int main()
{
    test02();
    return 0;
}