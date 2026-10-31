// This program represents a weighted graph using linked lists with O(V + E) space.

#include <iostream>
using namespace std;

class AdjacencyList {
    struct Node {
        int vertex, weight;
        Node* next;

        Node(int v, int w) {
            vertex = v;
            weight = w;
            next = nullptr;
        }
    };

    Node** adj;
    int vertices;

public:
    AdjacencyList(int n) {
        vertices = n;
        adj = new Node*[n];

        for (int i = 0; i < n; i++)
            adj[i] = nullptr;
    }

    void insertEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices)
            return;

        Node* a = new Node(v, w);
        a->next = adj[u];
        adj[u] = a;

        Node* b = new Node(u, w);
        b->next = adj[v];
        adj[v] = b;
    }

    void display() {
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            Node* curr = adj[i];

            while (curr != nullptr) {
                cout << "(" << curr->vertex << ","
                     << curr->weight << ") ";
                curr = curr->next;
            }

            cout << endl;
        }
    }

    ~AdjacencyList() {
        for (int i = 0; i < vertices; i++) {
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
    AdjacencyList g(4);

    g.insertEdge(0, 1, 10);
    g.insertEdge(0, 2, 20);
    g.insertEdge(1, 3, 30);

    g.display();
    return 0;
}