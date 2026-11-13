"""
============================================================================
Algorithm: Kruskal's Minimum Spanning Tree (MST) (Python)
============================================================================

Overview:
  Kruskal's algorithm is a greedy algorithm that finds a Minimum Spanning
  Tree (MST) for a connected, undirected, edge-weighted graph.

Core Strategy:
  1. Treat every vertex as an independent tree (a forest of V trees).
  2. Insert all edges into a Min-Heap (or sort them) in non-decreasing order
     of edge weight.
  3. Repeatedly extract the minimum-weight edge (u, v).
  4. Using a Disjoint Set Union (DSU / Union-Find) data structure:
     - If u and v belong to different connected components, adding this edge
       will NOT form a cycle. Add the edge to the MST and unite the two components.
     - If u and v already belong to the same component, discard the edge to
       prevent a cycle.
  5. Terminate when (V - 1) edges have been added, or all edges are exhausted.

Complexity:
  - Time Complexity:  O(E log E) or O(E log V) to extract edges from the Min-Heap,
                      plus O(E * alpha(V)) for DSU operations.
  - Space Complexity: O(V + E) to store the DSU arrays and Min-Heap edges.

Zero External Dependencies:
  Implemented from first principles with custom Disjoint Set Union (DSU) and
  a custom Binary Min-Heap without standard library queue or heap modules.
============================================================================
"""

from typing import Optional


class DSU:
    """Disjoint Set Union (DSU) with Path Compression and Union by Rank."""

    def __init__(self, n: int) -> None:
        if n < 0:
            raise ValueError("Number of elements cannot be negative.")
        self.n: int = n
        self.parent: list[int] = list(range(n))
        self.rank: list[int] = [0] * n

    def find(self, x: int) -> int:
        """Find the root representative of the set containing x with Path Compression."""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])  # Recursive path compression
        return self.parent[x]

    def unite(self, x: int, y: int) -> bool:
        """Merge the sets containing x and y.

        Returns False if x and y are already in the same set (cycle detected),
        True otherwise.
        """
        root_x = self.find(x)
        root_y = self.find(y)

        if root_x == root_y:
            return False

        # Union by rank: attach shallower tree beneath the deeper tree
        if self.rank[root_x] < self.rank[root_y]:
            self.parent[root_x] = root_y
        elif self.rank[root_x] > self.rank[root_y]:
            self.parent[root_y] = root_x
        else:
            self.parent[root_y] = root_x
            self.rank[root_x] += 1

        return True


class Edge:
    """Represents a weighted undirected edge connecting vertex u and vertex v."""

    def __init__(self, u: int, v: int, weight: int) -> None:
        self.u: int = u
        self.v: int = v
        self.weight: int = weight

    def __repr__(self) -> str:
        return f"Edge({self.u}, {self.v}, {self.weight})"


class MinHeap:
    """Binary Min-Heap for Edge structures ordered by edge weight."""

    def __init__(self, capacity: int) -> None:
        self.capacity: int = capacity
        self.heap: list[Optional[Edge]] = [None] * capacity
        self.size: int = 0

    def empty(self) -> bool:
        """Check if the heap is empty."""
        return self.size == 0

    def _swap(self, i: int, j: int) -> None:
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def _heapify_up(self, i: int) -> None:
        while i > 0:
            parent = (i - 1) // 2
            if self.heap[parent].weight <= self.heap[i].weight:
                break
            self._swap(parent, i)
            i = parent

    def _heapify_down(self, i: int) -> None:
        while True:
            smallest = i
            left = 2 * i + 1
            right = 2 * i + 2

            if left < self.size and self.heap[left].weight < self.heap[smallest].weight:
                smallest = left

            if right < self.size and self.heap[right].weight < self.heap[smallest].weight:
                smallest = right

            if smallest == i:
                break

            self._swap(i, smallest)
            i = smallest

    def insert(self, e: Edge) -> bool:
        """Insert an edge into the min-heap in O(log E) time."""
        if self.size == self.capacity:
            return False

        self.heap[self.size] = e
        self._heapify_up(self.size)
        self.size += 1
        return True

    def extract_min(self) -> Optional[Edge]:
        """Remove and return the minimum weight edge in O(log E) time."""
        if self.empty():
            return None

        min_edge = self.heap[0]
        self.heap[0] = self.heap[self.size - 1]
        self.heap[self.size - 1] = None
        self.size -= 1

        if not self.empty():
            self._heapify_down(0)

        return min_edge


class EdgeListGraph:
    """Graph representation using an edge list for Kruskal's algorithm."""

    def __init__(self, vertices: int, edges: int) -> None:
        if vertices < 0 or edges < 0:
            raise ValueError("Vertices and edges cannot be negative.")
        self.vertices: int = vertices
        self.total_edges: int = edges
        self.edge_list: list[Optional[Edge]] = [None] * edges
        self._current_index: int = 0

    def add_edge(self, u: int, v: int, weight: int, index: Optional[int] = None) -> None:
        """Add an edge at a specified index or append automatically."""
        edge = Edge(u, v, weight)
        if index is not None:
            if 0 <= index < self.total_edges:
                self.edge_list[index] = edge
        else:
            if self._current_index < self.total_edges:
                self.edge_list[self._current_index] = edge
                self._current_index += 1

    # Alias to match C++ camelCase method name
    addEdge = add_edge

    def kruskal_mst(self) -> None:
        """Execute Kruskal's algorithm to compute and print the Minimum Spanning Tree."""
        # Step 1: Push all edges into the Min-Heap
        heap = MinHeap(self.total_edges)
        for edge in self.edge_list:
            if edge is not None:
                heap.insert(edge)

        # Step 2: Initialize DSU with V disjoint sets
        dsu = DSU(self.vertices)
        total_weight = 0
        selected = 0

        print("MST edges:")

        # Step 3: Process edges in ascending order of weight
        while not heap.empty() and selected < self.vertices - 1:
            e = heap.extract_min()
            if e is None:
                break

            # Step 4: If uniting endpoints succeeds, the edge connects two
            # disjoint components without creating a cycle.
            if dsu.unite(e.u, e.v):
                print(f"{e.u} - {e.v} : {e.weight}")
                total_weight += e.weight
                selected += 1

        # Step 5: Check if graph was disconnected (less than V - 1 edges selected)
        if selected != self.vertices - 1:
            print("Graph is disconnected; no spanning tree exists.")
        else:
            print(f"Total MST weight: {total_weight}")

    # Alias to match C++ camelCase method name
    kruskalMST = kruskal_mst


def main() -> None:
    # Construct a sample graph with 4 vertices and 5 edges:
    # Vertices: 0, 1, 2, 3
    graph = EdgeListGraph(4, 5)

    graph.add_edge(0, 1, 10, 0)  # Edge (0 - 1) weight 10
    graph.add_edge(0, 2, 6, 1)   # Edge (0 - 2) weight 6
    graph.add_edge(0, 3, 5, 2)   # Edge (0 - 3) weight 5
    graph.add_edge(1, 3, 15, 3)  # Edge (1 - 3) weight 15
    graph.add_edge(2, 3, 4, 4)   # Edge (2 - 3) weight 4

    # Run Kruskal's algorithm
    graph.kruskal_mst()


if __name__ == "__main__":
    main()
