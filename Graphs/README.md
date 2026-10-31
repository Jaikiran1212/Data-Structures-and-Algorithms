# Graph ADT Implementation (C++)

A robust, low-level implementation of an **Undirected Weighted Graph Abstract Data Type (ADT)** using custom **Adjacency Lists** in C++.

This implementation avoids high-level STL containers (`std::vector`, `std::list`) in favor of direct pointer-based linked lists, giving complete transparency over memory allocation, pointer manipulation, and graph traversal fundamentals.

---

## 📁 Directory Structure

```text
Graphs/
├── Graph_implementation_ADT.cpp   # Complete Graph ADT class & demo
└── README.md                      # Documentation & usage guide
```

---

## ⚙️ Data Structure & Internal Representation

The graph is represented using an **Adjacency List** composed of dynamically allocated node chains.

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

## 🧰 Operations Supported

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

Compile using `g++` with C++11 or later:

```bash
g++ -std=c++11 Graph_implementation_ADT.cpp -o graph_adt
./graph_adt
```

---

## 📤 Sample Output

Executing the demo script yields:

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

- **Manual Memory Management**: Features a complete destructor (`~Graph()`) that traverses all adjacency lists, deallocating each `Node` via `delete`, followed by `delete[] adj` to prevent memory leaks.
- **Bounds Checking**: Validates index ranges for all node lookups and edge insertions to prevent segmentation faults.
- **Undirected Invariance**: Adding/removing an edge $(u, v)$ symmetrically updates both `adj[u]` and `adj[v]`.
