#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int main()
{
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<vector<int>> grid(n + 1, vector<int>(n + 1, INT_MAX));
    for (int i = 0; i < m; i++)
    {
        cin >> p1 >> p2 >> val;
        grid[p1][p2] = val;
    }

    int start = 1;
    int end = n;

    // 存储从源点到每个节点的最短距离
    std::vector<int> minDist(n + 1, INT_MAX);

    // 记录顶点是否被访问过
    std::vector<bool> visited(n + 1, false);

    minDist[start] = 0; // 起始点到自身的距离为0

    for (int i = 1; i <= n; i++)
    { // 遍历所有节点

        int minVal = INT_MAX;
        int cur = 1;

        // 1、选距离源点最近且未访问过的节点
        for (int v = 1; v <= n; ++v)
        {
            if (!visited[v] && minDist[v] < minVal)
            {
                minVal = minDist[v];
                cur = v;
            }
        }

        visited[cur] = true; // 2、标记该节点已被访问

        // 3、第三步，更新非访问节点到源点的距离（即更新minDist数组）
        for (int v = 1; v <= n; v++)
        {
            if (!visited[v] && grid[cur][v] != INT_MAX && minDist[cur] + grid[cur][v] < minDist[v])
            {
                minDist[v] = minDist[cur] + grid[cur][v];
            }
        }
    }

    if (minDist[end] == INT_MAX)
        cout << -1 << endl; // 不能到达终点
    else
        cout << minDist[end] << endl; // 到达终点最短路径
}