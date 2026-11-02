# AVL Tree

This folder contains two standalone C++ programs illustrating AVL trees and their rotations.

## Files

| File | Purpose |
|---|---|
| [`AVLTree.cpp`](./AVLTree.cpp) | AVL tree with insertion, deletion, search, inorder traversal, and preorder traversal. |
| [`AVLRotations.cpp`](./AVLRotations.cpp) | Walkthrough of the LL, RR, LR, and RL rotation cases. |

## What is an AVL tree?

An AVL tree is a binary search tree that keeps itself height-balanced after insertions and deletions. For every node, the balance factor is

```text
height(left subtree) - height(right subtree)
```

and must remain in `[-1, 1]`. When it does not, one of four rotations restores balance:

| Imbalance | Repair |
|---|---|
| Left-left (LL) | Right rotation |
| Right-right (RR) | Left rotation |
| Left-right (LR) | Left rotation on the left child, then right rotation |
| Right-left (RL) | Right rotation on the right child, then left rotation |

## Operations and complexity

For `n` stored keys, AVL height remains `O(log n)`.

| Operation | Complexity |
|---|---|
| Insert | `O(log n)` |
| Delete | `O(log n)` |
| Search | `O(log n)` |
| Inorder / preorder traversal | `O(n)` |

Duplicate keys are ignored. The tree program releases all allocated nodes when the tree is destroyed.

## Build and run

Compile each program separately because each file has its own `main()`:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic AVLTree.cpp -o avl_tree
./avl_tree

g++ -std=c++11 -Wall -Wextra -pedantic AVLRotations.cpp -o avl_rotations
./avl_rotations
```

The rotation walkthrough prints the resulting root and inorder traversal for each case. Inorder output stays sorted, illustrating that rotations preserve the binary-search-tree ordering.
