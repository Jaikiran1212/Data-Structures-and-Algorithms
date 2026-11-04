# Graph Data Structures & Algorithms (C++)

A comprehensive collection of **Graph Data Structure** implementations in C++, focusing on low-level memory efficiency, pointer manipulation, representation paradigms, fundamental traversal algorithms, supporting priority structures, and Minimum Spanning Tree (MST) algorithms.

All implementations avoid external STL containers (`std::vector`, `std::list`, `std::stack`, `std::queue`, `std::priority_queue`, `std::set`) in favor of direct dynamic arrays and linked lists, with full destructors to guarantee zero memory leaks.

---

## 📁 Directory Structure

```text
Graphs/
├── Graph_implementation_ADT.cpp   # Full Graph ADT with insertion, deletion & search
├── README.md                      # Primary graphs documentation
├── Graph_representation/          # Core representation techniques
│   ├── adjacency_matrix_representation.cpp   # 2D array representation (O(V^2))
│   ├── adjacency_list_representation.cpp     # Linked lists array representation (O(V + E))
│   ├── edge_list_representaion.cpp           # Edge array representation (O(E))
│   └── README.md                             # Comparative analysis & benchmarks
├── Graph_traversals/              # Search & traversal algorithms
│   ├── BFS_and_DFS.cpp                       # Iterative BFS and DFS using custom buffers
│   ├── python/
│   │   └── BFS_and_DFS.py                    # Python iterative BFS and DFS
│   └── README.md                             # Traversal guide & algorithmic comparison
├── Supporting_Data_Structures/    # Specialized structures for advanced algorithms
│   ├── DSU.h                                 # Disjoint Set Union (Path Compression + Rank)
│   ├── MinHeap.h                             # Array-based Edge Min-Heap (Kruskal)
│   ├── PriorityQueue.h                       # Array-based Vertex Min-Priority Queue (Dijkstra)
│   ├── main.cpp                              # Test harness & demonstration
│   └── README.md                             # Algorithmic use cases & analysis
└── MST_Algorithms/                # Minimum Spanning Tree algorithms
    ├── Kruskal's_algorithm.cpp               # Kruskal's MST using Min-Heap and DSU
    ├── Prim's_algorithm.cpp                  # Prim's MST using Adjacency List and Priority Queue
    ├── Boruvka's_algorithm.cpp               # Boruvka's MST using Edge List and DSU
    └── README.md                             # Comparative analysis & theoretical guide
```

---

## 📑 Contents

### 1. Graph ADT Implementation (`Graph_implementation_ADT.cpp`)
A full-featured Undirected Weighted Graph ADT implementing vertex degree inspections, dynamic edge insertion, edge deletion (relational unlinking and memory deallocation), and adjacency queries.

### 2. Graph Representations ([`Graph_representation/`](./Graph_representation))
A dedicated comparative module benchmarking the three standard graph storage formats:
- **Adjacency Matrix**: Fast $O(1)$ lookups, optimal for dense graphs.
- **Adjacency List**: Space-efficient $O(V + E)$, optimal for sparse graphs.
- **Edge List**: Compact $O(E)$ edge storage, optimal for algorithms like Kruskal's or Bellman-Ford.

### 3. Graph Traversals ([`Graph_traversals/`](./Graph_traversals))
Iterative implementations of the two foundational graph exploration algorithms:
- **Depth-First Search (DFS)**: Deep branch exploration utilizing a dynamic LIFO stack.
- **Breadth-First Search (BFS)**: Radial level-order exploration utilizing a dynamic FIFO queue.
- Python equivalents are available in [`Graph_traversals/python/`](./Graph_traversals/python).

### 4. Supporting Data Structures ([`Supporting_Data_Structures/`](./Supporting_Data_Structures))
Auxiliary data structures designed to power advanced greedy and shortest-path graph algorithms:
- **DSU**: Nearly $O(1)$ amortized subset merging and cycle detection for Kruskal's MST.
- **MinHeap**: $O(\log E)$ edge extraction for MST edge processing.
- **PriorityQueue**: $O(\log V)$ vertex extraction for Dijkstra's and Prim's algorithms.

### 5. Minimum Spanning Tree Algorithms ([`MST_Algorithms/`](./MST_Algorithms))
Complete implementations of the three classic greedy MST algorithms:
- **Kruskal's Algorithm**: Global edge sorting via Min-Heap with DSU cycle avoidance ($O(E \log E)$).
- **Prim's Algorithm**: Vertex-centric tree expansion via custom Priority Queue ($O((V + E) \log V)$).
- **Borůvka's Algorithm**: Multi-component parallel edge selection via DSU ($O(E \log V)$).

---

## ⚙️ Graph ADT Data Structure

The Graph ADT uses an **Adjacency List** composed of dynamically allocated node chains:

```text
Vertex [0] -> (1, w=10) -> (2, w=20) -> NULL
Vertex [1] -> (0, w=10) -> (3, w=30) -> NULL
Vertex [2] -> (0, w=20) -> (4, w=40) -> NULL
Vertex [3] -> (1, w=30) -> NULL
Vertex [4] -> (2, w=40) -> NULL
```

### Node Structure
```cpp
struct Node {
    int vertex;  // Target vertex index
    int weight;  // Weight of the incident edge
    Node* next;  // Pointer to the next adjacent node

    Node(int v, int w) : vertex(v), weight(w), next(nullptr) {}
};
```

---

## 🧰 Graph ADT Operations Supported

| Method | Signature | Description | Time Complexity |
|---|---|---|---|
| **Constructor** | `Graph(int vertices)` | Initializes adjacency list array of size $V$ | $O(V)$ |
| **Number of Vertices** | `int numVertices()` | Returns total vertices count $V$ | $O(1)$ |
| **Insert Edge** | `void insertEdge(int u, int v, int w)` | Adds an undirected weighted edge between $u$ and $v$ | $O(1)$ |
| **Erase Edge** | `void eraseEdge(int u, int v)` | Removes edge between $u$ and $v$ and deallocates nodes | $O(\text{deg}(u) + \text{deg}(v))$ |
| **Check Adjacency** | `bool isAdjacentTo(int u, int v)` | Checks if an edge exists connecting $u$ and $v$ | $O(\text{deg}(u))$ |
| **Incident Vertices** | `void incidentVertices(int u)` | Prints all adjacent neighbors of vertex $u$ | $O(\text{deg}(u))$ |
| **Display** | `void display()` | Prints the full adjacency list of the graph | $O(V + E)$ |
| **Destructor** | `~Graph()` | Frees all dynamically allocated nodes and pointer array | $O(V + E)$ |

> **Space Complexity:** $O(V + E)$ where $V$ is vertices and $E$ is edges.

---

## ▶️ Compilation & Execution

### Graph ADT
```bash
g++ -std=c++11 Graph_implementation_ADT.cpp -o graph_adt
./graph_adt
```

### Graph Representations
```bash
cd Graph_representation
g++ -std=c++11 adjacency_matrix_representation.cpp -o adj_mat
g++ -std=c++11 adjacency_list_representation.cpp -o adj_list
g++ -std=c++11 edge_list_representaion.cpp -o edge_list
```
See [`Graph_representation/README.md`](./Graph_representation/README.md) for detailed analysis and run guides.

### Graph Traversals (BFS & DFS)
```bash
cd Graph_traversals
g++ -std=c++11 BFS_and_DFS.cpp -o bfs_dfs
./bfs_dfs
```
See [`Graph_traversals/README.md`](./Graph_traversals/README.md) for traversal mechanics and tracing.

### Supporting Data Structures (DSU, MinHeap, PriorityQueue)
```bash
cd Supporting_Data_Structures
g++ -std=c++11 main.cpp -o supporting_demo
./supporting_demo
```
See [`Supporting_Data_Structures/README.md`](./Supporting_Data_Structures/README.md) for individual component breakdowns.

### Minimum Spanning Tree (MST) Algorithms
```bash
cd MST_Algorithms
g++ -std=c++11 "Kruskal's_algorithm.cpp" -o kruskal
g++ -std=c++11 "Prim's_algorithm.cpp" -o prim
g++ -std=c++11 "Boruvka's_algorithm.cpp" -o boruvka
```
See [`MST_Algorithms/README.md`](./MST_Algorithms/README.md) for algorithm comparisons and traces.

---

## 📤 Sample Output (Graph ADT)

```text
Graph:
0: (2,20) (1,10) 
1: (3,30) (0,10) 
2: (4,40) (0,20) 
3: (1,30) 
4: (2,40) 

Adjacent (0,1): Yes
Incident vertices of 0: 2 1 

After deleting edge (0,1):
0: (2,20) 
1: (3,30) 
2: (4,40) (0,20) 
3: (1,30) 
4: (2,40) 
```

---

## 💡 Key Highlights

- **Manual Memory Management**: Complete destructors in all graph modules systematically deallocate dynamic arrays and linked lists to prevent memory leaks.
- **Bounds Checking**: Validates index ranges for all node lookups and edge insertions to prevent segmentation faults.
- **Undirected Invariance**: Adding/removing an edge $(u, v)$ symmetrically updates both `adj[u]` and `adj[v]`.
