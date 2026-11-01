#include <iostream>
#include "DSU.h"
#include "MinHeap.h"
#include "PriorityQueue.h"
using namespace std;

int main() {
    // -------------------------------------------------------------
    // 1. DSU (Disjoint Set Union) Demonstration
    // -------------------------------------------------------------
    cout << "=== DSU Demonstration ===" << endl;

    // Create DSU structure for 6 elements (labeled 0 through 5).
    DSU dsu(6);

    // Merge pairs to form components:
    // Component A: {0, 1, 2}
    // Component B: {3, 4}
    // Component C: {5}
    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    // Check connectivity:
    // 0 and 2 are in Component A -> Expected: 1 (true)
    cout << "Connected(0, 2): " << dsu.connected(0, 2) << endl;

    // 0 is in Component A, 4 is in Component B -> Expected: 0 (false)
    cout << "Connected(0, 4): " << dsu.connected(0, 4) << endl;

    // Unite Component A and Component B by merging vertices 2 and 4.
    dsu.unite(2, 4);

    // Now 0 and 4 are in the same merged component {0, 1, 2, 3, 4} -> Expected: 1 (true)
    cout << "Connected(0, 4) after unite(2, 4): " << dsu.connected(0, 4) << endl;


    // -------------------------------------------------------------
    // 2. MinHeap (Edges) Demonstration
    // -------------------------------------------------------------
    cout << "\n=== MinHeap (Edges) Demonstration ===" << endl;

    // Create edge min-heap with capacity for 5 edges.
    MinHeap edgeHeap(5);

    // Insert edges with varying weights in arbitrary order.
    edgeHeap.insert(0, 1, 10);  // Edge (0 - 1) weight 10
    edgeHeap.insert(1, 2, 5);   // Edge (1 - 2) weight 5
    edgeHeap.insert(2, 3, 20);  // Edge (2 - 3) weight 20

    // Extract edges repeatedly: they should appear in ascending order of weight (5, then 10, then 20).
    int u, v, w;
    while (edgeHeap.extractMin(u, v, w)) {
        cout << "Extracted edge: " << u << " - " << v << " (weight: " << w << ")" << endl;
    }


    // -------------------------------------------------------------
    // 3. PriorityQueue (Vertices) Demonstration
    // -------------------------------------------------------------
    cout << "\n=== PriorityQueue (Vertices) Demonstration ===" << endl;

    // Create vertex priority queue with capacity for 5 items.
    PriorityQueue pq(5);

    // Insert vertices with their tentative distances/priorities.
    pq.insert(0, 15);  // Vertex 0 with priority 15
    pq.insert(1, 5);   // Vertex 1 with priority 5
    pq.insert(2, 25);  // Vertex 2 with priority 25

    // Extract vertices repeatedly: vertex with lowest priority value comes out first (1, then 0, then 2).
    int vertex, priority;
    while (pq.extractMin(vertex, priority)) {
        cout << "Extracted vertex: " << vertex << " (priority: " << priority << ")" << endl;
    }

    return 0;
}
