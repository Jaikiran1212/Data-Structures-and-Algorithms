# Graph Representations (Python)

This directory provides clean, modular, and type-annotated Python implementations for the three primary data structures used to represent **Weighted Undirected Graphs**:

1. **Adjacency Matrix** ($O(V^2)$ space)
2. **Adjacency List** ($O(V + E)$ space, implemented using singly-linked lists)
3. **Edge List** ($O(E)$ space, implemented using an edge collection)

These implementations correspond directly to the C++ first-principles implementations in the parent folder, maintaining identical graph topologies, edge insertion order, and console display formats.

---

## 📁 Directory Structure

```text
python/
├── __init__.py                           # Package initializer exposing all classes
├── adjacency_matrix_representation.py    # 2D grid representation
├── adjacency_list_representation.py      # Array of linked lists representation
├── edge_list_representation.py           # Array of Edge objects representation
├── edge_list_representaion.py            # Alias forwarding for naming parity
└── README.md                             # Documentation & run instructions
```

---

## 🔬 In-Depth Representation Comparison

### 1. Adjacency Matrix (`adjacency_matrix_representation.py`)

Represents the graph using a 2D list `matrix[V][V]`.
- An entry `matrix[u][v] = w` indicates an edge of weight $w$ connecting vertices $u$ and $v$.
- A value of `0` denotes the absence of an edge.

```text
       0   1   2   3
  0 [  0  10  20   0 ]
  1 [ 10   0   0  30 ]
  2 [ 20   0   0   0 ]
  3 [  0  30   0   0 ]
```

- **Pros**:
  - $O(1)$ constant-time edge existence check (`has_edge(u, v)`) and weight retrieval.
  - Simple, matrix-based representation directly applicable to algebraic graph algorithms (e.g., Floyd-Warshall).
- **Cons**:
  - $O(V^2)$ space complexity regardless of the number of edges (wasteful for sparse graphs).
  - Iterating over neighbors of a vertex always takes $O(V)$ time.

---

### 2. Adjacency List (`adjacency_list_representation.py`)

Maintains an array (list) of singly linked lists (`adj[u] = Node(v, w, next)`), where each index $u$ points to the head of a linked list storing adjacent neighbors and weights.

```text
Vertex [0] -> (2, w=20) -> (1, w=10) -> None
Vertex [1] -> (3, w=30) -> (0, w=10) -> None
Vertex [2] -> (0, w=20) -> None
Vertex [3] -> (1, w=30) -> None
```

- **Pros**:
  - Optimal space complexity $O(V + E)$, making it the standard choice for sparse graphs ($E \ll V^2$).
  - Iterating through neighbors of vertex $u$ takes only $O(\text{deg}(u))$ time.
  - Edge insertion at the head is $O(1)$.
- **Cons**:
  - Checking if an edge $(u, v)$ exists requires traversing the linked list of $u$ ($O(\text{deg}(u))$ time).
  - Deleting an edge requires linked list traversal and pointer updates.

---

### 3. Edge List (`edge_list_representation.py`)

Stores all graph connections as a collection of discrete `Edge` records: `Edge(u, v, w)`.

```text
Index [0]: 0 - 1 : 10
Index [1]: 0 - 2 : 20
Index [2]: 1 - 3 : 30
```

- **Pros**:
  - Minimal space footprint: strictly $O(E)$.
  - Ideal for edge-centric algorithms such as Kruskal's Minimum Spanning Tree (which sorts edges by weight) and Bellman-Ford shortest paths.
  - Adding an edge is an $O(1)$ append.
- **Cons**:
  - Checking edge existence between $u$ and $v$ requires a linear scan over all edges ($O(E)$ time).
  - Finding all neighbors of a specific vertex $u$ requires scanning the entire edge list ($O(E)$ time).

---

## 📊 Complexity Comparison Matrix

| Operation | Adjacency Matrix | Adjacency List | Edge List |
|---|---|---|---|
| **Space Complexity** | $O(V^2)$ | $O(V + E)$ | $O(E)$ |
| **Add Edge** | $O(1)$ | $O(1)$ (prepend to head) | $O(1)$ (append) |
| **Edge Lookup $(u, v)$** | $O(1)$ | $O(\text{deg}(u))$ | $O(E)$ |
| **Delete Edge** | $O(1)$ | $O(\text{deg}(u))$ | $O(E)$ |
| **Iterate Neighbors of $u$** | $O(V)$ | $O(\text{deg}(u))$ | $O(E)$ |
| **Ideal For** | Dense graphs ($E \approx V^2$) | Sparse graphs ($E \ll V^2$) | Edge-centric algorithms (Kruskal, Bellman-Ford) |

---

## ▶️ Execution Guide

Run each script directly with `python3`:

### 1. Adjacency Matrix
```bash
python3 adjacency_matrix_representation.py
```
**Output:**
```text
0 10 20 0 
10 0 0 30 
20 0 0 0 
0 30 0 0 
```

### 2. Adjacency List
```bash
python3 adjacency_list_representation.py
```
**Output:**
```text
0: (2,20) (1,10) 
1: (3,30) (0,10) 
2: (0,20) 
3: (1,30) 
```

### 3. Edge List
```bash
python3 edge_list_representation.py
```
**Output:**
```text
0 - 1 : 10
0 - 2 : 20
1 - 3 : 30
```

---

## 🐍 Python Features & Implementation Notes

- **Object-Oriented Design**: Each representation is encapsulated inside its own class (`AdjacencyMatrix`, `AdjacencyList`, `EdgeList`).
- **Compatibility**: Both Pythonic `snake_case` methods (`insert_edge`, `remove_edge`, `has_edge`, `get_neighbors`) and C++ compatible `camelCase` aliases (`insertEdge`) are supported.
- **Type Annotations**: Fully typed with PEP 484 type hints (`typing.Optional`, `list`, `tuple`).
- **Garbage Collection**: Python automatically manages memory through reference counting and cyclic GC, removing the need for manual C++ `delete[]` calls while maintaining the same underlying data structure relationships.

