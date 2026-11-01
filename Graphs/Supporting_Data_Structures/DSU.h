#ifndef DSU_H
#define DSU_H

// Disjoint Set Union (DSU) / Union-Find Data Structure
// Supports:
// 1. find(x)     - determines which set an element belongs to (with Path Compression)
// 2. unite(x, y) - merges two sets together (with Union by Rank)
// 3. connected(x, y) - checks if two elements share the same set
//
// Time Complexity: Nearly O(1) amortized time per operation: O(alpha(n)),
// where alpha is the extremely slow-growing Inverse Ackermann function.
//
// Graph Use Cases:
// - Cycle detection in undirected graphs.
// - Finding connected components.
// - Kruskal's Algorithm for Minimum Spanning Trees (MST).

class DSU {
    int* parent;   // parent[i] points to the parent of node i; if parent[i] == i, i is the set representative (root).
    int* rankArr;  // rankArr[i] approximates tree height rooted at i, used to keep trees balanced when merging.
    int n;         // Total number of elements in the universe.

public:
    // Constructor: initializes 'size' disjoint sets where each element is initially its own root.
    DSU(int size) {
        n = size;
        parent = new int[n];
        rankArr = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i;  // Every element is initially its own parent/representative.
            rankArr[i] = 0;  // Initial tree height/rank of a single node is 0.
        }
    }

    // find(x): Finds the representative (root) of the set containing element x.
    // Uses "Path Compression": directly links all visited nodes along the path to the root.
    // This dramatically flattens the tree so future lookups execute in almost O(1) time.
    int find(int x) {
        // If x is not its own parent, recursively find the root and compress the path.
        if (parent[x] != x)
            parent[x] = find(parent[x]);  // Path compression step.

        return parent[x];  // Return the root representative.
    }

    // unite(x, y): Merges the set containing x with the set containing y.
    // Uses "Union by Rank": attaches the shallower tree under the deeper tree to prevent tall, skewed chains.
    // Returns:
    // - false if x and y were ALREADY in the same set (adding an edge between them forms a cycle!).
    // - true if a new merge occurred.
    bool unite(int x, int y) {
        int rootX = find(x);  // Find the representative root of x.
        int rootY = find(y);  // Find the representative root of y.

        // If both elements share the same root, they are already part of the same connected component.
        if (rootX == rootY)
            return false;

        // Union by rank: attach the tree with smaller rank under the tree with larger rank.
        if (rankArr[rootX] < rankArr[rootY]) {
            parent[rootX] = rootY;  // rootY has greater depth; make it the parent of rootX.
        }
        else if (rankArr[rootX] > rankArr[rootY]) {
            parent[rootY] = rootX;  // rootX has greater depth; make it the parent of rootY.
        }
        else {
            // If ranks are equal, pick either as parent and increment its rank by 1.
            parent[rootY] = rootX;
            rankArr[rootX]++;
        }

        return true;  // Sets were successfully united.
    }

    // connected(x, y): Checks whether vertices x and y belong to the same component/set.
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    // Destructor: releases all dynamically allocated memory.
    ~DSU() {
        delete[] parent;
        delete[] rankArr;
    }
};

#endif
