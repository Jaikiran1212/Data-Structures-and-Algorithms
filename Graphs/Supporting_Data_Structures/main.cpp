#include <iostream>
#include "DSU.h"
#include "MinHeap.h"
#include "PriorityQueue.h"
using namespace std;

int main() {
    cout << "=== DSU Demonstration ===" << endl;
    DSU dsu(6);

    dsu.unite(0, 1);
    dsu.unite(1, 2);
    dsu.unite(3, 4);

    cout << "Connected(0, 2): " << dsu.connected(0, 2) << endl; // 1 (true)
    cout << "Connected(0, 4): " << dsu.connected(0, 4) << endl; // 0 (false)

    dsu.unite(2, 4);

    cout << "Connected(0, 4) after unite(2, 4): " << dsu.connected(0, 4) << endl; // 1 (true)

    cout << "\n=== MinHeap (Edges) Demonstration ===" << endl;
    MinHeap edgeHeap(5);
    edgeHeap.insert(0, 1, 10);
    edgeHeap.insert(1, 2, 5);
    edgeHeap.insert(2, 3, 20);

    int u, v, w;
    while (edgeHeap.extractMin(u, v, w)) {
        cout << "Extracted edge: " << u << " - " << v << " (weight: " << w << ")" << endl;
    }

    cout << "\n=== PriorityQueue (Vertices) Demonstration ===" << endl;
    PriorityQueue pq(5);
    pq.insert(0, 15);
    pq.insert(1, 5);
    pq.insert(2, 25);

    int vertex, priority;
    while (pq.extractMin(vertex, priority)) {
        cout << "Extracted vertex: " << vertex << " (priority: " << priority << ")" << endl;
    }

    return 0;
}
