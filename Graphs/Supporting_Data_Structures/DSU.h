
#ifndef DSU_H
#define DSU_H

// This program implements DSU with path compression and union by rank in nearly O(1) amortized time.

class DSU {
    int* parent;
    int* rankArr;
    int n;

public:
    DSU(int size) {
        n = size;
        parent = new int[n];
        rankArr = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rankArr[i] = 0;
        }
    }

    // Find the representative of a set and compress the path.
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    // Merge two sets if they are different.
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

    // Check whether two vertices belong to the same set.
    bool connected(int x, int y) {
        return find(x) == find(y);
    }

    ~DSU() {
        delete[] parent;
        delete[] rankArr;
    }
};

#endif
