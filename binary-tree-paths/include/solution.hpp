#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <string>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    std::vector<std::string> binaryTreePaths(TreeNode* root);

private:
    void dfs(TreeNode* node, std::string& path, std::vector<std::string>& result);
};

// Helper utilities for tree lifecycle management
TreeNode* createNode(int val);
void deleteTree(TreeNode* root);

#endif // SOLUTION_HPP