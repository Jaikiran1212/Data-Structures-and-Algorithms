
#include <iostream>
using namespace std;

// Prim's algorithm builds an MST in O((V + E) log V) time using an adjacency list.

class PriorityQueue {
private:
    struct Item {
        int vertex, priority;
    };

    Item* heap;
    int size, capacity;

    void swapItems(int i, int j) {
        Item temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent].priority <= heap[i].priority)
                break;

            swapItems(parent, i);
            i = parent;
        }
    }

    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size &&
                heap[left].priority < heap[smallest].priority)
                smallest = left;

            if (right < size &&
                heap[right].priority < heap[smallest].priority)
                smallest = right;

            if (smallest == i)
                break;

            swapItems(i, smallest);
            i = smallest;
        }
    }

public:
    PriorityQueue(int capacity) {
        this->capacity = capacity;
        size = 0;
        heap = new Item[capacity];
    }

    bool empty() {
        return size == 0;
    }

    bool insert(int vertex, int priority) {
        if (size == capacity)
            return false;

        heap[size].vertex = vertex;
        heap[size].priority = priority;
        heapifyUp(size);
        size++;
        return true;
    }

    bool extractMin(int& vertex, int& priority) {
        if (empty())
            return false;

        vertex = heap[0].vertex;
        priority = heap[0].priority;

        heap[0] = heap[size - 1];
        size--;

        if (!empty())
            heapifyDown(0);

        return true;
    }

    ~PriorityQueue() {
        delete[] heap;
    }
};

struct Node {
    int vertex, weight;
    Node* next;
};

class AdjacencyListGraph {
private:
    int vertices;
    Node** adj;

public:
    AdjacencyListGraph(int v) {
        vertices = v;
        adj = new Node*[vertices];

        for (int i = 0; i < vertices; i++)
            adj[i] = NULL;
    }

    void addEdge(int u, int v, int weight) {
        Node* a = new Node{v, weight, adj[u]};
        adj[u] = a;

        Node* b = new Node{u, weight, adj[v]};
        adj[v] = b;
    }

    void primMST(int start) {
        int* key = new int[vertices];
        int* parent = new int[vertices];
        bool* inMST = new bool[vertices];

        const int INF = 1000000000;

        for (int i = 0; i < vertices; i++) {
            key[i] = INF;
            parent[i] = -1;
            inMST[i] = false;
        }

        // Each vertex can receive several entries; skip outdated entries.
        PriorityQueue pq(vertices * 10 + 1);
        key[start] = 0;
        pq.insert(start, 0);

        int totalWeight = 0;
        int selected = 0;

        while (!pq.empty()) {
            int u, priority;
            pq.extractMin(u, priority);

            if (inMST[u])
                continue;

            inMST[u] = true;
            selected++;

            if (parent[u] != -1) {
                cout << parent[u] << " - " << u
                     << " : " << key[u] << '\n';
                totalWeight += key[u];
            }

            Node* current = adj[u];

            while (current != NULL) {
                int v = current->vertex;
                int w = current->weight;

                if (!inMST[v] && w < key[v]) {
                    key[v] = w;
                    parent[v] = u;
                    pq.insert(v, key[v]);
                }

                current = current->next;
            }
        }

        if (selected != vertices)
            cout << "Graph is disconnected; no spanning tree exists.\n";
        else
            cout << "Total MST weight: " << totalWeight << '\n';

        delete[] key;
        delete[] parent;
        delete[] inMST;
    }

    ~AdjacencyListGraph() {
        for (int i = 0; i < vertices; i++) {
            Node* current = adj[i];

            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] adj;
    }
};

int main() {
    AdjacencyListGraph graph(5);

    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);

    graph.primMST(0);

    return 0;
}
