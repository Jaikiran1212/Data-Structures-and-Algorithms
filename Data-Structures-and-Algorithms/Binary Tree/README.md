# Binary Tree

A complete, beginner-friendly **binary tree template** implemented in **C++**, **Java** and **Python** — same logic, same output, three languages.
No library containers are used (no STL, no `java.util`, no `collections.deque`): the queue is built by hand from a plain array/list.

## 📑 Table of Contents

- [Folder structure](#-folder-structure)
- [What is a binary tree?](#-what-is-a-binary-tree)
- [Tree used in the demo](#-tree-used-in-the-demo)
- [Operations implemented](#-operations-implemented)
- [Traversal orders](#-traversal-orders)
- [Time & space complexity](#-time--space-complexity)
- [How level-order insertion works](#-how-level-order-insertion-works)
- [Sample output](#-sample-output)
- [How to run](#%EF%B8%8F-how-to-run)
- [Language notes](#-language-notes)
- [Key concepts covered](#-key-concepts-covered)
- [What to learn next](#-what-to-learn-next)

## 📁 Folder structure

```
Binary Tree/
├── README.md
├── Cpp/
│   └── BinaryTree.cpp
├── Java/
│   └── BinaryTree.java
└── Python/
    └── binary_tree.py
```

| File | Language | Entry point |
|---|---|---|
| [`Cpp/BinaryTree.cpp`](./Cpp/BinaryTree.cpp) | C++ | `main()` |
| [`Java/BinaryTree.java`](./Java/BinaryTree.java) | Java | `BinaryTree.main()` |
| [`Python/binary_tree.py`](./Python/binary_tree.py) | Python 3 | `if __name__ == "__main__"` |

## 🌳 What is a binary tree?

A binary tree is a hierarchical structure where every **node** stores a value and has **at most two children** — a *left* child and a *right* child.

| Term | Meaning |
|---|---|
| **Root** | The top node (no parent) |
| **Leaf** | A node with no children |
| **Subtree** | A node together with everything below it |
| **Height** | Number of levels from the root down to the deepest leaf |

> This is a **general** binary tree (values are *not* kept in sorted order). A sorted version is called a Binary Search Tree.

## 🖼 Tree used in the demo

The numbers `1 2 3 4 5 6` are inserted one by one, filling each level from left to right:

```
          1            <- level 1 (root)
        /   \
       2     3         <- level 2
      / \   /
     4   5 6           <- level 3 (leaves: 4, 5, 6)
```

Nodes = 6 · Leaves = 3 · Height = 3

## 🧰 Operations implemented

| Operation | C++ / Java | Python | What it does |
|---|---|---|---|
| Insert (level order) | `insertLevel(x)` | `insert_level(x)` | Adds `x` in the first free slot, top to bottom, left to right |
| Preorder | `preorder()` | `preorder()` | Node → Left → Right |
| Inorder | `inorder()` | `inorder()` | Left → Node → Right |
| Postorder | `postorder()` | `postorder()` | Left → Right → Node |
| Level order | `levelorder()` | `level_order()` | Level by level (breadth-first) |
| Search | `search(x)` | `search(x)` | Is `x` present in the tree? |
| Count nodes | `countNodes()` | `count_nodes()` | Total number of nodes |
| Count leaves | `countLeaves()` | `count_leaves()` | Nodes with no children |
| Height | `height()` | `height()` | Number of levels |

## 🔀 Traversal orders

For the demo tree:

| Traversal | Rule | Result |
|---|---|---|
| Preorder | Node, Left, Right | `1 2 4 5 3 6` |
| Inorder | Left, Node, Right | `4 2 5 1 6 3` |
| Postorder | Left, Right, Node | `4 5 2 6 3 1` |
| Level order | Level by level | `1 2 3 4 5 6` |

The three depth-first traversals use the same recursive code — only the position of the "print" line changes.

## ⏱ Time & space complexity

`n` = number of nodes, `h` = height of the tree.

| Operation | Time | Extra space | Why |
|---|---|---|---|
| Level-order insert | **O(n)** | O(n) | Queue scan from the root until a free slot is found |
| Preorder / Inorder / Postorder | **O(n)** | O(h) | Every node is visited once; recursion depth = height |
| Level-order traversal | **O(n)** | O(n) | Every node visited once; queue can hold a whole level |
| Search | **O(n)** | O(h) | Tree is unsorted, so in the worst case every node is checked |
| Count nodes | **O(n)** | O(h) | Visits every node |
| Count leaves | **O(n)** | O(h) | Visits every node |
| Height | **O(n)** | O(h) | Visits every node |

**Notes**

- Because `insertLevel` always fills the next free slot, the tree stays **complete**, so `h = ⌊log₂ n⌋ + 1`. Recursion depth is therefore small (O(log n)) in this program.
- A tree built another way (for example a chain where each node has only one child) can have `h = n`, and recursion would use O(n) space.
- Constant-time (`O(1)`) work: `getRoot()` only.

## 🧠 How level-order insertion works

The function walks the tree **level by level** using a queue and puts the new node in the **first empty child slot** it meets.

1. If the tree is empty, the new node becomes the root.
2. Otherwise put the root in the queue.
3. Take the front node `p` out of the queue.
4. If `p` has no left child → attach the new node there and stop. Otherwise queue the left child.
5. If `p` has no right child → attach the new node there and stop. Otherwise queue the right child.
6. Repeat from step 3.

**Example — inserting `4` into the tree `1, 2, 3`:**

```
queue = [1]      take 1 -> left (2) exists, right (3) exists -> queue = [2, 3]
queue = [2, 3]   take 2 -> left is empty -> attach 4 as left child of 2. Done.
```

The queue is a plain **array** (C++/Java) or **list with a moving front index** (Python) — no built-in queue class.

## 📤 Sample output

All three programs print exactly the same thing:

```
Preorder   : 1 2 4 5 3 6
Inorder    : 4 2 5 1 6 3
Postorder  : 4 5 2 6 3 1
Level order: 1 2 3 4 5 6
Search 5   : Found
Nodes      : 6
Leaves     : 3
Height     : 3
```

## ▶️ How to run

**C++** (needs `g++`)
```bash
cd Cpp
g++ BinaryTree.cpp -o binarytree
./binarytree            # Windows: binarytree.exe
```

**Java** (JDK 8+)
```bash
cd Java
javac BinaryTree.java
java BinaryTree
```

**Python** (3.6+)
```bash
cd Python
python binary_tree.py   # or python3 binary_tree.py
```

## 🔍 Language notes

| Topic | C++ | Java | Python |
|---|---|---|---|
| Empty child | `NULL` | `null` | `None` |
| Child access | `p->left` | `p.left` | `p.left` |
| Queue | `Node* q[QMAX]` | `Node[] q = new Node[QMAX]` | `list` + front index |
| Queue size limit | 100 (`QMAX`) | 100 (`QMAX`) | none (list grows) |
| Memory | manual (`new`, never freed here) | garbage collected | garbage collected |
| Helper visibility | `private` section | `private` methods | `_underscore` names |

> **C++ memory note:** nodes are created with `new` and not freed, which is fine for a short demo. A production version would add a destructor that deletes every node.

## 💡 Key concepts covered

- Node structure (`data` + `left` + `right`)
- Recursion with a **base case** (empty subtree)
- Depth-first traversals (preorder, inorder, postorder)
- Breadth-first traversal with a hand-made queue
- Wrapper methods (public) that call recursive helpers (private)
- Tree measurements: node count, leaf count, height

## 🚀 What to learn next

- [ ] Binary Search Tree (insert, search, min, max, delete)
- [ ] Heaps (max heap, min heap, heap sort)
- [ ] Balanced trees (AVL, Red-Black)

## 📄 License

Feel free to use/reference this code for learning purposes.
