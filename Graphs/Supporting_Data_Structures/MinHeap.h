#ifndef MINHEAP_H
#define MINHEAP_H

// Binary Min-Heap for Graph Edges
//
// A specialized complete binary tree maintained in a contiguous array.
// Stores graph edges (u, v, w) and keeps the minimum-weight edge at the root (index 0).
//
// Array-based Binary Tree Layout:
// - Parent of node at index i:      (i - 1) / 2
// - Left child of node at index i:  2 * i + 1
// - Right child of node at index i: 2 * i + 2
//
// Time Complexity:
// - insert():     O(log E)
// - extractMin(): O(log E)
// - getMin():     O(1)
//
// Graph Use Case:
// - Kruskal's Minimum Spanning Tree algorithm: greedily inspects edges in increasing weight order.

class MinHeap {
    // Structure representing an undirected weighted graph edge.
    struct Edge {
        int u;  // Source vertex
        int v;  // Destination vertex
        int w;  // Edge weight (used as the heap comparison key)
    };

    Edge* heap;    // Contiguous array storing heap elements.
    int size;      // Current number of edges stored in the heap.
    int capacity;  // Maximum capacity of the heap array.

    // Helper: Swaps two edges at indices i and j in the heap array.
    void swapEdges(int i, int j) {
        Edge temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // heapifyUp(i): Restores the min-heap invariant after inserting an element at index i.
    // Bubbles the element UP towards the root as long as its weight is smaller than its parent's.
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;  // Calculate parent index in 0-based array.

            // If the parent's weight is already smaller than or equal to current, invariant is satisfied.
            if (heap[parent].w <= heap[i].w)
                break;

            // Otherwise, swap with parent and continue moving up.
            swapEdges(parent, i);
            i = parent;
        }
    }

    // heapifyDown(i): Restores the min-heap invariant after extracting the root.
    // Sifts the element at index i DOWN by swapping it with its smallest child until invariant holds.
    void heapifyDown(int i) {
        while (true) {
            int smallest = i;           // Assume current node has the smallest key.
            int left = 2 * i + 1;       // Left child index.
            int right = 2 * i + 2;      // Right child index.

            // Check if left child exists and has a smaller weight than current smallest.
            if (left < size && heap[left].w < heap[smallest].w)
                smallest = left;

            // Check if right child exists and has a smaller weight than current smallest.
            if (right < size && heap[right].w < heap[smallest].w)
                smallest = right;

            // If current node is smaller than both children, heap property is restored.
            if (smallest == i)
                break;

            // Swap with the smaller child and continue moving down.
            swapEdges(i, smallest);
            i = smallest;
        }
    }

public:
    // Constructor: Allocates fixed-capacity array for the heap.
    MinHeap(int maxSize) {
        capacity = maxSize;
        size = 0;
        heap = new Edge[capacity];
    }

    // Returns true if the heap contains no elements.
    bool empty() {
        return size == 0;
    }

    // Returns current number of edges stored in the heap.
    int getSize() {
        return size;
    }

    // insert(u, v, w): Inserts a new edge and restores the min-heap property in O(log E) time.
    void insert(int u, int v, int w) {
        // Prevent overflow if capacity is reached.
        if (size == capacity)
            return;

        // Place new edge at the next available slot at the end of the array.
        heap[size] = {u, v, w};

        // Bubble up the new edge to its correct position.
        heapifyUp(size);
        size++;
    }

    // getMin(u, v, w): Peeks at the minimum-weight edge at index 0 without removing it (O(1)).
    void getMin(int& u, int& v, int& w) {
        if (size == 0)
            return;

        u = heap[0].u;
        v = heap[0].v;
        w = heap[0].w;
    }

    // extractMin(u, v, w): Removes and returns the minimum-weight edge in O(log E) time.
    bool extractMin(int& u, int& v, int& w) {
        // Return false if heap is empty.
        if (size == 0)
            return false;

        // Retrieve the root element (minimum weight).
        u = heap[0].u;
        v = heap[0].v;
        w = heap[0].w;

        // Overwrite the root with the last element in the heap.
        heap[0] = heap[size - 1];
        size--;

        // Sift down the new root to restore the min-heap property.
        if (size > 0)
            heapifyDown(0);

        return true;
    }

    // Destructor: Deallocates the dynamic heap array.
    ~MinHeap() {
        delete[] heap;
    }
};

#endif
