# Binary Tree Paths (LeetCode #257)

A fast, memory-optimized **C++17** solution for [LeetCode Problem 257: Binary Tree Paths](https://leetcode.com/problems/binary-tree-paths/).

Includes modern CMake build configuration, modular source structure, and automated unit test assertions.

---

## 📁 Directory Structure

```text
binary-tree-paths/
├── CMakeLists.txt        # CMake build configuration (C++17)
├── README.md             # Project documentation & problem guide
├── include/
│   └── solution.hpp      # TreeNode definition & Solution class interface
├── src/
│   └── solution.cpp      # DFS backtracking algorithm implementation
└── tests/
    └── test_main.cpp     # Test suite with assertion checks
```

---

## 📋 Problem Description

Given the `root` of a binary tree, return all **root-to-leaf paths** in any order. A leaf is defined as a node with no children.

Each path must be formatted as node values separated by arrows: `"root->node->...->leaf"`.

### Example 1:

```text
       1
     /   \
    2     3
     \
      5
```

- **Input:** `root = [1, 2, 3, null, 5]`
- **Output:** `["1->2->5", "1->3"]`

### Example 2:

- **Input:** `root = [1]`
- **Output:** `["1"]`

---

## 💡 Solution Strategy: DFS with State Unwinding

The solution utilizes Depth-First Search (DFS) with an optimized in-place backtracking string buffer:

1. **Path Buffer by Reference**: Rather than copying strings at each recursive call (which leads to $O(n^2)$ copying overhead), a single `std::string& path` is passed by reference.
2. **Backtracking via Resize**: Before appending the current node's value and arrow `"->"`, the method records `size_t prev_len = path.length()`.
3. **Leaf Detection**: When reaching a leaf (`!node->left && !node->right`), the assembled path is added to `result`.
4. **State Restoration**: After recursive calls return, `path.resize(prev_len)` instantaneously restores the string buffer to its previous state in $O(1)$ time.

---

## ⏱ Complexity Analysis

- **Time Complexity:** $O(n)$ where $n$ is the number of nodes in the binary tree. Each node is visited once during the DFS traversal.
- **Space Complexity:** $O(h)$ where $h$ is the height of the tree for recursion stack frames and the string path buffer (excluding the result list). In a balanced tree, $h = O(\log n)$; in the worst case (skewed tree), $h = O(n)$.

---

## 🛠 Building & Running Tests

### Option 1: Using CMake (Recommended)

```bash
mkdir build && cd build
cmake ..
make
./run_tests
```

### Option 2: Direct Compilation with `g++`

```bash
g++ -std=c++17 -Iinclude src/solution.cpp tests/test_main.cpp -o run_tests
./run_tests
```

**Test Output:**
```text
Running tests...
[PASS] testStandardTree
[PASS] testSingleNode
[PASS] testEmptyTree
All test assertions passed successfully!
```

---

## 🛡 Memory Management

To ensure zero memory leaks during testing, the library provides a recursive helper `deleteTree(TreeNode* root)` that traverses subtrees in post-order and deallocates every dynamically allocated `TreeNode` before program termination.