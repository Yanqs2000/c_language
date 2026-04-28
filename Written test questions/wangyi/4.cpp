#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

const int B = 150;
const int MAX_COORD = 100005;
const int OFFSET = 100000 * 150 + 5;
const int BIT_SIZE = MAX_COORD + OFFSET + 100005;

struct Bird
{
    int x, t, start_jump;
};

struct FenwickTree
{
    vector<int> tree;
    void init(int n)
    {
        tree.assign(n + 1, 0);
    }
    void update(int i, int delta)
    {
        for (; i < tree.size(); i += i & -i)
            tree[i] += delta;
    }
    int query(int i)
    {
        int sum = 0;
        i = min(i, (int)tree.size() - 1);
        for (; i > 0; i -= i & -i)
            sum += tree[i];
        return sum;
    }

    int query(int l, int r)
    {
        if (l > r)
            return 0;
        return query(r) - query(max(0, l - 1));
    }
};

vector<int> small_t_birds[B + 1];
vector<Bird> big_birds;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    int total_global_jumps = 0;

    while (Q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x, t;
            cin >> x >> t;
            if (t > B)
            {
                big_birds.push_back({x, t, total_global_jumps});
            }
            else
            {
                int fixed_val = x - total_global_jumps * t;
                small_t_birds[t].push_back(fixed_val);
            }
        }
        else if (op == 2)
        {
            total_global_jumps++;
        }
        else if (op == 3)
        {
            int l, r;
            cin >> l >> r;
            int count = 0;

            for (const auto &bird : big_birds)
            {
                long long cur_pos = (long long)bird.x + (long long)(total_global_jumps - bird.start_jump) * bird.t;
                if (cur_pos >= l && cur_pos <= r)
                {
                    count++;
                }
            }

            for (int t = 1; t <= B; ++t)
            {
                if (small_t_birds[t].empty())
                    continue;
                int target_l = l - total_global_jumps * t;
                int target_r = r - total_global_jumps * t;

                for (int fv : small_t_birds[t])
                {
                    if (fv >= target_l && fv <= target_r)
                    {
                        count++;
                    }
                }
            }
            cout << count << "\n";
        }
    }

    return 0;
}
