"""
============================================================================
Algorithm: Boruvka's Minimum Spanning Tree (MST) (Python)
============================================================================

Overview:
  Boruvka's algorithm is the oldest known MST algorithm, published in 1926
  by Czech mathematician Otakar Boruvka for the electrification of Moravia.
  It constructs an MST by repeatedly finding and adding the cheapest outgoing
  edge for every connected component simultaneously.

Core Strategy:
  1. Begin with V disconnected components (every vertex is its own component).
  2. In each phase:
     a. Initialize a cheapest[] array with -1 for all components.
     b. Iterate through all E edges:
        - Determine the component IDs of both endpoints using DSU.
        - If they belong to different components, check if this edge is cheaper
          than the current known cheapest edge for either component. If so, update cheapest[].
     c. For each component, retrieve its cheapest outgoing edge. If this edge
        connects two distinct components in the DSU, unite them, add the edge to the
        MST, and decrement the component count.
  3. Repeat until only 1 component remains (or no new edges can be added).

Halving Invariant & Complexity:
  - Each phase reduces the number of components by at least half (components <= C / 2).
  - Therefore, there are at most ceil(log2 V) phases.
  - In each phase, all E edges are inspected in O(E * alpha(V)) time.
  - Total Time Complexity:  O(E log V)
  - Total Space Complexity: O(V + E) for the edge array, DSU, and cheapest tracker.

Historical & Practical Significance:
  Boruvka's algorithm is inherently parallelizable: every component can find its
  cheapest outgoing edge concurrently without inter-component locking, making it
  the foundation of state-of-the-art parallel and distributed MST algorithms.
============================================================================
"""

from typing import Optional


class Edge:
    """Represents a weighted undirected edge connecting vertex u and vertex v."""

    def __init__(self, u: int, v: int, weight: int) -> None:
        self.u: int = u
        self.v: int = v
        self.weight: int = weight

    def __repr__(self) -> str:
        return f"Edge({self.u}, {self.v}, {self.weight})"


class DSU:
    """Disjoint Set Union (DSU) with Path Compression and Union by Rank."""

    def __init__(self, n: int) -> None:
        if n < 0:
            raise ValueError("Number of elements cannot be negative.")
        self.n: int = n
        self.parent: list[int] = list(range(n))
        self.rank: list[int] = [0] * n

    def find(self, x: int) -> int:
        """Find root representative of vertex x with recursive Path Compression."""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def unite(self, x: int, y: int) -> bool:
        """Merge sets containing x and y using Union by Rank.

        Returns False if already in the same set, True otherwise.
        """
        a = self.find(x)
        b = self.find(y)

        if a == b:
            return False

        if self.rank[a] < self.rank[b]:
            self.parent[a] = b
        elif self.rank[a] > self.rank[b]:
            self.parent[b] = a
        else:
            self.parent[b] = a
            self.rank[a] += 1

        return True


class EdgeListGraph:
    """Graph representation via an edge list for Boruvka's algorithm."""

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

    def boruvka_mst(self) -> None:
        """Merges components in parallel phases using their cheapest outgoing edges."""
        dsu = DSU(self.vertices)
        cheapest: list[int] = [-1] * self.vertices

        components = self.vertices
        total_weight = 0

        print("MST edges:")

        # Loop runs at most O(log V) times because each iteration halves component count
        while components > 1:
            # Step 1: Reset the cheapest edge record for all components
            for i in range(self.vertices):
                cheapest[i] = -1

            # Step 2: Iterate through all edges to find the cheapest outgoing edge for each component
            for i in range(self.total_edges):
                edge = self.edge_list[i]
                if edge is None:
                    continue

                set_u = dsu.find(edge.u)
                set_v = dsu.find(edge.v)

                # Ignore internal edges connecting vertices already within the same component
                if set_u == set_v:
                    continue

                # Check if this edge is cheaper than current known cheapest edge for component set_u
                if cheapest[set_u] == -1 or edge.weight < self.edge_list[cheapest[set_u]].weight:
                    cheapest[set_u] = i

                # Check if this edge is cheaper than current known cheapest edge for component set_v
                if cheapest[set_v] == -1 or edge.weight < self.edge_list[cheapest[set_v]].weight:
                    cheapest[set_v] = i

            merged = 0

            # Step 3: Add the identified cheapest edges to the MST
            for i in range(self.vertices):
                edge_index = cheapest[i]
                if edge_index == -1:
                    continue

                e = self.edge_list[edge_index]
                if e is None:
                    continue

                # Unite the two components if not already joined during this phase
                if dsu.unite(e.u, e.v):
                    print(f"{e.u} - {e.v} : {e.weight}")
                    total_weight += e.weight
                    components -= 1
                    merged += 1

            # If no edges could merge components, graph is disconnected
            if merged == 0:
                break

        # Step 4: Validate connectivity
        if components != 1:
            print("Graph is disconnected; no spanning tree exists.")
        else:
            print(f"Total MST weight: {total_weight}")

    # Alias to match C++ camelCase method name
    boruvkaMST = boruvka_mst


def main() -> None:
    # Construct a sample graph with 4 vertices and 5 edges:
    graph = EdgeListGraph(4, 5)

    graph.add_edge(0, 1, 10, 0)  # Edge (0 - 1) weight 10
    graph.add_edge(0, 2, 6, 1)   # Edge (0 - 2) weight 6
    graph.add_edge(0, 3, 5, 2)   # Edge (0 - 3) weight 5
    graph.add_edge(1, 3, 15, 3)  # Edge (1 - 3) weight 15
    graph.add_edge(2, 3, 4, 4)   # Edge (2 - 3) weight 4

    # Run Boruvka's algorithm
    graph.boruvka_mst()


if __name__ == "__main__":
    main()
