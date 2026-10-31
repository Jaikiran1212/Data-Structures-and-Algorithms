// This program implements DFS and BFS using linked lists, a stack, and a queue in O(V + E) time.

#include <iostream>
using namespace std;

class Graph {
    struct Node {
        int vertex;
        Node* next;

        Node(int v) {
            vertex = v;
            next = nullptr;
        }
    };

    Node** adj;
    int n;

public:
    Graph(int vertices) {
        n = vertices;
        adj = new Node*[n];

        for (int i = 0; i < n; i++)
            adj[i] = nullptr;
    }

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

    void DFS(int source) {
        if (source < 0 || source >= n)
            return;

        bool* visited = new bool[n];
        int* stack = new int[n];
        int top = -1;

        for (int i = 0; i < n; i++)
            visited[i] = false;

        stack[++top] = source;

        while (top != -1) {
            int u = stack[top--];

            if (!visited[u]) {
                cout << u << " ";
                visited[u] = true;

                Node* curr = adj[u];

                while (curr != nullptr) {
                    if (!visited[curr->vertex])
                        stack[++top] = curr->vertex;

                    curr = curr->next;
                }
            }
        }

        delete[] visited;
        delete[] stack;
    }

    void BFS(int source) {
        if (source < 0 || source >= n)
            return;

        bool* visited = new bool[n];
        int* queue = new int[n];
        int front = 0, rear = 0;

        for (int i = 0; i < n; i++)
            visited[i] = false;

        visited[source] = true;
        queue[rear++] = source;

        while (front < rear) {
            int u = queue[front++];
            cout << u << " ";

            Node* curr = adj[u];

            while (curr != nullptr) {
                int v = curr->vertex;

                if (!visited[v]) {
                    visited[v] = true;
                    queue[rear++] = v;
                }

                curr = curr->next;
            }
        }

        delete[] visited;
        delete[] queue;
    }

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