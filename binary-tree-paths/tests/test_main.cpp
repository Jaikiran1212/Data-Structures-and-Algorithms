#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include "solution.hpp"

void testStandardTree() {
    // Tree:
    //      1
    //     / \
    //    2   3
    //     \
    //      5
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->right = createNode(5);

    Solution solver;
    std::vector<std::string> paths = solver.binaryTreePaths(root);

    assert(paths.size() == 2);
    assert(paths[0] == "1->2->5");
    assert(paths[1] == "1->3");

    deleteTree(root);
    std::cout << "[PASS] testStandardTree" << std::endl;
}

void testSingleNode() {
    TreeNode* root = createNode(42);

    Solution solver;
    std::vector<std::string> paths = solver.binaryTreePaths(root);

    assert(paths.size() == 1);
    assert(paths[0] == "42");

    deleteTree(root);
    std::cout << "[PASS] testSingleNode" << std::endl;
}

void testEmptyTree() {
    Solution solver;
    std::vector<std::string> paths = solver.binaryTreePaths(nullptr);

    assert(paths.empty());
    std::cout << "[PASS] testEmptyTree" << std::endl;
}

int main() {
    std::cout << "Running tests..." << std::endl;
    testStandardTree();
    testSingleNode();
    testEmptyTree();
    std::cout << "All test assertions passed successfully!" << std::endl;
    return 0;
}