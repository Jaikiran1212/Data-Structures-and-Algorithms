"""
============================================================================
Algorithm: Prim's Minimum Spanning Tree (MST) (Python)
============================================================================

Overview:
  Prim's algorithm (also known as the Jarník-Prim algorithm) is a greedy
  graph algorithm that constructs an MST by continuously expanding a single
  growing tree one vertex at a time.

Core Strategy:
  1. Begin at an arbitrary starting vertex (e.g., vertex 0) and maintain:
     - in_mst[]: Boolean flags indicating vertices already in the growing tree.
     - key[]:    Minimum weight required to connect an external vertex to the MST.
     - parent[]: Predecessor of each vertex in the resulting spanning tree.
  2. Set key[start] = 0 and insert (start, 0) into a Min-Priority Queue.
  3. While the priority queue is not empty:
     a. Extract the vertex u with the smallest key value.
     b. If u is already included in the MST, skip it (lazy deletion).
     c. Mark in_mst[u] = True and add the edge (parent[u], u) to the MST.
     d. For every neighbor v of u:
        - If v is not yet in the MST and edge weight w(u, v) < key[v]:
          Update key[v] = w(u, v), parent[v] = u, and push (v, key[v]) into the PQ.
  4. Continue until all V vertices are in the MST (or the queue empties).

Mathematical Basis:
  The Cut Property: For any cut dividing graph vertices into two subsets,
  the minimum-weight edge crossing the cut must belong to some MST.

Complexity:
  - Time Complexity:  O((V + E) log V) using an adjacency list and binary heap.
  - Space Complexity: O(V + E) for adjacency linked lists and tracking arrays.

Zero External Dependencies:
  Implemented from scratch without standard library priority queue modules,
  demonstrating raw linked lists and custom binary heap mechanics.
============================================================================
"""

from typing import Optional


class PriorityQueue:
    """Array-based Binary Min-Priority Queue for graph vertices."""

    class Item:
        def __init__(self, vertex: int, priority: int) -> None:
            self.vertex: int = vertex
            self.priority: int = priority

    def __init__(self, capacity: int) -> None:
        self.capacity: int = capacity
        self.heap: list[Optional[PriorityQueue.Item]] = [None] * capacity
        self.size: int = 0

    def empty(self) -> bool:
        """Check if the priority queue contains no elements."""
        return self.size == 0

    def _swap(self, i: int, j: int) -> None:
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def _heapify_up(self, i: int) -> None:
        while i > 0:
            parent = (i - 1) // 2
            if self.heap[parent].priority <= self.heap[i].priority:
                break
            self._swap(parent, i)
            i = parent

    def _heapify_down(self, i: int) -> None:
        while True:
            smallest = i
            left = 2 * i + 1
            right = 2 * i + 2

            if left < self.size and self.heap[left].priority < self.heap[smallest].priority:
                smallest = left

            if right < self.size and self.heap[right].priority < self.heap[smallest].priority:
                smallest = right

            if smallest == i:
                break

            self._swap(i, smallest)
            i = smallest

    def insert(self, vertex: int, priority: int) -> bool:
        """Insert a vertex with its priority into the heap in O(log V) time."""
        if self.size == self.capacity:
            return False

        self.heap[self.size] = self.Item(vertex, priority)
        self._heapify_up(self.size)
        self.size += 1
        return True

    def extract_min(self) -> Optional[tuple[int, int]]:
        """Remove and return (vertex, priority) with the minimum priority in O(log V) time."""
        if self.empty():
            return None

        min_item = self.heap[0]
        self.heap[0] = self.heap[self.size - 1]
        self.heap[self.size - 1] = None
        self.size -= 1

        if not self.empty():
            self._heapify_down(0)

        return (min_item.vertex, min_item.priority)


class Node:
    """Represents a singly-linked list node in the adjacency list."""

    def __init__(self, vertex: int, weight: int, next_node: Optional["Node"] = None) -> None:
        self.vertex: int = vertex
        self.weight: int = weight
        self.next: Optional[Node] = next_node


class AdjacencyListGraph:
    """Graph representation using an adjacency list of linked nodes for Prim's algorithm."""

    def __init__(self, vertices: int) -> None:
        if vertices < 0:
            raise ValueError("Number of vertices cannot be negative.")
        self.vertices: int = vertices
        self.adj: list[Optional[Node]] = [None] * vertices

    def add_edge(self, u: int, v: int, weight: int) -> None:
        """Insert an undirected weighted edge by prepending to both adjacency lists."""
        if u < 0 or v < 0 or u >= self.vertices or v >= self.vertices:
            return

        a = Node(v, weight, self.adj[u])
        self.adj[u] = a

        b = Node(u, weight, self.adj[v])
        self.adj[v] = b

    # Alias to match C++ camelCase method name
    addEdge = add_edge

    def prim_mst(self, start: int = 0) -> None:
        """Grows the MST starting from vertex 'start' using a greedy cut approach."""
        if not (0 <= start < self.vertices):
            print("Invalid start vertex.")
            return

        inf = 10**9
        key: list[int] = [inf] * self.vertices
        parent: list[int] = [-1] * self.vertices
        in_mst: list[bool] = [False] * self.vertices

        # Generous capacity to support multiple updates per vertex (lazy deletion)
        pq = PriorityQueue(self.vertices * 10 + 1)

        key[start] = 0
        pq.insert(start, 0)

        total_weight = 0
        selected = 0

        while not pq.empty():
            item = pq.extract_min()
            if item is None:
                break
            u, _ = item

            # Lazy deletion check: skip if already included in MST
            if in_mst[u]:
                continue

            in_mst[u] = True
            selected += 1

            # If u is not the root, print the chosen MST edge connecting it
            if parent[u] != -1:
                print(f"{parent[u]} - {u} : {key[u]}")
                total_weight += key[u]

            # Relax incident edges to unvisited neighbors of u
            curr = self.adj[u]
            while curr is not None:
                v = curr.vertex
                w = curr.weight

                if not in_mst[v] and w < key[v]:
                    key[v] = w
                    parent[v] = u
                    pq.insert(v, key[v])

                curr = curr.next

        # Check connectivity (all V vertices must be reachable)
        if selected != self.vertices:
            print("Graph is disconnected; no spanning tree exists.")
        else:
            print(f"Total MST weight: {total_weight}")

    # Alias to match C++ camelCase method name
    primMST = prim_mst


def main() -> None:
    # Construct a sample graph with 5 vertices (0 through 4) and 7 undirected edges:
    graph = AdjacencyListGraph(5)

    graph.add_edge(0, 1, 2)  # Edge (0 - 1) weight 2
    graph.add_edge(0, 3, 6)  # Edge (0 - 3) weight 6
    graph.add_edge(1, 2, 3)  # Edge (1 - 2) weight 3
    graph.add_edge(1, 3, 8)  # Edge (1 - 3) weight 8
    graph.add_edge(1, 4, 5)  # Edge (1 - 4) weight 5
    graph.add_edge(2, 4, 7)  # Edge (2 - 4) weight 7
    graph.add_edge(3, 4, 9)  # Edge (3 - 4) weight 9

    # Run Prim's algorithm starting from vertex 0
    graph.prim_mst(0)


if __name__ == "__main__":
    main()
