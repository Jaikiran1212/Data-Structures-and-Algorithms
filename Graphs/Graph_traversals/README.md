# Graph Traversals: BFS & DFS (C++)

A low-level implementation of the two foundational graph traversal algorithms — **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** — on an undirected graph in C++.

Implemented strictly from first principles without relying on STL containers (`std::stack`, `std::queue`, `std::vector`), using custom dynamic array-based stack and queue buffers and manual dynamic linked list adjacency lists.

---

## 📁 Directory Structure

```text
Graph_traversals/
├── BFS_and_DFS.cpp     # Complete Graph class with iterative BFS & DFS
└── README.md           # Documentation, algorithmic comparison & run guide
```

---

## 🧠 Algorithmic Concepts

### Graph Topology (Sample Demo)

The demo initializes an undirected graph with 6 vertices ($V = 6$, labeled $0 \dots 5$) and 5 edges:

```text
        0
       / \
      1   2
     / \   \
    3   4   5
```

Because edges are prepended to the linked lists at insertion, the adjacency list order is:
- **0**: `2 -> 1`
- **1**: `4 -> 3 -> 0`
- **2**: `5 -> 0`
- **3**: `1`
- **4**: `1`
- **5**: `2`

---

### 1. Depth-First Search (DFS)
- **Strategy**: Explores as deep as possible along each branch before backtracking.
- **Data Structure**: Explicit **LIFO Stack** (`int* stack`).
- **Mechanism**:
  1. Push start vertex onto the stack.
  2. While the stack is not empty, pop top vertex $u$.
  3. If $u$ is unvisited: mark visited, print $u$, and push all unvisited neighbors of $u$ onto the stack.
- **Trace from Source 0**: `0 -> 1 -> 3 -> 4 -> 2 -> 5`

### 2. Breadth-First Search (BFS)
- **Strategy**: Explores all neighbors at the current depth level before moving deeper.
- **Data Structure**: Explicit **FIFO Queue** (`int* queue`).
- **Mechanism**:
  1. Enqueue start vertex and mark it visited.
  2. While the queue is not empty, dequeue front vertex $u$ and print it.
  3. Traverse all unvisited neighbors $v$ of $u$, mark them visited, and enqueue them.
- **Trace from Source 0**: `0 -> 2 -> 1 -> 5 -> 4 -> 3`

---

## 📊 Comparison Matrix

| Property | Depth-First Search (DFS) | Breadth-First Search (BFS) |
|---|---|---|
| **Underlying Mechanism** | LIFO (Stack) | FIFO (Queue) |
| **Exploration Style** | Deep branch exploration | Level-by-level radial exploration |
| **Time Complexity** | $O(V + E)$ | $O(V + E)$ |
| **Space Complexity** | $O(V)$ (visited + stack buffers) | $O(V)$ (visited + queue buffers) |
| **Shortest Path (Unweighted)** | No | **Yes** (guarantees minimum edges) |
| **Key Applications** | Topological sort, cycle detection, strongly connected components | Shortest path on unweighted graphs, level-order traversal, web crawling |

---

## ▶️ Compilation & Execution

Compile and run using `g++` (C++11 or later):

```bash
g++ -std=c++11 BFS_and_DFS.cpp -o bfs_dfs
./bfs_dfs
```

### 📤 Sample Output

```text
DFS: 0 1 3 4 2 5 
BFS: 0 2 1 5 4 3 
```

---

## 🛡 Memory Management

- **Internal Stack & Queue**: Both `DFS()` and `BFS()` dynamically allocate helper buffers (`visited`, `stack`, `queue`) of size $V$ and immediately release them via `delete[]` upon method completion.
- **Adjacency Lists**: The `~Graph()` destructor traverses every vertex's linked list to deallocate each `Node` individually with `delete`, followed by `delete[] adj`.
