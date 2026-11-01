/**
 * ============================================================================
 * Algorithm: Kruskal's Minimum Spanning Tree (MST)
 * ============================================================================
 * 
 * Overview:
 *   Kruskal's algorithm is a greedy algorithm that finds a Minimum Spanning
 *   Tree (MST) for a connected, undirected, edge-weighted graph.
 * 
 * Core Strategy:
 *   1. Treat every vertex as an independent tree (a forest of V trees).
 *   2. Insert all edges into a Min-Heap (or sort them) in non-decreasing order
 *      of edge weight.
 *   3. Repeatedly extract the minimum-weight edge (u, v).
 *   4. Using a Disjoint Set Union (DSU / Union-Find) data structure:
 *      - If u and v belong to different connected components, adding this edge
 *        will NOT form a cycle. Add the edge to the MST and unite the two components.
 *      - If u and v already belong to the same component, discard the edge to
 *        prevent a cycle.
 *   5. Terminate when (V - 1) edges have been added, or all edges are exhausted.
 * 
 * Complexity:
 *   - Time Complexity:  O(E log E) or O(E log V) to extract edges from the Min-Heap,
 *                       plus O(E * alpha(V)) for DSU operations.
 *   - Space Complexity: O(V + E) to store the DSU arrays and Min-Heap edges.
 * 
 * Zero External Dependencies:
 *   Implemented from scratch without STL containers (no std::priority_queue,
 *   no std::vector), demonstrating low-level heapification and disjoint-set mechanics.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Disjoint Set Union (DSU) with Path Compression and Union by Rank
// ----------------------------------------------------------------------------
class DSU {
private:
    int* parent;   // parent[i] points to the parent of node i; if parent[i] == i, i is a root.
    int* rankArr;  // rankArr[i] approximates tree height, used to maintain balanced trees.
    int n;         // Total number of vertices.

public:
    // Initialize n disjoint sets where each element is initially its own root.
    DSU(int n) {
        this->n = n;
        parent = new int[n];
        rankArr = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Every vertex starts as its own representative.
            rankArr[i] = 0;  // Initial rank/depth is 0.
        }
    }

    // find(x): Finds the root representative of the set containing x.
    // Uses Path Compression: flattens the tree by linking visited nodes directly to the root.
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Recursive path compression.
        return parent[x];
    }

    // unite(x, y): Merges the sets containing x and y.
    // Returns false if x and y are already in the same set (cycle detected!).
    // Returns true if a successful union occurred.
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        // If both vertices share the same representative, adding an edge creates a cycle.
        if (rootX == rootY)
            return false;

        // Union by rank: attach the shallower tree beneath the deeper tree.
        if (rankArr[rootX] < rankArr[rootY])
            parent[rootX] = rootY;
        else if (rankArr[rootX] > rankArr[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rankArr[rootX]++;  // Height increases only when merging equal-rank trees.
        }

        return true;
    }

    // Destructor: Clean up dynamic memory.
    ~DSU() {
        delete[] parent;
        delete[] rankArr;
    }
};

// ----------------------------------------------------------------------------
// Edge Representation
// ----------------------------------------------------------------------------
struct Edge {
    int u;       // Source vertex
    int v;       // Destination vertex
    int weight;  // Edge cost/weight
};

// ----------------------------------------------------------------------------
// Binary Min-Heap for Graph Edges
// ----------------------------------------------------------------------------
class MinHeap {
private:
    Edge* heap;         // Dynamic array storing complete binary heap.
    int size;           // Number of active edges currently in the heap.
    int capacity;       // Maximum capacity of the heap array.

    // Swap two edges in the heap array.
    void swapEdges(int i, int j) {
        Edge temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // heapifyUp(i): Restores min-heap invariant by bubbling an element up.
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[parent].weight <= heap[i].weight)
                break;
            swapEdges(parent, i);
            i = parent;
        }
    }

    // heapifyDown(i): Restores min-heap invariant by sifting an element down.
    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[left].weight < heap[smallest].weight)
                smallest = left;

            if (right < size && heap[right].weight < heap[smallest].weight)
                smallest = right;

            if (smallest == i)
                break;

            swapEdges(i, smallest);
            i = smallest;
        }
    }

public:
    // Constructor: Allocate contiguous memory for the heap.
    MinHeap(int capacity) {
        this->capacity = capacity;
        size = 0;
        heap = new Edge[capacity];
    }

    // Check if the heap is empty.
    bool empty() {
        return size == 0;
    }

    // Insert an edge into the heap in O(log E) time.
    bool insert(Edge e) {
        if (size == capacity)
            return false;

        heap[size] = e;
        heapifyUp(size);
        size++;
        return true;
    }

    // Remove and return the edge with minimum weight in O(log E) time.
    bool extractMin(Edge& e) {
        if (empty())
            return false;

        e = heap[0];               // Minimum weight edge is always at the root.
        heap[0] = heap[size - 1];  // Move the last element to the root.
        size--;

        if (!empty())
            heapifyDown(0);        // Restore heap order.

        return true;
    }

    // Destructor: Clean up heap memory.
    ~MinHeap() {
        delete[] heap;
    }
};

// ----------------------------------------------------------------------------
// Graph Representation via Edge List
// ----------------------------------------------------------------------------
class EdgeListGraph {
private:
    int vertices;    // Number of vertices (V)
    int edges;       // Number of edges (E)
    Edge* edgeList;  // Array storing all graph edges

public:
    // Constructor: Allocate edge list array.
    EdgeListGraph(int v, int e) {
        vertices = v;
        edges = e;
        edgeList = new Edge[e];
    }

    // Add an edge with given endpoints and weight at a specified index.
    void addEdge(int u, int v, int weight, int index) {
        if (index >= 0 && index < edges) {
            edgeList[index].u = u;
            edgeList[index].v = v;
            edgeList[index].weight = weight;
        }
    }

    // Kruskal's MST Algorithm:
    // Greedily selects the lightest edge that does not introduce a cycle.
    void kruskalMST() {
        // Step 1: Push all edges into the Min-Heap.
        MinHeap heap(edges);
        for (int i = 0; i < edges; i++)
            heap.insert(edgeList[i]);

        // Step 2: Initialize DSU with V disjoint sets.
        DSU dsu(vertices);
        int totalWeight = 0;  // Accumulator for total MST cost.
        int selected = 0;     // Counter of chosen edges (MST needs exactly V - 1).

        cout << "MST edges:\n";

        // Step 3: Process edges in ascending order of weight.
        while (!heap.empty() && selected < vertices - 1) {
            Edge e;
            heap.extractMin(e);

            // Step 4: If uniting endpoints succeeds, the edge connects two previously
            // disjoint components without creating a cycle.
            if (dsu.unite(e.u, e.v)) {
                cout << e.u << " - " << e.v
                     << " : " << e.weight << '\n';
                totalWeight += e.weight;
                selected++;
            }
        }

        // Step 5: Check if graph was disconnected (less than V - 1 edges selected).
        if (selected != vertices - 1)
            cout << "Graph is disconnected; no spanning tree exists.\n";
        else
            cout << "Total MST weight: " << totalWeight << '\n';
    }

    // Destructor: Free dynamic edge array.
    ~EdgeListGraph() {
        delete[] edgeList;
    }
};

// ----------------------------------------------------------------------------
// Demonstration Driver
// ----------------------------------------------------------------------------
int main() {
    // Construct a sample graph with 4 vertices and 5 edges:
    // Vertices: 0, 1, 2, 3
    EdgeListGraph graph(4, 5);

    graph.addEdge(0, 1, 10, 0);  // Edge (0 - 1) weight 10
    graph.addEdge(0, 2, 6, 1);   // Edge (0 - 2) weight 6
    graph.addEdge(0, 3, 5, 2);   // Edge (0 - 3) weight 5
    graph.addEdge(1, 3, 15, 3);  // Edge (1 - 3) weight 15
    graph.addEdge(2, 3, 4, 4);   // Edge (2 - 3) weight 4

    // Run Kruskal's algorithm:
    // Expected output edges: (2-3: 4), (0-3: 5), (0-1: 10) -> Total weight: 19
    graph.kruskalMST();

    return 0;
}
