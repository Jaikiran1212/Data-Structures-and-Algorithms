/**
 * ============================================================================
 * Algorithm: Boruvka's Minimum Spanning Tree (MST)
 * ============================================================================
 * 
 * Overview:
 *   Boruvka's algorithm is the oldest known MST algorithm, published in 1926
 *   by Czech mathematician Otakar Boruvka for the electrification of Moravia.
 *   It constructs an MST by repeatedly finding and adding the cheapest outgoing
 *   edge for every connected component simultaneously.
 * 
 * Core Strategy:
 *   1. Begin with V disconnected components (every vertex is its own component).
 *   2. In each phase:
 *      a. Initialize a cheapest[] array with -1 for all components.
 *      b. Iterate through all E edges:
 *         - Determine the component IDs of both endpoints using DSU.
 *         - If they belong to different components, check if this edge is cheaper
 *           than the current known cheapest edge for either component. If so, update cheapest[].
 *      c. For each component, retrieve its cheapest outgoing edge. If this edge
 *         connects two distinct components in the DSU, unite them, add the edge to the
 *         MST, and decrement the component count.
 *   3. Repeat until only 1 component remains (or no new edges can be added).
 * 
 * Halving Invariant & Complexity:
 *   - Each phase reduces the number of components by at least half (components <= C / 2).
 *   - Therefore, there are at most ceil(log2 V) phases.
 *   - In each phase, all E edges are inspected in O(E * alpha(V)) time.
 *   - Total Time Complexity:  O(E log V)
 *   - Total Space Complexity: O(V + E) for the edge array, DSU, and cheapest tracker.
 * 
 * Historical & Practical Significance:
 *   Boruvka's algorithm is inherently parallelizable: every component can find its
 *   cheapest outgoing edge concurrently without inter-component locking, making it
 *   the foundation of state-of-the-art parallel and distributed MST algorithms.
 * ============================================================================
 */

#include <iostream>
using namespace std;

// ----------------------------------------------------------------------------
// Edge Representation
// ----------------------------------------------------------------------------
struct Edge {
    int u;       // Source vertex
    int v;       // Destination vertex
    int weight;  // Edge weight/cost
};

// ----------------------------------------------------------------------------
// Disjoint Set Union (DSU) with Path Compression and Union by Rank
// ----------------------------------------------------------------------------
class DSU {
private:
    int* parent;   // parent[i] points to parent node; if parent[i] == i, i is the set root.
    int* rankArr;  // rankArr[i] stores depth approximation for tree balancing.
    int n;         // Number of vertices.

public:
    // Initialize n disjoint sets where each vertex is initially its own representative.
    DSU(int n) {
        this->n = n;
        parent = new int[n];
        rankArr = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rankArr[i] = 0;
        }
    }

    // find(x): Finds root representative of vertex x with recursive Path Compression.
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Directly link to root to flatten tree.
        return parent[x];
    }

    // unite(x, y): Merges sets containing x and y using Union by Rank.
    // Returns false if x and y are already in the same set, true otherwise.
    bool unite(int x, int y) {
        int a = find(x);
        int b = find(y);

        if (a == b)
            return false;  // Already in the same component.

        // Attach shallower tree under deeper tree.
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

    // Destructor: Free DSU tracking arrays.
    ~DSU() {
        delete[] parent;
        delete[] rankArr;
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
    // Constructor: Allocate dynamic array for edges.
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

    // Boruvka's MST Algorithm:
    // Merges components in parallel phases using their cheapest outgoing edges.
    void boruvkaMST() {
        DSU dsu(vertices);                   // DSU to maintain active components
        int* cheapest = new int[vertices];   // cheapest[i] stores index of cheapest edge for component i

        int components = vertices;           // Initially, each vertex is its own component
        int totalWeight = 0;                 // Accumulated weight of the MST

        cout << "MST edges:\n";

        // Loop runs at most O(log V) times because each iteration halves the number of components.
        while (components > 1) {
            // Step 1: Reset the cheapest edge record for all components.
            for (int i = 0; i < vertices; i++)
                cheapest[i] = -1;

            // Step 2: Iterate through all edges to find the cheapest outgoing edge for each component.
            for (int i = 0; i < edges; i++) {
                int setU = dsu.find(edgeList[i].u);  // Component of vertex u
                int setV = dsu.find(edgeList[i].v);  // Component of vertex v

                // Ignore internal edges connecting vertices already within the same component.
                if (setU == setV)
                    continue;

                // Check if this edge is cheaper than the currently known cheapest edge for component setU.
                if (cheapest[setU] == -1 ||
                    edgeList[i].weight < edgeList[cheapest[setU]].weight)
                    cheapest[setU] = i;

                // Check if this edge is cheaper than the currently known cheapest edge for component setV.
                if (cheapest[setV] == -1 ||
                    edgeList[i].weight < edgeList[cheapest[setV]].weight)
                    cheapest[setV] = i;
            }

            int merged = 0;  // Track number of components merged in this round

            // Step 3: Add the identified cheapest edges to the MST.
            for (int i = 0; i < vertices; i++) {
                int edgeIndex = cheapest[i];

                // If component i has an outgoing edge:
                if (edgeIndex == -1)
                    continue;

                Edge e = edgeList[edgeIndex];

                // Unite the two components if not already joined during this phase.
                if (dsu.unite(e.u, e.v)) {
                    cout << e.u << " - " << e.v
                         << " : " << e.weight << '\n';

                    totalWeight += e.weight;
                    components--;
                    merged++;
                }
            }

            // If no edges could merge components, graph is disconnected.
            if (merged == 0)
                break;
        }

        // Step 4: Validate connectivity.
        if (components != 1)
            cout << "Graph is disconnected; no spanning tree exists.\n";
        else
            cout << "Total MST weight: " << totalWeight << '\n';

        // Clean up temporary tracking buffer.
        delete[] cheapest;
    }

    // Destructor: Free dynamic edge list.
    ~EdgeListGraph() {
        delete[] edgeList;
    }
};

// ----------------------------------------------------------------------------
// Demonstration Driver
// ----------------------------------------------------------------------------
int main() {
    // Construct a sample graph with 4 vertices and 5 edges:
    EdgeListGraph graph(4, 5);

    graph.addEdge(0, 1, 10, 0);  // Edge (0 - 1) weight 10
    graph.addEdge(0, 2, 6, 1);   // Edge (0 - 2) weight 6
    graph.addEdge(0, 3, 5, 2);   // Edge (0 - 3) weight 5
    graph.addEdge(1, 3, 15, 3);  // Edge (1 - 3) weight 15
    graph.addEdge(2, 3, 4, 4);   // Edge (2 - 3) weight 4
    // Run Boruvka's algorithm:
    // Expected output edges: (0-3: 5), (0-1: 10), (2-3: 4) -> Total weight: 19
    graph.boruvkaMST();

    return 0;
}
