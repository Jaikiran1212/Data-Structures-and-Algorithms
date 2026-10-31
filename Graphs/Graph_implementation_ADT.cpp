// This program implements Graph ADT operations using linked lists with O(V + E) space.

#include <iostream>
using namespace std;

class Graph {
private:
    struct Node {
        int vertex;
        int weight;
        Node* next;

        Node(int v, int w) {
            vertex = v;
            weight = w;
            next = nullptr;
        }
    };

    int n;
    Node** adj;

public:
    Graph(int vertices) {
        n = vertices;
        adj = new Node*[n];

        for (int i = 0; i < n; i++)
            adj[i] = nullptr;
    }

    int numVertices() {
        return n;
    }

    void insertEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u >= n || v >= n)
            return;

        Node* a = new Node(v, w);
        a->next = adj[u];
        adj[u] = a;

        Node* b = new Node(u, w);
        b->next = adj[v];
        adj[v] = b;
    }

    void eraseEdge(int u, int v) {
        if (u < 0 || v < 0 || u >= n || v >= n)
            return;

        Node* curr = adj[u];
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->vertex == v) {
                if (prev == nullptr)
                    adj[u] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                break;
            }

            prev = curr;
            curr = curr->next;
        }

        curr = adj[v];
        prev = nullptr;

        while (curr != nullptr) {
            if (curr->vertex == u) {
                if (prev == nullptr)
                    adj[v] = curr->next;
                else
                    prev->next = curr->next;

                delete curr;
                break;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    bool isAdjacentTo(int u, int v) {
        if (u < 0 || v < 0 || u >= n || v >= n)
            return false;

        Node* curr = adj[u];

        while (curr != nullptr) {
            if (curr->vertex == v)
                return true;

            curr = curr->next;
        }

        return false;
    }

    void incidentVertices(int u) {
        if (u < 0 || u >= n)
            return;

        Node* curr = adj[u];

        while (curr != nullptr) {
            cout << curr->vertex << " ";
            curr = curr->next;
        }

        cout << endl;
    }

    void display() {
        for (int i = 0; i < n; i++) {
            cout << i << ": ";
            Node* curr = adj[i];

            while (curr != nullptr) {
                cout << "(" << curr->vertex
                     << "," << curr->weight << ") ";
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
    Graph g(5);

    g.insertEdge(0, 1, 10);
    g.insertEdge(0, 2, 20);
    g.insertEdge(1, 3, 30);
    g.insertEdge(2, 4, 40);

    cout << "Graph:\n";
    g.display();

    cout << "\nAdjacent (0,1): "
         << (g.isAdjacentTo(0, 1) ? "Yes" : "No") << endl;

    cout << "Incident vertices of 0: ";
    g.incidentVertices(0);

    g.eraseEdge(0, 1);

    cout << "\nAfter deleting edge (0,1):\n";
    g.display();

    return 0;
}