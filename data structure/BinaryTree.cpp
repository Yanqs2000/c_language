#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Tree {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    static void printVector(const vector<int> &nums) {
        for (int num : nums) {
            cout << num << " ";
        }
        cout << endl;
    }

    static TreeNode* buildTree(const vector<string> &nodes) {
        if (nodes.empty()) return nullptr;

        TreeNode* root = new TreeNode(stoi(nodes[0]));
        queue<TreeNode*> q;
        q.push(root);

        for (int i = 1; i < nodes.size(); i++) {
            TreeNode* cur = q.front();
            q.pop();

            if (i < nodes.size() && nodes[i] != "null")
            {
                cur->left = new TreeNode(stoi(nodes[i]));
                q.push(cur->left);
            }

            if (++i < nodes.size() && nodes[i] != "null")
            {
                cur->right = new TreeNode(stoi(nodes[i]));
                q.push(cur->right);
            }
        }
        return root;
    }
    // 后序删除
    static void freeTreeNode(TreeNode *root) {
        if (root == nullptr)
            return;
        freeTreeNode(root->left);
        freeTreeNode(root->right);
        delete root;
    }
};

class Traverse {
public:
    virtual void travel(Tree::TreeNode* root, vector<int> &nums) = 0;
    virtual ~Traverse() = default;
};

class preorderTraverse : public Traverse {
public:
    void travel(Tree::TreeNode *root, vector<int> &nums) override {
        preOrder(root, nums);
    }

private:
    void preOrder(Tree::TreeNode* cur, vector<int> &nums) {
        if (cur == nullptr) return;

        nums.push_back(cur->val);
        preOrder(cur->left, nums);
        preOrder(cur->right, nums);
    }
};

class inorderTraverse : public Traverse {
public:
    void travel(Tree::TreeNode *root, vector<int> &nums) override {
        inOrder(root, nums);
    }

private:
    void inOrder(Tree::TreeNode *cur, vector<int> &nums) {
        if (cur == nullptr)
            return;

        inOrder(cur->left, nums);
        nums.push_back(cur->val);
        inOrder(cur->right, nums);
    }
};

class postorderTraverse : public Traverse {
public:
    void travel(Tree::TreeNode *root, vector<int> &nums) override {
        postOrder(root, nums);
    }

private:
    void postOrder(Tree::TreeNode *cur, vector<int> &nums) {
        if (cur == nullptr)
            return;

        postOrder(cur->left, nums);
        postOrder(cur->right, nums);
        nums.push_back(cur->val);
    }
};

class levalorderTraverse : public Traverse {
public:
    void travel(Tree::TreeNode *root, vector<int> &nums) override {
        levelOrder(root, nums);
    }

private:
    void levelOrder(Tree::TreeNode *root, vector<int> &nums) {
        queue<Tree::TreeNode*> que;
        if (root != nullptr) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                Tree::TreeNode* node = que.front();
                que.pop();
                nums.push_back(node->val);
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
    }
};

int main() {
    vector<string> input = {"1", "2", "3", "4", "5", "null", "8", "null", "null", "6", "7", "9"};
    Tree::TreeNode* root = Tree::buildTree(input);

    Traverse *t_preorder = new preorderTraverse();
    Traverse *t_inorder = new inorderTraverse();
    Traverse *t_postorder = new postorderTraverse();
    Traverse *t_levelorder = new levalorderTraverse();

    vector<int> preNums;
    vector<int> inNums;
    vector<int> postNums;
    vector<int> levelNums;

    t_preorder->travel(root, preNums);
    t_inorder->travel(root, inNums);
    t_postorder->travel(root, postNums);
    t_levelorder->travel(root, levelNums);

    Tree::printVector(preNums);
    Tree::printVector(inNums);
    Tree::printVector(postNums);
    Tree::printVector(levelNums);

    delete t_preorder;
    delete t_inorder;
    delete t_postorder;
    delete t_levelorder;
    Tree::freeTreeNode(root);

    return 0;
}