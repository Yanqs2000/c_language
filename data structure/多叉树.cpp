#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node
{
public:
    int val;
    vector<Node*> children;
};

class State
{
public:
    Node* node;
    int depth;
    State(Node* node, int depth) : node(node), depth(depth) {}
};

// 多叉树的递归遍历
void traverse(Node* root)
{
    if (root == NULL)
    {
        return;
    }
    // 遍历vector中的每个元素
    // 前序位置
    for (Node* child : root->children)
    {
        traverse(child);
    }
    // 后续位置
}

// 多叉树的层序遍历
void levelTraverse01(Node* root)
{
    if(root == NULL)
    {
        return;
    }
    queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        Node* cur = q.front();
        q.pop();
        cout << cur->val << " ";
        for(Node* child : cur->children)
        {
            q.push(child);
        }
    }
}

void levelTraverse02(Node* root)
{
    if(root == NULL)
    {
        return;
    }
    queue<Node*> q;
    q.push(root);
    // 记录当前遍历的层数(root为第一层)
    int depth = 1;

    // 按层进行遍历
    while(!q.empty())
    {
        int size = q.size();
        for(int i = 0; i < size; i++)
        {
            Node* cur = q.front();
            q.pop();
            // 访问 cur 节点, 同时知道它所在的层数
            cout << "Depth: " << depth << " value: " << cur->val << endl;

            // 将 cur 的子节点加入队列
            for(Node* child : cur->children)
            {
                q.push(child);
            }
        }
        depth++;
    }
}

void levelTraverse03(Node* root)
{
    if(root == NULL)
    {
        return;
    }

    queue<State> q;
    q.push(State(root, 1));

    while(!q.empty())
    {
        State cur = q.front();
        q.pop();

        cout << "Depth: " << cur.depth << " value: " << cur.node->val << endl;
        for (Node* child : cur.node->children)
        {
            q.push(State(child, cur.depth + 1));
        }
    }
}