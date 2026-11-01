/**
 * ============================================================================
 * Algorithm: Prim's Minimum Spanning Tree (MST)
 * ============================================================================
 * 
 * Overview:
 *   Prim's algorithm (also known as the Jarník-Prim algorithm) is a greedy
 *   graph algorithm that constructs an MST by continuously expanding a single
 *   growing tree one vertex at a time.
 * 
 * Core Strategy:
 *   1. Begin at an arbitrary starting vertex (e.g., vertex 0) and maintain:
 *      - inMST[]: Boolean flags indicating vertices already in the growing tree.
 *      - key[]:   Minimum weight required to connect an external vertex to the MST.
 *      - parent[]:Predecessor of each vertex in the resulting spanning tree.
 *   2. Set key[start] = 0 and insert (start, 0) into a Min-Priority Queue.
 *   3. While the priority queue is not empty:
 *      a. Extract the vertex u with the smallest key value.
 *      b. If u is already included in the MST, skip it (lazy deletion).
 *      c. Mark inMST[u] = true and add the edge (parent[u], u) to the MST.
 *      d. For every neighbor v of u:
 *         - If v is not yet in the MST and edge weight w(u, v) < key[v]:
 *           Update key[v] = w(u, v), parent[v] = u, and push (v, key[v]) into the PQ.
 *   4. Continue until all V vertices are in the MST (or the queue empties).
 * 
 * Mathematical Basis:
 *   The Cut Property: For any cut dividing graph vertices into two subsets,
 *   the minimum-weight edge crossing the cut must belong to some MST.
 * 
 * Complexity:
 *   - Time Complexity:  O((V + E) log V) using an adjacency list and binary heap.
 *   - Space Complexity: O(V + E) for adjacency linked lists and tracking arrays.
 * 
 * Zero External Dependencies:
 *   Implemented from scratch without STL containers (no std::priority_queue,
 *   no std::vector, no std::list), demonstrating raw linked lists and heap mechanics.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Min-Priority Queue for Graph Vertices
// ----------------------------------------------------------------------------
class PriorityQueue {
private:
    struct Item {
        int vertex;    // Target vertex identifier
        int priority;  // Key / cut weight used for ordering in the heap
    };

    Item* heap;        // Array-based complete binary heap buffer
    int size;          // Current number of items in the queue
    int capacity;      // Maximum capacity of the heap

    // Swap two items in the heap array.
    void swapItems(int i, int j) {
        Item temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // heapifyUp(i): Restores min-heap property by bubbling an element up.
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent].priority <= heap[i].priority)
                break;

            swapItems(parent, i);
            i = parent;
        }
    }

    // heapifyDown(i): Restores min-heap property by sifting an element down.
    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[left].priority < heap[smallest].priority)
                smallest = left;

            if (right < size && heap[right].priority < heap[smallest].priority)
                smallest = right;

            if (smallest == i)
                break;

            swapItems(i, smallest);
            i = smallest;
        }
    }

public:
    // Constructor: Allocate contiguous memory for the priority queue.
    PriorityQueue(int capacity) {
        this->capacity = capacity;
        size = 0;
        heap = new Item[capacity];
    }

    // Check if the priority queue contains no elements.
    bool empty() {
        return size == 0;
    }

    // Insert a vertex with its priority into the heap in O(log V) time.
    bool insert(int vertex, int priority) {
        if (size == capacity)
            return false;

        heap[size].vertex = vertex;
        heap[size].priority = priority;
        heapifyUp(size);
        size++;
        return true;
    }

    // Remove and return the vertex with the minimum priority in O(log V) time.
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

    // Destructor: Clean up dynamic heap memory.
    ~PriorityQueue() {
        delete[] heap;
    }
};

// ----------------------------------------------------------------------------
// Adjacency List Node
// ----------------------------------------------------------------------------
struct Node {
    int vertex;  // Neighbor vertex
    int weight;  // Weight of the incident edge
    Node* next;  // Pointer to the next adjacent node in the list
};

// ----------------------------------------------------------------------------
// Graph Representation via Adjacency Lists
// ----------------------------------------------------------------------------
class AdjacencyListGraph {
private:
    int vertices;  // Total number of vertices (V)
    Node** adj;    // Array of linked list head pointers

public:
    // Constructor: Allocate array of linked list heads.
    AdjacencyListGraph(int v) {
        vertices = v;
        adj = new Node*[vertices];

        for (int i = 0; i < vertices; i++)
            adj[i] = NULL;
    }

    // Insert an undirected weighted edge by prepending to both adjacency lists.
    void addEdge(int u, int v, int weight) {
        Node* a = new Node{v, weight, adj[u]};
        adj[u] = a;

        Node* b = new Node{u, weight, adj[v]};
        adj[v] = b;
    }

    // Prim's MST Algorithm:
    // Grows the MST starting from vertex 'start' using a greedy cut approach.
    void primMST(int start) {
        int* key = new int[vertices];        // Minimum edge weight connecting vertex i to MST
        int* parent = new int[vertices];    // Predecessor of vertex i in the MST
        bool* inMST = new bool[vertices];    // True if vertex i is already included in the MST

        const int INF = 1000000000;          // Representation of infinity

        // Step 1: Initialize all vertices as unvisited with infinite cost.
        for (int i = 0; i < vertices; i++) {
            key[i] = INF;
            parent[i] = -1;
            inMST[i] = false;
        }

        // Step 2: Initialize priority queue.
        // Allocate generous capacity to support multiple updates per vertex (lazy deletion).
        PriorityQueue pq(vertices * 10 + 1);

        // Distance to start vertex from itself is 0.
        key[start] = 0;
        pq.insert(start, 0);

        int totalWeight = 0;  // Total MST weight accumulator
        int selected = 0;     // Count of vertices incorporated into the tree

        // Step 3: Process the closest unvisited vertex at each step.
        while (!pq.empty()) {
            int u, priority;
            pq.extractMin(u, priority);

            // Lazy deletion check: if u was already added to the MST via an earlier
            // extraction with a smaller weight, skip this stale queue entry.
            if (inMST[u])
                continue;

            // Include vertex u in the MST.
            inMST[u] = true;
            selected++;

            // If u is not the root, print the chosen MST edge connecting it.
            if (parent[u] != -1) {
                cout << parent[u] << " - " << u
                     << " : " << key[u] << '\n';
                totalWeight += key[u];
            }

            // Step 4: Relax all incident edges to unvisited neighbors of u.
            Node* current = adj[u];

            while (current != NULL) {
                int v = current->vertex;
                int w = current->weight;

                // If neighbor v is outside the MST and this edge provides a cheaper connection:
                if (!inMST[v] && w < key[v]) {
                    key[v] = w;          // Update cheapest connection cost
                    parent[v] = u;       // Set u as the predecessor of v
                    pq.insert(v, key[v]);// Push updated candidate into the priority queue
                }

                current = current->next;
            }
        }

        // Step 5: Check connectivity (all V vertices must be reachable).
        if (selected != vertices)
            cout << "Graph is disconnected; no spanning tree exists.\n";
        else
            cout << "Total MST weight: " << totalWeight << '\n';

        // Free temporary buffers used during traversal.
        delete[] key;
        delete[] parent;
        delete[] inMST;
    }

    // Destructor: Deallocate all dynamically allocated nodes in adjacency lists.
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

// ----------------------------------------------------------------------------
// Demonstration Driver
// ----------------------------------------------------------------------------
int main() {
    // Construct a sample graph with 5 vertices (0 through 4) and 7 undirected edges:
    AdjacencyListGraph graph(5);

    graph.addEdge(0, 1, 2);  // Edge (0 - 1) weight 2
    graph.addEdge(0, 3, 6);  // Edge (0 - 3) weight 6
    graph.addEdge(1, 2, 3);  // Edge (1 - 2) weight 3
    graph.addEdge(1, 3, 8);  // Edge (1 - 3) weight 8
    graph.addEdge(1, 4, 5);  // Edge (1 - 4) weight 5
    graph.addEdge(2, 4, 7);  // Edge (2 - 4) weight 7
    graph.addEdge(3, 4, 9);  // Edge (3 - 4) weight 9

    // Run Prim's algorithm starting from vertex 0:
    // Expected output edges:
    //   0 - 1 : 2
    //   1 - 2 : 3
    //   1 - 4 : 5
    //   0 - 3 : 6
    // Total MST weight: 16
    graph.primMST(0);

    return 0;
}
