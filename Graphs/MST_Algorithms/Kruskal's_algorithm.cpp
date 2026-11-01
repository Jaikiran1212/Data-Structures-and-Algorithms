
#include <iostream>
using namespace std;

// Kruskal's algorithm builds an MST in O(E log E) time using an edge list.

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
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return false;

        if (rankArr[rootX] < rankArr[rootY])
            parent[rootX] = rootY;
        else if (rankArr[rootX] > rankArr[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }

        return true;
    }

    ~DSU() {
        delete[] parent;
        delete[] rankArr;
    }
};

struct Edge {
    int u, v, weight;
};

class MinHeap {
private:
    Edge* heap;
    int size, capacity;

    void swapEdges(int i, int j) {
        Edge temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent].weight <= heap[i].weight)
                break;
            swapEdges(parent, i);
            i = parent;
        }
    }

    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size &&
                heap[left].weight < heap[smallest].weight)
                smallest = left;

            if (right < size &&
                heap[right].weight < heap[smallest].weight)
                smallest = right;

            if (smallest == i)
                break;

            swapEdges(i, smallest);
            i = smallest;
        }
    }

public:
    MinHeap(int capacity) {
        this->capacity = capacity;
        size = 0;
        heap = new Edge[capacity];
    }

    bool empty() {
        return size == 0;
    }

    bool insert(Edge e) {
        if (size == capacity)
            return false;

        heap[size] = e;
        heapifyUp(size);
        size++;
        return true;
    }

    bool extractMin(Edge& e) {
        if (empty())
            return false;

        e = heap[0];
        heap[0] = heap[size - 1];
        size--;

        if (!empty())
            heapifyDown(0);

        return true;
    }

    ~MinHeap() {
        delete[] heap;
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

    void kruskalMST() {
        MinHeap heap(edges);

        for (int i = 0; i < edges; i++)
            heap.insert(edgeList[i]);

        DSU dsu(vertices);
        int totalWeight = 0;
        int selected = 0;

        cout << "MST edges:\n";

        while (!heap.empty() && selected < vertices - 1) {
            Edge e;
            heap.extractMin(e);

            if (dsu.unite(e.u, e.v)) {
                cout << e.u << " - " << e.v
                     << " : " << e.weight << '\n';
                totalWeight += e.weight;
                selected++;
            }
        }

        if (selected != vertices - 1)
            cout << "Graph is disconnected; no spanning tree exists.\n";
        else
            cout << "Total MST weight: " << totalWeight << '\n';
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

    graph.kruskalMST();

    return 0;
}
