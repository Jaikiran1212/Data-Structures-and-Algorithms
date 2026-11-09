"""
Adjacency Matrix Representation of a Weighted Undirected Graph (Python)
----------------------------------------------------------------------
Represents graph connectivity using a 2D matrix of size V x V.
- matrix[u][v] = w denotes an edge between u and v with weight w.
- A value of 0 denotes the absence of an edge.

Time Complexities:
- Add Edge: O(1)
- Remove Edge: O(1)
- Query Edge (u, v): O(1)
- Iterate Neighbors of u: O(V)
- Space Complexity: O(V^2)
"""

from typing import Optional


class AdjacencyMatrix:
    """Weighted Undirected Graph representation using a 2D adjacency matrix."""

    def __init__(self, vertices: int) -> None:
        if vertices < 0:
            raise ValueError("The number of vertices cannot be negative.")
        self.vertices: int = vertices
        self.matrix: list[list[int]] = [[0] * vertices for _ in range(vertices)]

    def insert_edge(self, u: int, v: int, w: int) -> None:
        """Insert a weighted undirected edge between vertices u and v."""
        if u < 0 or v < 0 or u >= self.vertices or v >= self.vertices:
            return

        self.matrix[u][v] = w
        self.matrix[v][u] = w

    # Alias to match C++ camelCase method name
    insertEdge = insert_edge

    def remove_edge(self, u: int, v: int) -> None:
        """Remove the edge between vertices u and v if present."""
        if 0 <= u < self.vertices and 0 <= v < self.vertices:
            self.matrix[u][v] = 0
            self.matrix[v][u] = 0

    def has_edge(self, u: int, v: int) -> bool:
        """Check if an edge exists between vertices u and v."""
        if 0 <= u < self.vertices and 0 <= v < self.vertices:
            return self.matrix[u][v] != 0
        return False

    def get_weight(self, u: int, v: int) -> Optional[int]:
        """Return the weight of edge (u, v), or None if no edge exists."""
        if 0 <= u < self.vertices and 0 <= v < self.vertices:
            weight = self.matrix[u][v]
            return weight if weight != 0 else None
        return None

    def get_neighbors(self, u: int) -> list[tuple[int, int]]:
        """Return a list of (neighbor_vertex, weight) tuples for vertex u."""
        if not (0 <= u < self.vertices):
            return []
        return [(v, self.matrix[u][v]) for v in range(self.vertices) if self.matrix[u][v] != 0]

    def display(self) -> None:
        """Display the adjacency matrix row by row."""
        for i in range(self.vertices):
            for j in range(self.vertices):
                print(self.matrix[i][j], end=" ")
            print()


def main() -> None:
    g = AdjacencyMatrix(4)

    g.insert_edge(0, 1, 10)
    g.insert_edge(0, 2, 20)
    g.insert_edge(1, 3, 30)

    g.display()


if __name__ == "__main__":
    main()

