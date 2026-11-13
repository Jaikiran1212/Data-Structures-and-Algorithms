# Minimum Spanning Tree (MST) Algorithms (Python)

A comprehensive collection of the three classic **Minimum Spanning Tree (MST)** algorithms implemented from first principles in Python:

1. **Kruskal's Algorithm** ($O(E \log E)$ or $O(E \log V)$)
2. **Prim's Algorithm** ($O((V + E) \log V)$)
3. **Borůvka's Algorithm** ($O(E \log V)$)

Consistent with this repository's architectural philosophy, all implementations avoid standard library abstractions (`heapq`, `queue.PriorityQueue`, `collections`) in favor of custom binary heaps, custom Disjoint Set Union (DSU) structures with Path Compression and Union by Rank, and custom singly-linked list node chains.

---

## 📁 Directory Structure

```text
python/
├── __init__.py               # Package initializer exposing MST classes and helpers
├── kruskals_algorithm.py     # Edge-centric greedy MST using Min-Heap and DSU
├── prims_algorithm.py        # Vertex-centric greedy MST using Adjacency List and Min-Priority Queue
├── boruvkas_algorithm.py     # Component-centric parallel MST using Edge List and DSU
├── Kruskal's_algorithm.py    # Forwarding alias matching C++ filename
├── Prim's_algorithm.py       # Forwarding alias matching C++ filename
├── Boruvka's_algorithm.py    # Forwarding alias matching C++ filename
└── README.md                 # Documentation, algorithmic comparison & run guide
```

---

## 🌳 What is a Minimum Spanning Tree?

Given a connected, undirected, edge-weighted graph $G = (V, E)$, a **Spanning Tree** is an acyclic subgraph connecting all $V$ vertices using exactly $V - 1$ edges.

A **Minimum Spanning Tree (MST)** is a spanning tree whose total sum of edge weights is minimized:

$$\text{Weight}(T) = \sum_{e \in T} w(e) \quad \text{is minimal}$$

### Fundamental Properties
- **The Cut Property**: For any cut $(S, V \setminus S)$ dividing the graph vertices into two disjoint sets, the minimum-weight edge crossing the cut belongs to an MST. (Used by **Prim** and **Borůvka**).
- **The Cycle Property**: For any cycle in the graph, the edge with the strictly largest weight cannot belong to any MST. (Used by **Kruskal**).

---

## 🔬 In-Depth Algorithm Breakdown

### 1. Kruskal's Algorithm (`kruskals_algorithm.py`)
- **Strategy**: Sorts all graph edges globally by weight using a custom binary `MinHeap`. Greedily adds the lightest edge to the MST if and only if its endpoints belong to different components.
- **Cycle Prevention**: Uses a custom **Disjoint Set Union (DSU)** with *Path Compression* and *Union by Rank*.
- **When to Use**: Ideal for sparse graphs ($E \approx V$) or when edges are already sorted or easily heapified.

### 2. Prim's Algorithm (`prims_algorithm.py`)
- **Strategy**: Grows a single continuous tree starting from an arbitrary vertex. At each step, examines all edges crossing from the tree to the non-tree vertices, greedily selecting the lightest crossing edge via an array-based binary `PriorityQueue` with lazy deletion.
- **Representation**: Uses pointer-based singly linked `Node` lists.
- **When to Use**: Ideal for dense graphs ($E \approx V^2$), where vertex relaxation is fast and edge density is high.

### 3. Borůvka's Algorithm (`boruvkas_algorithm.py`)
- **Strategy**: Starts with $V$ individual components. In each phase, every component concurrently identifies its cheapest outgoing edge. All chosen edges are simultaneously added to the MST via DSU.
- **Halving Invariant**: Each phase reduces the number of components by at least half, guaranteeing completion in at most $\lceil \log_2 V \rceil$ phases.
- **When to Use**: Ideal for parallel, multithreaded, and distributed computing architectures where components can choose edges concurrently without locking.

---

## 📊 Comprehensive Comparison Matrix

| Feature | Kruskal's Algorithm | Prim's Algorithm | Borůvka's Algorithm |
|---|---|---|---|
| **Underlying Philosophy** | Edge-centric (Cycle Property) | Vertex-centric (Cut Property) | Component-centric (Cut Property) |
| **Growth Pattern** | Grows an acyclic forest into a tree | Grows a single tree outwards | Merges multiple trees in parallel |
| **Graph Representation** | Edge List | Adjacency List (Linked List) | Edge List |
| **Primary Data Structure** | Custom Min-Heap + DSU | Custom Min-Priority Queue | DSU + Cheapest Edge Array |
| **Time Complexity** | $O(E \log E)$ or $O(E \log V)$ | $O((V + E) \log V)$ | $O(E \log V)$ |
| **Space Complexity** | $O(V + E)$ | $O(V + E)$ | $O(V + E)$ |
| **Optimal Graph Density** | Sparse ($E \ll V^2$) | Dense ($E \approx V^2$) | Any (especially parallel/distributed) |
| **Disconnected Graph Handling** | Detects via `selected != V - 1` | Detects via `selected != V` | Detects via `components != 1` |

---

## ▶️ Execution Guide

Run each algorithm directly using `python3`:

### 1. Kruskal's Algorithm
```bash
python3 kruskals_algorithm.py
```
**Sample Output:**
```text
MST edges:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10
Total MST weight: 19
```

### 2. Prim's Algorithm
```bash
python3 prims_algorithm.py
```
**Sample Output:**
```text
0 - 1 : 2
1 - 2 : 3
1 - 4 : 5
0 - 3 : 6
Total MST weight: 16
```

### 3. Borůvka's Algorithm
```bash
python3 boruvkas_algorithm.py
```
**Sample Output:**
```text
MST edges:
0 - 3 : 5
0 - 1 : 10
2 - 3 : 4
Total MST weight: 19
```

---

## 🐍 Python Implementation Notes

- **Zero Standard Library Heaps/Queues**: Implements `MinHeap` and `PriorityQueue` directly on array buffers with explicit `_heapify_up` and `_heapify_down` methods.
- **Disjoint Set Union (DSU)**: Full recursive Path Compression flattens trees to near constant time ($O(\alpha(V))$), while Union by Rank prevents unbalanced trees.
- **C++ Parity**: Supports both Pythonic `snake_case` methods (`add_edge`, `kruskal_mst`, `prim_mst`, `boruvka_mst`) and C++ `camelCase` aliases (`addEdge`, `kruskalMST`, `primMST`, `boruvkaMST`).
- **Filenames**: Provides standard PEP 8 module names (`kruskals_algorithm.py`, etc.) as well as alias files preserving the C++ filenames (`Kruskal's_algorithm.py`, etc.) for seamless cross-language workflows.
