
#include <iostream>
using namespace std;

// Boruvka's algorithm builds an MST by repeatedly joining components using their cheapest outgoing edges.

struct Edge {
    int u, v, weight;
};

class DSU {
private:
    int* parent;
    int* rankArr;
    int n;

public:
    DSU(int n) {
        this->n = n;
        parent = new int[n];
        rankArr = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rankArr[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        int a = find(x);
        int b = find(y);

        if (a == b)
            return false;

        if (rankArr[a] < rankArr[b])
            parent[a] = b;
        else if (rankArr[a] > rankArr[b])
            parent[b] = a;
        else {
            parent[b] = a;
            rankArr[a]++;
        }

        return true;
    }

    ~DSU() {
        delete[] parent;
        delete[] rankArr;
    }
};

class EdgeListGraph {
private:
    int vertices, edges;
    Edge* edgeList;

public:
    EdgeListGraph(int v, int e) {
        vertices = v;
        edges = e;
        edgeList = new Edge[e];
    }

    void addEdge(int u, int v, int weight, int index) {
        if (index >= 0 && index < edges) {
            edgeList[index].u = u;
            edgeList[index].v = v;
            edgeList[index].weight = weight;
        }
    }

    void boruvkaMST() {
        DSU dsu(vertices);
        int* cheapest = new int[vertices];

        int components = vertices;
        int totalWeight = 0;

        cout << "MST edges:\n";

        while (components > 1) {
            for (int i = 0; i < vertices; i++)
                cheapest[i] = -1;

            for (int i = 0; i < edges; i++) {
                int setU = dsu.find(edgeList[i].u);
                int setV = dsu.find(edgeList[i].v);

                if (setU == setV)
                    continue;

                if (cheapest[setU] == -1 ||
                    edgeList[i].weight <
                    edgeList[cheapest[setU]].weight)
                    cheapest[setU] = i;

                if (cheapest[setV] == -1 ||
                    edgeList[i].weight <
                    edgeList[cheapest[setV]].weight)
                    cheapest[setV] = i;
            }

            int merged = 0;

            for (int i = 0; i < vertices; i++) {
                int edgeIndex = cheapest[i];

                if (edgeIndex == -1)
                    continue;

                Edge e = edgeList[edgeIndex];

                if (dsu.unite(e.u, e.v)) {
                    cout << e.u << " - " << e.v
                         << " : " << e.weight << '\n';

                    totalWeight += e.weight;
                    components--;
                    merged++;
                }
            }

            if (merged == 0)
                break;
        }

        if (components != 1)
            cout << "Graph is disconnected; no spanning tree exists.\n";
        else
            cout << "Total MST weight: " << totalWeight << '\n';

        delete[] cheapest;
    }

    ~EdgeListGraph() {
        delete[] edgeList;
    }
};

int main() {
    EdgeListGraph graph(4, 5);

    graph.addEdge(0, 1, 10, 0);
    graph.addEdge(0, 2, 6, 1);
    graph.addEdge(0, 3, 5, 2);
    graph.addEdge(1, 3, 15, 3);
    graph.addEdge(2, 3, 4, 4);

    graph.boruvkaMST();

    return 0;
}
