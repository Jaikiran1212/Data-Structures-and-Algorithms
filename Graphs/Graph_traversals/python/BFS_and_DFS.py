from collections import deque


class Graph:
    def __init__(self, vertices: int) -> None:
        if vertices < 0:
            raise ValueError("The number of vertices cannot be negative.")
        self.adjacency_list: list[list[int]] = [[] for _ in range(vertices)]

    def insert_edge(self, u: int, v: int) -> None:
        if not (0 <= u < len(self.adjacency_list) and 0 <= v < len(self.adjacency_list)):
            return

        # Insert at the front to match the adjacency order of the C++ linked lists.
        self.adjacency_list[u].insert(0, v)
        self.adjacency_list[v].insert(0, u)

    def dfs(self, source: int) -> list[int]:
        if not 0 <= source < len(self.adjacency_list):
            return []

        visited = [False] * len(self.adjacency_list)
        stack = [source]
        traversal = []

        while stack:
            vertex = stack.pop()
            if visited[vertex]:
                continue

            visited[vertex] = True
            traversal.append(vertex)
            for neighbor in self.adjacency_list[vertex]:
                if not visited[neighbor]:
                    stack.append(neighbor)

        return traversal

    def bfs(self, source: int) -> list[int]:
        if not 0 <= source < len(self.adjacency_list):
            return []

        visited = [False] * len(self.adjacency_list)
        visited[source] = True
        queue = deque([source])
        traversal = []

        while queue:
            vertex = queue.popleft()
            traversal.append(vertex)

            for neighbor in self.adjacency_list[vertex]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)

        return traversal

    def display(self) -> None:
        for vertex, neighbors in enumerate(self.adjacency_list):
            print(f"{vertex}: {' '.join(map(str, neighbors))}")


def main() -> None:
    graph = Graph(6)
    graph.insert_edge(0, 1)
    graph.insert_edge(0, 2)
    graph.insert_edge(1, 3)
    graph.insert_edge(1, 4)
    graph.insert_edge(2, 5)

    print("DFS:", *graph.dfs(0))
    print("BFS:", *graph.bfs(0))


if __name__ == "__main__":
    main()
