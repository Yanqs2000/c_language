#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    int v, e;
    int x, y, k;
    cin >> v >> e;
    vector<vector<int>> graph(v + 1, vector<int>(v + 1, INT_MAX));
    while (e--) {
        cin >> x >> y >> k;
        graph[x][y] = k;
        graph[y][x] = k;
    }

    vector<int> minDist(v + 1, INT_MAX);
    vector<bool> visited(v + 1, false);

    for (int i = 1; i < v; i++) {
        // 1.选距离生成树最近的点
        int cur = -1;
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) {
            //选取最小生成树节点的条件：
            //（1）不在最小生成树里
            //（2）距离最小生成树最近的节点
            if (!visited[j] && minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }

        // 2.把这个点加入最小生成树
        visited[cur] = true;

        // 3、prim三部曲，第三步：更新非生成树节点到生成树的距离（即更新minDist数组）
        // cur节点加入之后， 最小生成树加入了新的节点，那么所有节点到 最小生成树的距离（即minDist数组）需要更新一下
        // 由于cur节点是新加入到最小生成树，那么只需要关心与 cur 相连的 非生成树节点 的距离 是否比 原来 非生成树节点到生成树节点的距离更小了呢

        for (int j = 1; j <= v; j++) {
            if (!visited[j] && graph[cur][j] < minDist[j]) {
                minDist[j] = graph[cur][j];
            }
        }
    }
    int sum = 0;
    for (int i = 2; i <= v; i++) {
        sum += minDist[i];
    }
    cout << sum << endl;
    
    return 0;
}