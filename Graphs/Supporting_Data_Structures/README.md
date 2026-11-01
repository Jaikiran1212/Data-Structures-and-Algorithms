# Supporting Data Structures for Graph Algorithms (C++)

A collection of high-performance, low-level **Supporting Data Structures** implemented from first principles in C++. 

These data structures serve as the algorithmic backbone for advanced graph algorithms such as **Kruskal's Minimum Spanning Tree (MST)**, **Prim's MST**, **Dijkstra's Shortest Path**, and **Disjoint-Set Cycle Detection**.

Consistent with this repository's design principles, all implementations avoid standard library abstractions (`std::priority_queue`, `std::vector`, `std::set`) in favor of direct dynamic array memory management and clean destructors (RAII).

---

## 📁 Directory Structure

```text
Supporting_Data_Structures/
├── DSU.h               # Disjoint Set Union (Path Compression + Union by Rank)
├── MinHeap.h           # Array-based Min-Heap keyed on edge weights (Kruskal)
├── PriorityQueue.h     # Array-based Min-Priority Queue for vertices (Dijkstra/Prim)
├── main.cpp            # Unified test driver & demonstration
└── README.md           # Documentation, complexity analysis & algorithmic usage
```

---

## 🧩 Components Overview

### 1. Disjoint Set Union — DSU (`DSU.h`)
Manages a partition of $n$ elements into disjoint subsets.
- **Path Compression**: During `find(x)`, recursively points all traversed nodes directly to the root:
  ```cpp
  if (parent[x] != x)
      parent[x] = find(parent[x]);
  ```
- **Union by Rank**: Always attaches the shallower tree under the root of the deeper tree, preventing tree skewing.
- **Amortized Complexity**: $O(\alpha(V))$ per operation, where $\alpha$ is the Inverse Ackermann function ($\alpha(V) \le 4$ for all practical universe sizes).

### 2. Edge Min-Heap (`MinHeap.h`)
A binary min-heap specialized for storing and extracting graph edges (`Edge { int u, v, w }`) in non-decreasing order of weight $w$.
- Complete binary tree maintained in a contiguous array (`heap[i]`, left child at `2i + 1`, right child at `2i + 2`, parent at `(i - 1) / 2`).
- Sublinear insertion and extraction via `heapifyUp()` and `heapifyDown()`.

### 3. Vertex Min-Priority Queue (`PriorityQueue.h`)
An array-based binary min-heap keyed on vertex priority (`Item { int vertex, priority }`), commonly used for maintaining tentative distances or cut weights.
- Enables greedy selection of the nearest unvisited vertex in graph exploration.

---

## 🧰 Operations & Complexity Analysis

| Data Structure | Operation | Method Signature | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **DSU** | Initialize | `DSU(int size)` | $O(V)$ | $O(V)$ |
| **DSU** | Find Representative | `int find(int x)` | $O(\alpha(V)) \approx O(1)$ | $O(V)$ recursion |
| **DSU** | Merge Sets | `bool unite(int x, int y)` | $O(\alpha(V)) \approx O(1)$ | $O(1)$ |
| **DSU** | Connectivity Query | `bool connected(int x, int y)` | $O(\alpha(V)) \approx O(1)$ | $O(1)$ |
| **MinHeap** | Insert Edge | `void insert(int u, int v, int w)` | $O(\log E)$ | $O(1)$ |
| **MinHeap** | Peek Minimum Edge | `void getMin(int& u, int& v, int& w)`| $O(1)$ | $O(1)$ |
| **MinHeap** | Extract Minimum Edge| `bool extractMin(int& u, int& v, int& w)` | $O(\log E)$ | $O(1)$ |
| **PriorityQueue** | Insert Vertex | `void insert(int vertex, int priority)` | $O(\log V)$ | $O(1)$ |
| **PriorityQueue** | Extract Min Vertex | `bool extractMin(int& vertex, int& priority)` | $O(\log V)$ | $O(1)$ |

---

## 🎯 Applications in Advanced Graph Algorithms

```text
+-----------------------+-----------------------------+------------------------------------+
| Algorithm             | Supporting Data Structure   | Role                               |
+-----------------------+-----------------------------+------------------------------------+
| Kruskal's MST         | DSU & MinHeap               | Min-weight edge ordering & cycle   |
|                       |                             | prevention across forest subsets.  |
| Dijkstra's Algorithm  | PriorityQueue               | Greedily extracts vertex with the  |
|                       |                             | smallest known distance.           |
| Prim's MST            | PriorityQueue               | Selects minimum crossing edge into |
|                       |                             | the growing spanning tree.         |
| Cycle Detection       | DSU                         | Detects cycles in undirected       |
|                       |                             | graphs in near-constant time.      |
+-----------------------+-----------------------------+------------------------------------+
```

---

## ▶️ Compilation & Execution

Compile and run the test driver using `g++` (C++11 or later):

```bash
g++ -std=c++11 main.cpp -o supporting_demo
./supporting_demo
```

### 📤 Sample Output

```text
=== DSU Demonstration ===
Connected(0, 2): 1
Connected(0, 4): 0
Connected(0, 4) after unite(2, 4): 1

=== MinHeap (Edges) Demonstration ===
Extracted edge: 1 - 2 (weight: 5)
Extracted edge: 0 - 1 (weight: 10)
Extracted edge: 2 - 3 (weight: 20)

=== PriorityQueue (Vertices) Demonstration ===
Extracted vertex: 1 (priority: 5)
Extracted vertex: 0 (priority: 15)
Extracted vertex: 2 (priority: 25)
```

---

## 🛡 Memory Management

- **DSU**: Deallocates integer tracking buffers via `delete[] parent` and `delete[] rankArr`.
- **MinHeap & PriorityQueue**: Allocates a fixed-capacity contiguous buffer on construction and frees it via `delete[] heap` in their respective destructors.
