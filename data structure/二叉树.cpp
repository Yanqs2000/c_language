#include <iostream>
#include <queue>

using namespace std;

class TreeNode
{
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class State
{
public:
    TreeNode* node;
    int depth;

    State(TreeNode* node, int depth) : node(node), depth(depth) {}
};

// 构造一个二叉树
void build()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
}

// 二叉树的递归遍历(DFS)
void traverse(TreeNode* root)
{
    if (root == NULL)
        return;
    // 前序位置
    traverse(root->left);
    // 中序位置
    traverse(root->right);
    // 后序位置
}

// 二叉树的层序遍历(BFS)
void levelTraverse01(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);

    // 首先放入头元素，然后每次将头元素出队，将头元素的左右子节点入队
    while (!q.empty())
    {
        TreeNode* cur = q.front();
        q.pop();

        cout << cur->val << " " << endl; 

        if(cur->left != NULL)
        {
            q.push(cur->left);
        }
        if(cur->right != NULL)
        {
            q.push(cur->right);
        }
    }
}

void levelTraverse02(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    // 记录当前遍历的层数(root为第一层)
    int depth = 1;
    
    // 按层进行遍历
    while (!q.empty())
    {
        int size = q.size();
        for(int i = 0; i < size; i++)
        {
            TreeNode* cur = q.front();
            q.pop();
            // 访问 cur 节点, 同时知道它所在的层数
            cout << "Depth: " << depth << " value: " << cur->val << endl;

            // 将 cur 的子节点加入队列
            if(cur->left != NULL)
            {
                q.push(cur->left);
            }
            if(cur->right != NULL)
            {
                q.push(cur->right);
            }
        }
        depth++;
    }
}

// 按层进行遍历，并且每个层的权重不等
void levelTraverse03(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    queue<State> q;
    // 根节点的路径权重和为 1 
    q.push(State(root, 1));

    while (!q.empty())
    {
        State cur = q.front();
        q.pop();
        // 访问 cur 节点, 同时知道它所在的层数(深度)
        cout << "Depth: " << cur.depth << " value: " << cur.node->val << endl;

        // 将 cur 的子节点加入队列
        if(cur.node->left != NULL)
        {
            q.push(State(cur.node->left, cur.depth + 1));
        }
        if(cur.node->right != NULL)
        {
            q.push(State(cur.node->right, cur.depth + 1));
        }
    }
    
}

// 求最短距离
class Solution01_DFS
{
private:
    // 记录最小深度（根节点到最近的叶子节点的距离）
    int minDepthValue = INT_MAX;
    // 记录当前遍历到的节点深度
    int currentDepth = 0;

public:
    int minDepth(TreeNode* root)
    {
        if (root == NULL)
        {
            return 0;
        }
        traverse(root);
        return minDepthValue;
    }

    void traverse(TreeNode* root)
    {
        if (root == NULL)
        {
            return;
        }
        // 前序位置进入节点时，增加当前深度
        currentDepth++;
        // 如果是叶子节点，更新最小深度
        if (root->left == NULL && root->right == NULL)
        {
            minDepthValue = min(minDepthValue, currentDepth);
        }
        traverse(root->left);
        traverse(root->right);
        // 后序位置离开节点时，减少当前深度
        currentDepth--;
    }
};


class Solution02_BFS
{
public:
    int minDepth(TreeNode* root)
    {
        if(root == NULL)
        {
            return 0;
        }
        queue<TreeNode*> q;
        q.push(root);
        // root本身就是一层
        int depth = 1;

        while (!q.empty())
        {
            int size = q.size();
            // 遍历当前节点
            for(int i = 0; i < size; i++)
            {
                TreeNode* cur = q.front();
                q.pop();
                // 如果是叶子节点，返回当前深度
                if (cur->left == NULL && cur->right == NULL)
                {
                    return depth;
                }
                // 将子节点加入队列
                if (cur->left != NULL)
                {
                    q.push(cur->left);
                }
                if (cur->right != NULL)
                {
                    q.push(cur->right);
                }
            }
            depth++;
        }
        return depth;
    }
};

int main()
{
    // 手动构造示例二叉树
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    // 调用 minDepth 函数
    Solution01_DFS sol01;
    int result01 = sol01.minDepth(root);
    cout << "二叉树的最小深度是: " << result01 << endl; // 期望输出 2

    // 调用 minDepth 函数
    Solution02_BFS sol02;
    int result02 = sol02.minDepth(root);
    cout << "二叉树的最小深度是: " << result02 << endl; // 期望输出 2
    return 0;
}
