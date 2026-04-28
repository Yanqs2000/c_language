#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

// 题目提供的结构体，无需修改
struct Transfer
{
    int u;
    int v;
};

// 题目提供的字符串解析函数，无需修改
vector<Transfer> parse_transfer_string(const string &s)
{
    vector<Transfer> transfers;
    size_t i = 0;
    size_t len = s.length();

    while (i < len)
    {
        if (s[i] == '(')
        {
            i++;
            string u_str;
            while (i < len && isdigit(s[i]))
            {
                u_str += s[i++];
            }

            while (i < len && (s[i] == ',' || s[i] == ' '))
            {
                i++;
            }

            string v_str;
            while (i < len && isdigit(s[i]))
            {
                v_str += s[i++];
            }

            if (!u_str.empty() && !v_str.empty())
            {
                transfers.push_back({stoi(u_str), stoi(v_str)});
            }
        }
        else
        {
            i++;
        }
    }
    return transfers;
}   

// 题目提供的图结构，你需要在这里完成核心代码
class Graph
{
private:
    int n;                        // 账户数量（节点数）
    vector<vector<int>> adj_list; // 邻接表

    // 辅助函数：使用深度优先搜索检测环路
    // u: 当前访问的节点
    // visited_states: 记录每个节点状态的数组
    //   0: unvisited (未访问)
    //   1: visiting (访问中，在当前递归栈中)
    //   2: visited (已访问，所有子节点都已探索完毕)
    bool hasCycleUtil(int u, vector<int> &visited_states)
    {
        // 将当前节点标记为“访问中”
        visited_states[u] = 1;

        // 遍历所有与节点u邻接的节点v
        for (int v : adj_list[u])
        {
            // 如果邻接节点v的状态是“访问中”，说明找到了一个环
            if (visited_states[v] == 1)
            {
                return true;
            }
            // 如果邻接节点v是“未访问”状态，则对其进行递归DFS
            if (visited_states[v] == 0)
            {
                if (hasCycleUtil(v, visited_states))
                {
                    return true;
                }
            }
            // 如果邻接节点v的状态是“已访问”(visited_states[v] == 2)，
            // 说明从v出发的路径已经被探索过且没有发现环，直接跳过。
        }

        // 当节点u的所有邻接节点都已访问完毕，将u标记为“已访问”
        visited_states[u] = 2;

        // 从u出发没有找到环
        return false;
    }

public:
    Graph(int n) : n(n), adj_list(n) {}

    void add_edge(int u, int v)
    {
        adj_list[u].push_back(v);
    }

    // ================== 在该函数内完成题目要求 ==================
    // 你可以定义其他辅助函数
    bool solution()
    {
        // 创建一个数组来记录每个节点的访问状态
        // 初始化所有节点为 0 (unvisited)
        vector<int> visited_states(n, 0);

        // 遍历图中的每一个节点，因为图可能是不连通的
        for (int i = 0; i < n; ++i)
        {
            // 如果当前节点尚未被访问过
            if (visited_states[i] == 0)
            {
                // 从该节点开始进行DFS，检查是否存在环
                if (hasCycleUtil(i, visited_states))
                {
                    // 如果找到了环，立即返回true
                    return true;
                }
            }
        }

        // 如果遍历完所有节点都没有发现环，则返回false
        return false;
    }
    // ========================================================
};

// 题目提供的输入读取函数，无需修改
void read_input(int &n, int &m, string &transfers_str)
{
    string n_line, m_line;
    getline(cin, n_line);
    getline(cin, m_line);
    getline(cin, transfers_str);

    // 简单的去除末尾可能存在的逗号
    size_t n_comma = n_line.find(',');
    if (n_comma != string::npos)
    {
        n_line = n_line.substr(0, n_comma);
    }
    size_t m_comma = m_line.find(',');
    if (m_comma != string::npos)
    {
        m_line = m_line.substr(0, m_comma);
    }

    n = stoi(n_line);
    m = stoi(m_line);

    // 去除字符串前后的引号和方括号
    size_t first = transfers_str.find_first_of("[");
    size_t last = transfers_str.find_last_of("]");
    if (first != string::npos && last != string::npos)
    {
        transfers_str = transfers_str.substr(first + 1, last - first - 1);
    }
}

// 题目提供的主函数框架，无需修改
int main()
{
    int n, m;
    string transfers_str;

    read_input(n, m, transfers_str);

    vector<Transfer> transfers = parse_transfer_string(transfers_str);

    Graph graph(n);
    for (const auto &transfer : transfers)
    {
        graph.add_edge(transfer.u, transfer.v);
    }

    bool result = graph.solution();

    cout << (result ? "True" : "False") << endl;

    return 0;
}
