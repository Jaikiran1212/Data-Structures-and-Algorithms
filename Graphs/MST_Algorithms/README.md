# Minimum Spanning Tree (MST) Algorithms (C++ & Python)

A comprehensive collection of the three classic **Minimum Spanning Tree (MST)** algorithms implemented from first principles in C++ and Python:
1. **Kruskal's Algorithm** ($O(E \log E)$)
2. **Prim's Algorithm** ($O((V + E) \log V)$)
3. **Borůvka's Algorithm** ($O(E \log V)$)

Consistent with this repository's architectural guidelines, all implementations avoid standard library abstractions (`std::priority_queue`, `std::vector`, `std::set`, Python `heapq`) in favor of custom arrays, custom binary heaps, custom linked lists, and Disjoint Set Union (DSU) structures.

---

## 📁 Directory Structure

```text
MST_Algorithms/
├── Kruskal's_algorithm.cpp   # Edge-centric greedy MST using Min-Heap and DSU (C++)
├── Prim's_algorithm.cpp      # Vertex-centric greedy MST using Adjacency List and Priority Queue (C++)
├── Boruvka's_algorithm.cpp   # Component-centric parallel MST using Edge List and DSU (C++)
├── python/                   # Python implementations
│   ├── __init__.py           # Package initializer
│   ├── kruskals_algorithm.py # Kruskal's algorithm implementation
│   ├── prims_algorithm.py    # Prim's algorithm implementation
│   ├── boruvkas_algorithm.py # Borůvka's algorithm implementation
│   └── README.md             # Python-specific documentation & run guide
└── README.md                 # Comparative analysis, theoretical foundations & run guide
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

### 1. Kruskal's Algorithm (`Kruskal's_algorithm.cpp`)
- **Strategy**: Sorts all graph edges globally by weight using a binary Min-Heap. Greedily adds the lightest edge to the MST if and only if it connects two disconnected components.
- **Cycle Prevention**: Uses **Disjoint Set Union (DSU)** with *Path Compression* and *Union by Rank*.
- **When to Use**: Ideal for sparse graphs ($E \approx V$) or when edges are already sorted or easily heapified.

### 2. Prim's Algorithm (`Prim's_algorithm.cpp`)
- **Strategy**: Grows a single continuous tree starting from an arbitrary vertex. At each step, examines all edges crossing from the tree to the non-tree vertices, greedily selecting the lightest crossing edge via an array-based Min-Priority Queue.
- **Representation**: Uses pointer-based **Adjacency Lists**.
- **When to Use**: Ideal for dense graphs ($E \approx V^2$), where vertex relaxation is fast and edge density is high.

### 3. Borůvka's Algorithm (`Boruvka's_algorithm.cpp`)
- **Strategy**: Starts with $V$ individual components. In each phase, every component concurrently identifies its cheapest outgoing edge. All chosen edges are simultaneously added to the MST via DSU.
- **Halving Invariant**: Each phase reduces the number of components by at least half, guaranteeing completion in at most $\lceil \log_2 V \rceil$ phases.
- **When to Use**: Ideal for parallel, multithreaded, and distributed computing architectures where components can choose edges without locking.

---

## 📊 Comprehensive Comparison Matrix

| Feature | Kruskal's Algorithm | Prim's Algorithm | Borůvka's Algorithm |
|---|---|---|---|
| **Underlying Philosophy** | Edge-centric (Cycle Property) | Vertex-centric (Cut Property) | Component-centric (Cut Property) |
| **Growth Pattern** | Grows an acyclic forest into a tree | Grows a single tree outwards | Merges multiple trees in parallel |
| **Graph Representation** | Edge List | Adjacency List | Edge List |
| **Primary Data Structure** | Min-Heap + DSU | Min-Priority Queue | DSU + Cheapest Edge Array |
| **Time Complexity** | $O(E \log E)$ or $O(E \log V)$ | $O((V + E) \log V)$ | $O(E \log V)$ |
| **Space Complexity** | $O(V + E)$ | $O(V + E)$ | $O(V + E)$ |
| **Optimal Graph Density** | Sparse ($E \ll V^2$) | Dense ($E \approx V^2$) | Any (especially parallel/distributed) |
| **Disconnected Graph Handling** | Detects via `selected != V - 1` | Detects via `selected != V` | Detects via `components != 1` |

---

## ▶️ Compilation & Execution

### C++

Compile and run each algorithm using `g++` (C++11 or later):

#### 1. Kruskal's Algorithm
```bash
g++ -std=c++11 "Kruskal's_algorithm.cpp" -o kruskal
./kruskal
```
**Sample Output:**
```text
MST edges:
2 - 3 : 4
0 - 3 : 5
0 - 1 : 10
Total MST weight: 19
```

#### 2. Prim's Algorithm
```bash
g++ -std=c++11 "Prim's_algorithm.cpp" -o prim
./prim
```
**Sample Output:**
```text
0 - 1 : 2
1 - 2 : 3
1 - 4 : 5
0 - 3 : 6
Total MST weight: 16
```

#### 3. Borůvka's Algorithm
```bash
g++ -std=c++11 "Boruvka's_algorithm.cpp" -o boruvka
./boruvka
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

### Python

Execute directly from the `MST_Algorithms` directory:

```bash
# 1. Kruskal's Algorithm
python3 python/kruskals_algorithm.py

# 2. Prim's Algorithm
python3 python/prims_algorithm.py

# 3. Borůvka's Algorithm
python3 python/boruvkas_algorithm.py
```

Outputs match the C++ console results identically. See [python/README.md](python/README.md) for detailed Python documentation.

---

## 🛡 Memory Management (RAII)

Every program includes thorough destructor implementations:
- **DSU**: Deallocates `parent` and `rankArr` with `delete[]`.
- **Heaps & Priority Queues**: Deallocates internal array storage via `delete[] heap`.
- **Graph Containers**: Recursively frees linked list nodes (`delete temp`) and dynamic edge arrays (`delete[] edgeList`, `delete[] adj`).
- **Traversal Buffers**: Frees all temporary key, parent, and component tracking arrays at method completion.
