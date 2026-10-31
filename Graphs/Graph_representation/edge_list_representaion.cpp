// This program represents a weighted graph using an edge array with O(E) space.

#include <iostream>
using namespace std;

class EdgeList {
    struct Edge {
        int u, v, w;
    };

    Edge* edges;
    int vertices, edgeCount, capacity;

public:
    EdgeList(int n, int maxEdges) {
        vertices = n;
        capacity = maxEdges;
        edgeCount = 0;
        edges = new Edge[capacity];
    }

    void insertEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u >= vertices ||
            v >= vertices || edgeCount >= capacity)
            return;

        edges[edgeCount].u = u;
        edges[edgeCount].v = v;
        edges[edgeCount].w = w;
        edgeCount++;
    }

    void display() {
        for (int i = 0; i < edgeCount; i++)
            cout << edges[i].u << " - "
                 << edges[i].v << " : "
                 << edges[i].w << endl;
    }

    ~EdgeList() {
        delete[] edges;
    }
};

int main() {
    EdgeList g(4, 5);

    g.insertEdge(0, 1, 10);
    g.insertEdge(0, 2, 20);
    g.insertEdge(1, 3, 30);

    g.display();
    return 0;
}