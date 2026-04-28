#include <iostream>
using namespace std;

using int64 = long long;

const int MAXB = 60; // 10^15 用 60 位足够

int bitL[MAXB + 1], bitR[MAXB + 1];
int dp[MAXB + 1][2][2];
bool vis[MAXB + 1][2][2];

int dfs(int pos, int tightL, int tightR)
{
    if (pos < 0)
        return 0;
    if (vis[pos][tightL][tightR])
        return dp[pos][tightL][tightR];
    vis[pos][tightL][tightR] = true;

    int low = tightL ? bitL[pos] : 0;
    int high = tightR ? bitR[pos] : 1;

    int best = -1;
    for (int b = low; b <= high; ++b)
    {
        int ntL = tightL && (b == bitL[pos]);
        int ntR = tightR && (b == bitR[pos]);
        best = max(best, b + dfs(pos - 1, ntL, ntR));
    }

    return dp[pos][tightL][tightR] = best;
}

long long solveOne(long long L, long long R)
{
    for (int i = 0; i <= MAXB; ++i)
    {
        bitL[i] = (L >> i) & 1;
        bitR[i] = (R >> i) & 1;
    }

    memset(vis, 0, sizeof(vis));
    int bestOnes = dfs(MAXB, 1, 1);

    long long ans = 0;
    int tightL = 1, tightR = 1;

    // 从高位到低位恢复最小答案
    for (int pos = MAXB; pos >= 0; --pos)
    {
        int low = tightL ? bitL[pos] : 0;
        int high = tightR ? bitR[pos] : 1;

        for (int b = low; b <= high; ++b)
        { // 先试 0，再试 1，保证最小
            int ntL = tightL && (b == bitL[pos]);
            int ntR = tightR && (b == bitR[pos]);

            int remain = dfs(pos - 1, ntL, ntR);
            if (b + remain == bestOnes)
            {
                if (b)
                    ans |= (1LL << pos);
                tightL = ntL;
                tightR = ntR;
                bestOnes -= b;
                break;
            }
        }
    }

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--)
    {
        long long l, r;
        cin >> l >> r;
        cout << solveOne(l, r - 1) << '\n';
    }

    return 0;
}