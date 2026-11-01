
#include <iostream>
using namespace std;

class Graph {
    // Each node stores an adjacent vertex and the next node in the list.
    struct Node {
        int vertex;
        Node* next;

        Node(int v) {
            vertex = v;
            next = nullptr;
        }
    };

    Node** adj;  // Array of pointers to adjacency linked lists.
    int n;       // Number of vertices in the graph.

public:
    // Create an empty adjacency list for every vertex.
    Graph(int vertices) {
        n = vertices;
        adj = new Node*[n];

        for (int i = 0; i < n; i++)
            adj[i] = nullptr;
    }

    // Insert an undirected edge by adding both directions.
    void insertEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= n || v >= n)
            return;

        Node* a = new Node(v);
        a->next = adj[u];
        adj[u] = a;

        Node* b = new Node(u);
        b->next = adj[v];
        adj[v] = b;
    }

    // DFS explores one branch deeply before backtracking, using a manual stack.
    void DFS(int source) {
        if (source < 0 || source >= n)
            return;

        bool* visited = new bool[n];  // Tracks visited vertices.
        int* stack = new int[n];      // Array used as a stack.
        int top = -1;                 // -1 means the stack is empty.

        // Initially, no vertex has been visited.
        for (int i = 0; i < n; i++)
            visited[i] = false;

        // Push the starting vertex onto the stack.
        stack[++top] = source;

        // Continue until the stack becomes empty.
        while (top != -1) {
            int u = stack[top--];  // Pop the top vertex.

            // Process a vertex only once.
            if (!visited[u]) {
                cout << u << " ";  // Print the traversal order.
                visited[u] = true;

                // Examine every neighbour of the current vertex.
                Node* curr = adj[u];

                while (curr != nullptr) {
                    // Push unvisited neighbours for later exploration.
                    if (!visited[curr->vertex])
                        stack[++top] = curr->vertex;

                    curr = curr->next;
                }
            }
        }

        // Release the temporary memory used by DFS.
        delete[] visited;
        delete[] stack;
    }

    // BFS visits vertices level by level, using a manual queue.
    void BFS(int source) {
        if (source < 0 || source >= n)
            return;

        bool* visited = new bool[n];  // Tracks visited vertices.
        int* queue = new int[n];      // Array used as a queue.
        int front = 0, rear = 0;      // Queue is initially empty.

        // Initially, no vertex has been visited.
        for (int i = 0; i < n; i++)
            visited[i] = false;

        // Mark the source visited before enqueueing to avoid duplicates.
        visited[source] = true;
        queue[rear++] = source;

        // Continue until all queued vertices have been processed.
        while (front < rear) {
            int u = queue[front++];  // Remove the front vertex.
            cout << u << " ";        // Print the traversal order.

            // Examine every neighbour of the current vertex.
            Node* curr = adj[u];

            while (curr != nullptr) {
                int v = curr->vertex;

                // Visit each neighbour only once.
                if (!visited[v]) {
                    visited[v] = true;  // Mark before enqueueing.
                    queue[rear++] = v;
                }

                curr = curr->next;
            }
        }

        // Release the temporary memory used by BFS.
        delete[] visited;
        delete[] queue;
    }

    // Display every vertex and its adjacent vertices.
    void display() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            Node* curr = adj[i];

            while (curr != nullptr) {
                cout << curr->vertex << " ";
                curr = curr->next;
            }

            cout << endl;
        }
    }

    // Free all adjacency-list nodes and the pointer array.
    ~Graph() {
        for (int i = 0; i < n; i++) {
            Node* curr = adj[i];

            while (curr != nullptr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }

        delete[] adj;
    }
};

int main() {
    Graph g(6);

    // Construct the sample undirected graph.
    g.insertEdge(0, 1);
    g.insertEdge(0, 2);
    g.insertEdge(1, 3);
    g.insertEdge(1, 4);
    g.insertEdge(2, 5);

    cout << "DFS: ";
    g.DFS(0);

    cout << "\nBFS: ";
    g.BFS(0);

    cout << endl;
    return 0;
}
