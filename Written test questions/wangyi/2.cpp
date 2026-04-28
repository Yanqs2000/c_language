#include <cctype>
#include <cstdio>
#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <string>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

string trim(const string &s)
{
    int l = 0, r = (int)s.size() - 1;
    while (l <= r && isspace((unsigned char)s[l]))
        l++;
    while (r >= l && isspace((unsigned char)s[r]))
        r--;
    return l > r ? "" : s.substr(l, r - l + 1);
}

vector<string> split(const string &s)
{
    vector<string> res;
    string cur;
    for (char c : s)
    {
        if (c == ',')
        {
            res.push_back(trim(cur));
            cur.clear();
        }
        else
        {
            cur += c;
        }
    }
    res.push_back(trim(cur));
    return res;
}

TreeNode *buildTree(const string &input)
{
    string s = trim(input);
    if (s.empty() || s == "null")
        return nullptr;

    vector<string> vals = split(s);
    if (vals.empty() || vals[0] == "null")
        return nullptr;

    TreeNode *root = new TreeNode(stoi(vals[0]));
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < (int)vals.size())
    {
        TreeNode *cur = q.front();
        q.pop();

        if (i < (int)vals.size() && vals[i] != "null")
        {
            cur->left = new TreeNode(stoi(vals[i]));
            q.push(cur->left);
        }
        i++;

        if (i < (int)vals.size() && vals[i] != "null")
        {
            cur->right = new TreeNode(stoi(vals[i]));
            q.push(cur->right);
        }
        i++;
    }
    return root;
}

void inorder(TreeNode *root, vector<int> &res)
{
    if (!root)
        return;
    inorder(root->left, res);
    res.push_back(root->val);
    inorder(root->right, res);
}

void postorder(TreeNode *root, vector<int> &res)
{
    if (!root)
        return;
    postorder(root->left, res);
    postorder(root->right, res);
    res.push_back(root->val);
}

vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    if (!root)
        return ans;

    queue<TreeNode *> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty())
    {
        int sz = q.size();
        vector<int> level(sz);

        for (int i = 0; i < sz; i++)
        {
            TreeNode *node = q.front();
            q.pop();

            int idx = leftToRight ? i : (sz - 1 - i);
            level[idx] = node->val;

            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        ans.push_back(level);
        leftToRight = !leftToRight;
    }
    return ans;
}

void printVector(const vector<int> &v)
{
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++)
    {
        if (i)
            cout << ", ";
        cout << v[i];
    }
    cout << "]\n";
}

void printVector2D(const vector<vector<int>> &vv)
{
    cout << "[";
    for (int i = 0; i < (int)vv.size(); i++)
    {
        if (i)
            cout << ", ";
        cout << "[";
        for (int j = 0; j < (int)vv[i].size(); j++)
        {
            if (j)
                cout << ", ";
            cout << vv[i][j];
        }
        cout << "]";
    }
    cout << "]";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    getline(cin, input);

    TreeNode *root = buildTree(input);
    vector<int> inRes, postRes;
    inorder(root, inRes);
    postorder(root, postRes);
    vector<vector<int>> zigzagRes = zigzagLevelOrder(root);

    printVector(inRes);
    printVector(postRes);
    printVector2D(zigzagRes);

    return 0;
}