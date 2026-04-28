#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Search {
public:
    Search() {
        std::cout << "Search:" << std::endl;
    }
    virtual ~Search() {
        std::cout << "Search finished." << std::endl;
    }
    virtual void searchPath(vector<vector<int>> &graph, int x, int n) = 0;
    void printResult() {
        if (result.size() == 0)
            cout << -1 << endl;
        for (const vector<int> &pa : result)
        {
            for (int i = 0; i < pa.size() - 1; i++)
            {
                cout << pa[i] << " ";
            }
            cout << pa[pa.size() - 1] << endl;
        }
    }
protected:
    vector<vector<int>> result; // 收集符合条件的路径
    vector<int> path;           // 1节点到终点的路径
};

class DFS : public Search {
private:
    void dfs(vector<vector<int>> &graph, int x, int n) {
        //  当前遍历的节点x 到达节点n
        if (x == n)
        {
            result.push_back(path);
            return;
        }
        for (int i = 1; i <= n; i++)
        { // 遍历节点x链接的所有节点
            if (graph[x][i] == 1)
            {
                path.push_back(i);
                dfs(graph, i, n);
                path.pop_back();
            }
        }
    }

public:
    DFS() {
        std::cout << "DFS search:" << std::endl;
    }
    ~DFS() {
        std::cout << "DFS search finished." << std::endl;
    }
    void searchPath(vector<vector<int>> &graph, int x, int n) override {
        path.clear();
        result.clear();
        path.push_back(x);
        dfs(graph, x, n);
    }
};

class BFS : public Search {
public:
    BFS() {
        std::cout << "BFS search:" << std::endl;
    }
    ~BFS() {
        std::cout << "BFS search finished." << std::endl;
    }
    void searchPath(vector<vector<int>> &graph, int x, int n) override {
        result.clear();
        path.clear();

        queue<vector<int>> que;
        que.push({x});

        while (!que.empty()) {
            vector<int> curPath = que.front();
            que.pop();

            int curNode = curPath.back();

            if (curNode == n) {
                result.push_back(curPath);
                continue;
            }

            for (int i = 1; i <= n; i++) {
                if (graph[curNode][i] == 1) {
                    vector<int> nextPath = curPath;
                    nextPath.push_back(i);
                    que.push(nextPath);
                }
            }
        }
    }
};

int main() {
    int n, m, s, t;
    cin >> n >> m; // n为节点数，m为边数
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, 0));
    while (m--) {
        cin >> s >> t;
        graph[s][t] = 1;
    }
    Search* dfs = new DFS();
    Search* bfs = new BFS();
    
    dfs->searchPath(graph, 1, n);
    dfs->printResult();
    bfs->searchPath(graph, 1, n);
    bfs->printResult();
    delete dfs;
    delete bfs;
    return 0;
}