#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 为了避免潜在的整数溢出，使用 long long 存储高度
using ll = long long;

const int MAXN = 100005;

// 线段树节点
struct Node
{
    ll max_val;
    ll lazy_tag; // 懒惰标记，0表示没有标记
};

Node tree[MAXN * 4];
vector<ll> initial_heights;

// push_up: 用子节点的信息更新父节点
void push_up(int node_idx)
{
    tree[node_idx].max_val = max(tree[node_idx * 2].max_val, tree[node_idx * 2 + 1].max_val);
}

// push_down: 将父节点的懒惰标记下传给子节点
void push_down(int node_idx)
{
    if (tree[node_idx].lazy_tag != 0)
    {
        ll tag = tree[node_idx].lazy_tag;
        // 更新左子节点
        tree[node_idx * 2].max_val = tag;
        tree[node_idx * 2].lazy_tag = tag;
        // 更新右子节点
        tree[node_idx * 2 + 1].max_val = tag;
        tree[node_idx * 2 + 1].lazy_tag = tag;
        // 清除父节点的懒惰标记
        tree[node_idx].lazy_tag = 0;
    }
}

// build: 构建线段树
// node_idx: 当前节点在线段树数组中的索引
// l, r: 当前节点所代表的区间 [l, r]
void build(int node_idx, int l, int r)
{
    tree[node_idx].lazy_tag = 0;
    if (l == r)
    {
        tree[node_idx].max_val = initial_heights[l];
        return;
    }
    int mid = l + (r - l) / 2;
    build(node_idx * 2, l, mid);
    build(node_idx * 2 + 1, mid + 1, r);
    push_up(node_idx);
}

// update: 区间更新
// ul, ur: 需要更新的目标区间
// val: 新的高度值
void update(int node_idx, int l, int r, int ul, int ur, ll val)
{
    if (ul <= l && r <= ur)
    {
        tree[node_idx].max_val = val;
        tree[node_idx].lazy_tag = val;
        return;
    }

    push_down(node_idx);
    int mid = l + (r - l) / 2;
    if (ul <= mid)
    {
        update(node_idx * 2, l, mid, ul, ur, val);
    }
    if (ur > mid)
    {
        update(node_idx * 2 + 1, mid + 1, r, ul, ur, val);
    }
    push_up(node_idx);
}

// query: 区间查询
// ql, qr: 需要查询的目标区间
ll query(int node_idx, int l, int r, int ql, int qr)
{
    if (ql <= l && r <= qr)
    {
        return tree[node_idx].max_val;
    }

    push_down(node_idx);
    int mid = l + (r - l) / 2;
    ll max_h = 0;
    if (ql <= mid)
    {
        max_h = max(max_h, query(node_idx * 2, l, mid, ql, qr));
    }
    if (qr > mid)
    {
        max_h = max(max_h, query(node_idx * 2 + 1, mid + 1, r, ql, qr));
    }
    return max_h;
}

int main()
{
    // 提高cin/cout效率
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    initial_heights.resize(n + 1); // 使用1-based索引，方便对应题目
    for (int i = 1; i <= n; ++i)
    {
        cin >> initial_heights[i];
    }

    // 构建线段树，区间范围为 [1, n]
    build(1, 1, n);

    int m;
    cin >> m;

    for (int i = 0; i < m; ++i)
    {
        ll w, h;
        cin >> w >> h;

        // 1. 查询方块覆盖区域[1, w]的最高点
        ll landing_height = query(1, 1, n, 1, w);
        cout << landing_height << "\n";

        // 2. 更新方块覆盖区域[1, w]的高度
        ll new_height = landing_height + h;
        update(1, 1, n, 1, w, new_height);
    }

    return 0;
}
