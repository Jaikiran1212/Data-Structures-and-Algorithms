# Graph Data Structures & Algorithms (C++)

A comprehensive collection of **Graph Data Structure** implementations in C++, focusing on low-level memory efficiency, pointer manipulation, and foundational representation paradigms.

All implementations avoid external STL containers (`std::vector`, `std::list`) in favor of direct dynamic arrays and linked lists, with full destructors to guarantee zero memory leaks.

---

## 📁 Directory Structure

```text
Graphs/
├── Graph_implementation_ADT.cpp   # Full Graph ADT with insertion, deletion & search
├── README.md                      # Primary graphs documentation
└── Graph_representation/          # Core representation techniques
    ├── adjacency_matrix_representation.cpp   # 2D array representation (O(V^2))
    ├── adjacency_list_representation.cpp     # Linked lists array representation (O(V + E))
    ├── edge_list_representaion.cpp           # Edge array representation (O(E))
    └── README.md                             # Comparative analysis & benchmarks
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
Navigate to [`Graph_representation/`](./Graph_representation) or compile directly:
```bash
cd Graph_representation
g++ -std=c++11 adjacency_matrix_representation.cpp -o adj_mat
g++ -std=c++11 adjacency_list_representation.cpp -o adj_list
g++ -std=c++11 edge_list_representaion.cpp -o edge_list
```
See [`Graph_representation/README.md`](./Graph_representation/README.md) for detailed analysis and run guides.

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
