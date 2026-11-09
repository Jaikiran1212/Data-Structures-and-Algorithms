"""
Adjacency List Representation of a Weighted Undirected Graph (Python)
--------------------------------------------------------------------
Represents graph connectivity using an array (list) of singly linked lists,
where each index u contains the head of a linked list of adjacent nodes (v, w).

Time Complexities:
- Add Edge: O(1) (prepend to head)
- Remove Edge: O(deg(u))
- Query Edge (u, v): O(deg(u))
- Iterate Neighbors of u: O(deg(u))
- Space Complexity: O(V + E)
"""

from typing import Optional


class Node:
    """A node in the singly linked adjacency list representing a neighbor and edge weight."""

    def __init__(self, vertex: int, weight: int, next_node: Optional["Node"] = None) -> None:
        self.vertex: int = vertex
        self.weight: int = weight
        self.next: Optional[Node] = next_node


class AdjacencyList:
    """Weighted Undirected Graph representation using linked list adjacency lists."""

    def __init__(self, vertices: int) -> None:
        if vertices < 0:
            raise ValueError("The number of vertices cannot be negative.")
        self.vertices: int = vertices
        self.adj: list[Optional[Node]] = [None] * vertices

    def insert_edge(self, u: int, v: int, w: int) -> None:
        """Insert a weighted undirected edge between u and v by prepending to their linked lists."""
        if u < 0 or v < 0 or u >= self.vertices or v >= self.vertices:
            return

        a = Node(v, w, self.adj[u])
        self.adj[u] = a

        b = Node(u, w, self.adj[v])
        self.adj[v] = b

    # Alias to match C++ camelCase method name
    insertEdge = insert_edge

    def remove_edge(self, u: int, v: int) -> None:
        """Remove the edge between u and v if present."""
        if not (0 <= u < self.vertices and 0 <= v < self.vertices):
            return

        def _remove_from_list(head: Optional[Node], target: int) -> Optional[Node]:
            dummy = Node(-1, 0, head)
            curr = dummy
            while curr.next is not None:
                if curr.next.vertex == target:
                    curr.next = curr.next.next
                    break
                curr = curr.next
            return dummy.next

        self.adj[u] = _remove_from_list(self.adj[u], v)
        self.adj[v] = _remove_from_list(self.adj[v], u)

    def has_edge(self, u: int, v: int) -> bool:
        """Check if an edge exists between vertices u and v."""
        if not (0 <= u < self.vertices and 0 <= v < self.vertices):
            return False
        curr = self.adj[u]
        while curr is not None:
            if curr.vertex == v:
                return True
            curr = curr.next
        return False

    def get_weight(self, u: int, v: int) -> Optional[int]:
        """Return the weight of edge (u, v), or None if no edge exists."""
        if not (0 <= u < self.vertices and 0 <= v < self.vertices):
            return None
        curr = self.adj[u]
        while curr is not None:
            if curr.vertex == v:
                return curr.weight
            curr = curr.next
        return None

    def get_neighbors(self, u: int) -> list[tuple[int, int]]:
        """Return a list of (neighbor_vertex, weight) tuples for vertex u."""
        if not (0 <= u < self.vertices):
            return []
        neighbors: list[tuple[int, int]] = []
        curr = self.adj[u]
        while curr is not None:
            neighbors.append((curr.vertex, curr.weight))
            curr = curr.next
        return neighbors

    def display(self) -> None:
        """Display the adjacency list for each vertex."""
        for i in range(self.vertices):
            print(f"{i}: ", end="")
            curr = self.adj[i]
            while curr is not None:
                print(f"({curr.vertex},{curr.weight}) ", end="")
                curr = curr.next
            print()


def main() -> None:
    g = AdjacencyList(4)

    g.insert_edge(0, 1, 10)
    g.insert_edge(0, 2, 20)
    g.insert_edge(1, 3, 30)

    g.display()


if __name__ == "__main__":
    main()

