#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

// Segment Tree with Lazy Propagation
struct Node
{
    long long max_val;
    long long lazy;
};

vector<Node> tree;
vector<long long> initial_array;

void build(int node, int start, int end)
{
    if (start == end)
    {
        tree[node] = {initial_array[start], 0};
        return;
    }
    int mid = start + (end - start) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
    tree[node] = {max(tree[2 * node].max_val, tree[2 * node + 1].max_val), 0};
}

void push(int node)
{
    if (tree[node].lazy != 0)
    {
        tree[2 * node].max_val += tree[node].lazy;
        tree[2 * node].lazy += tree[node].lazy;
        tree[2 * node + 1].max_val += tree[node].lazy;
        tree[2 * node + 1].lazy += tree[node].lazy;
        tree[node].lazy = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, int val)
{
    if (start > end || start > r || end < l)
    {
        return;
    }
    if (l <= start && end <= r)
    {
        tree[node].max_val += val;
        tree[node].lazy += val;
        return;
    }
    push(node);
    int mid = start + (end - start) / 2;
    update_range(2 * node, start, mid, l, r, val);
    update_range(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
}

long long query_range(int node, int start, int end, int l, int r)
{
    if (start > end || start > r || end < l)
    {
        return -INF;
    }
    if (l <= start && end <= r)
    {
        return tree[node].max_val;
    }
    push(node);
    int mid = start + (end - start) / 2;
    long long p1 = query_range(2 * node, start, mid, l, r);
    long long p2 = query_range(2 * node + 1, mid + 1, end, l, r);
    return max(p1, p2);
}

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    int max_val = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }

    vector<long long> b(n, 0);
    vector<int> freq(max_val + 2, 0);

    // Calculate prefix_gain
    for (int i = 0; i < n; ++i)
    {
        if (a[i] + 1 <= max_val)
        {
            b[i] += freq[a[i] + 1];
        }
        freq[a[i]]++;
    }

    fill(freq.begin(), freq.end(), 0);
    // Calculate suffix_loss
    for (int i = n - 1; i >= 0; --i)
    {
        b[i] -= freq[a[i]];
        freq[a[i]]++;
    }

    vector<long long> p_b(n + 1, 0);
    for (int i = 0; i < n; ++i)
    {
        p_b[i + 1] = p_b[i] + b[i];
    }

    // Initialize Segment Tree
    initial_array.assign(n + 1, 0);
    for (int i = 0; i < n + 1; ++i)
    {
        initial_array[i] = -p_b[i];
    }

    tree.assign(4 * (n + 1), {0, 0});
    build(1, 0, n);

    vector<vector<int>> pos(max_val + 2);
    long long max_reduction = 0;

    for (int R = 0; R < n; ++R)
    {
        int val = a[R];
        // Update for a_k = a_R
        for (int p : pos[val])
        {
            // for L <= p+1, correction term increases by 1
            update_range(1, 0, n, 0, p, 1);
        }
        pos[val].push_back(R);

        // Update for a_k = a_R+1
        if (val + 1 <= max_val)
        {
            for (int p : pos[val + 1])
            {
                // for L <= p+1, correction term decreases by 1
                update_range(1, 0, n, 0, p, -1);
            }
        }

        // Query for max_{L in 0..R} (-p_b[L] + Corr(L+1, R+1))
        long long M = query_range(1, 0, n, 0, R);
        max_reduction = max(max_reduction, p_b[R + 1] + M);
    }

    cout << max_reduction << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
