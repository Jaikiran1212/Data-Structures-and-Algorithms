"""
Edge List Representation of a Weighted Undirected Graph (Python)
---------------------------------------------------------------
Represents graph connectivity as a collection (array/list) of discrete Edge records.
- Each edge stores (u, v, w) representing endpoints and weight.

Time Complexities:
- Add Edge: O(1) (append to list)
- Remove Edge: O(E) (linear search)
- Query Edge (u, v): O(E) (linear scan)
- Iterate Neighbors of u: O(E) (linear scan over all edges)
- Space Complexity: O(E)
"""

from typing import Optional


class Edge:
    """Represents a weighted undirected edge connecting vertex u and vertex v."""

    def __init__(self, u: int, v: int, w: int) -> None:
        self.u: int = u
        self.v: int = v
        self.w: int = w

    def __repr__(self) -> str:
        return f"Edge({self.u}, {self.v}, {self.w})"


class EdgeList:
    """Weighted Undirected Graph representation using an edge list."""

    def __init__(self, vertices: int, capacity: Optional[int] = None) -> None:
        if vertices < 0:
            raise ValueError("The number of vertices cannot be negative.")
        self.vertices: int = vertices
        self.capacity: Optional[int] = capacity
        self.edges: list[Edge] = []

    @property
    def edge_count(self) -> int:
        """Return the current number of edges."""
        return len(self.edges)

    def insert_edge(self, u: int, v: int, w: int) -> None:
        """Insert a weighted edge between vertices u and v."""
        if u < 0 or v < 0 or u >= self.vertices or v >= self.vertices:
            return
        if self.capacity is not None and len(self.edges) >= self.capacity:
            return

        self.edges.append(Edge(u, v, w))

    # Alias to match C++ camelCase method name
    insertEdge = insert_edge

    def remove_edge(self, u: int, v: int) -> None:
        """Remove the edge between vertices u and v if present."""
        for i, edge in enumerate(self.edges):
            if (edge.u == u and edge.v == v) or (edge.u == v and edge.v == u):
                self.edges.pop(i)
                break

    def has_edge(self, u: int, v: int) -> bool:
        """Check if an edge exists between vertices u and v."""
        return any(
            (edge.u == u and edge.v == v) or (edge.u == v and edge.v == u)
            for edge in self.edges
        )

    def get_weight(self, u: int, v: int) -> Optional[int]:
        """Return the weight of edge between u and v, or None if no edge exists."""
        for edge in self.edges:
            if (edge.u == u and edge.v == v) or (edge.u == v and edge.v == u):
                return edge.w
        return None

    def get_neighbors(self, u: int) -> list[tuple[int, int]]:
        """Return a list of (neighbor_vertex, weight) tuples for vertex u."""
        neighbors: list[tuple[int, int]] = []
        for edge in self.edges:
            if edge.u == u:
                neighbors.append((edge.v, edge.w))
            elif edge.v == u:
                neighbors.append((edge.u, edge.w))
        return neighbors

    def display(self) -> None:
        """Display all edges in the graph."""
        for edge in self.edges:
            print(f"{edge.u} - {edge.v} : {edge.w}")


def main() -> None:
    g = EdgeList(4, 5)

    g.insert_edge(0, 1, 10)
    g.insert_edge(0, 2, 20)
    g.insert_edge(1, 3, 30)

    g.display()


if __name__ == "__main__":
    main()

