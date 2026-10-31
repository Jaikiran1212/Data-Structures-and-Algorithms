# Graph Representations (C++)

This directory demonstrates the three primary data structures used to store and manipulate **Weighted Undirected Graphs** in C++ from first principles:
1. **Adjacency Matrix** ($O(V^2)$ space)
2. **Adjacency List** ($O(V + E)$ space)
3. **Edge List** ($O(E)$ space)

Each representation is built with raw dynamic pointers without external STL containers (`std::vector`, `std::list`), featuring full destructors to guarantee zero memory leaks.

---

## 📁 Directory Structure

```text
Graph_representation/
├── adjacency_matrix_representation.cpp   # 2D array representation
├── adjacency_list_representation.cpp     # Array of linked lists representation
├── edge_list_representaion.cpp           # Array of edge structures representation
└── README.md                             # Comparative analysis & run guide
```

---

## 🔬 In-Depth Representation Comparison

### 1. Adjacency Matrix (`adjacency_matrix_representation.cpp`)

Represents graph connectivity using a dynamically allocated 2D square matrix `matrix[V][V]`.
- An entry `matrix[u][v] = w` signifies a weighted edge between vertices $u$ and $v$.
- A value of `0` denotes the absence of an edge.

```text
       0   1   2   3
  0 [  0  10  20   0 ]
  1 [ 10   0   0  30 ]
  2 [ 20   0   0   0 ]
  3 [  0  30   0   0 ]
```

- **Pros**: $O(1)$ constant time edge lookups and updates.
- **Cons**: Consumes $O(V^2)$ memory regardless of edge density; iterating over neighbors always takes $O(V)$.

---

### 2. Adjacency List (`adjacency_list_representation.cpp`)

Maintains an array of singly linked lists (`Node** adj`), where each index $u$ stores a chain of adjacent neighbors and edge weights.

```text
Vertex [0] -> (1, w=10) -> (2, w=20) -> NULL
Vertex [1] -> (0, w=10) -> (3, w=30) -> NULL
Vertex [2] -> (0, w=20) -> NULL
Vertex [3] -> (1, w=30) -> NULL
```

- **Pros**: Space-efficient ($O(V + E)$), optimal for sparse graphs; iterating over neighbors takes $O(\text{deg}(u))$.
- **Cons**: Edge existence check $(u, v)$ requires traversing the linked list ($O(\text{deg}(u))$ time).

---

### 3. Edge List (`edge_list_representaion.cpp`)

Stores all graph connections as an array of discrete `Edge` records: `struct Edge { int u, v, w; };`.

```text
Index [0]: 0 - 1 : 10
Index [1]: 0 - 2 : 20
Index [2]: 1 - 3 : 30
```

- **Pros**: Minimal space ($O(E)$); optimal for algorithms that iterate through edges globally (e.g., Kruskal's MST, Bellman-Ford).
- **Cons**: Querying edge presence or finding neighbors of a specific vertex requires scanning the entire edge array ($O(E)$).

---

## 📊 Complexity Comparison Matrix

| Operation | Adjacency Matrix | Adjacency List | Edge List |
|---|---|---|---|
| **Space Complexity** | $O(V^2)$ | $O(V + E)$ | $O(E)$ |
| **Add Edge** | $O(1)$ | $O(1)$ (prepend) | $O(1)$ (append) |
| **Edge Lookup $(u, v)$** | $O(1)$ | $O(\text{deg}(u))$ | $O(E)$ |
| **Delete Edge** | $O(1)$ | $O(\text{deg}(u))$ | $O(E)$ |
| **Iterate Neighbors of $u$** | $O(V)$ | $O(\text{deg}(u))$ | $O(E)$ |
| **Ideal For** | Dense graphs ($E \approx V^2$) | Sparse graphs ($E \ll V^2$) | Edge-centric algorithms (Kruskal, Bellman-Ford) |

---

## ▶️ Compilation & Execution

Compile and run using `g++` (C++11 or later):

### 1. Adjacency Matrix
```bash
g++ -std=c++11 adjacency_matrix_representation.cpp -o adj_matrix
./adj_matrix
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
g++ -std=c++11 adjacency_list_representation.cpp -o adj_list
./adj_list
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
g++ -std=c++11 edge_list_representaion.cpp -o edge_list
./edge_list
```
**Output:**
```text
0 - 1 : 10
0 - 2 : 20
1 - 3 : 30
```

---

## 🛡 Memory Management

All implementations follow strict RAII conventions:
- **Matrix**: Iteratively frees row arrays `delete[] matrix[i]` before deallocating `delete[] matrix`.
- **List**: Iteratively traverses and deallocates every linked `Node` with `delete temp` before `delete[] adj`.
- **Edge List**: Frees contiguous edge buffer via `delete[] edges`.
