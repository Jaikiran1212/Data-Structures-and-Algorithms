#include "solution.hpp"

void Solution::dfs(TreeNode* node, std::string& path, std::vector<std::string>& result) {
    if (!node) return;

    size_t prev_len = path.length();
    path += std::to_string(node->val);

    // Leaf node: append current path to results
    if (!node->left && !node->right) {
        result.push_back(path);
    } else {
        path += "->";
        if (node->left) dfs(node->left, path, result);
        if (node->right) dfs(node->right, path, result);
    }

    // Backtrack to previous state
    path.resize(prev_len);
}

std::vector<std::string> Solution::binaryTreePaths(TreeNode* root) {
    std::vector<std::string> result;
    if (!root) return result;

    std::string path;
    dfs(root, path, result);
    return result;
}

TreeNode* createNode(int val) {
    return new TreeNode(val);
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}