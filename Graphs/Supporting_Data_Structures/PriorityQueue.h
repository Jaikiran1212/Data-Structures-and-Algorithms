#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

// Min-Priority Queue for Graph Vertices
//
// An array-based binary min-heap keyed on numerical priority (e.g. tentative distance).
// Guarantees that the vertex with the lowest numerical priority value stays at root index 0.
//
// Array-based Binary Tree Layout:
// - Parent of node at index i:      (i - 1) / 2
// - Left child of node at index i:  2 * i + 1
// - Right child of node at index i: 2 * i + 2
//
// Time Complexity:
// - insert():     O(log V)
// - extractMin(): O(log V)
// - empty():      O(1)
//
// Graph Use Cases:
// - Dijkstra's Algorithm: Greedily extracts the unvisited vertex with the minimum tentative distance.
// - Prim's Algorithm: Greedily selects the lowest-weight cut edge connecting to the growing MST.

class PriorityQueue {
    // Structure representing an item in the priority queue.
    struct Item {
        int vertex;    // Target vertex index
        int priority;  // Key used for ordering (e.g. shortest distance or cut weight)
    };

    Item* heap;    // Contiguous array storing binary heap items.
    int size;      // Current number of items in the queue.
    int capacity;  // Maximum capacity of the array.

    // Helper: Swaps two items at indices i and j in the heap array.
    void swapItems(int i, int j) {
        Item temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // heapifyUp(i): Restores min-heap property after inserting a new item at index i.
    // Bubbles the item UP towards root as long as its priority is lower than its parent's.
    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;  // Calculate parent index in 0-based indexing.

            // If parent's priority is already smaller or equal, invariant holds.
            if (heap[parent].priority <= heap[i].priority)
                break;

            // Otherwise, swap with parent and climb up.
            swapItems(parent, i);
            i = parent;
        }
    }

    // heapifyDown(i): Restores min-heap property after removing the root.
    // Sifts the item at index i DOWN by swapping with its lowest-priority child.
    void heapifyDown(int i) {
        while (true) {
            int smallest = i;           // Assume current index is the smallest.
            int left = 2 * i + 1;       // Left child index.
            int right = 2 * i + 2;      // Right child index.

            // Check if left child exists and has smaller priority than current smallest.
            if (left < size && heap[left].priority < heap[smallest].priority)
                smallest = left;

            // Check if right child exists and has smaller priority than current smallest.
            if (right < size && heap[right].priority < heap[smallest].priority)
                smallest = right;

            // If current element is smaller than both children, invariant is restored.
            if (smallest == i)
                break;

            // Swap with smaller child and continue descending.
            swapItems(i, smallest);
            i = smallest;
        }
    }

public:
    // Constructor: Allocates fixed-capacity array for the priority queue.
    PriorityQueue(int maxSize) {
        capacity = maxSize;
        size = 0;
        heap = new Item[capacity];
    }

    // Returns true if the priority queue is empty.
    bool empty() {
        return size == 0;
    }

    // insert(vertex, priority): Inserts a vertex with its priority value in O(log V) time.
    void insert(int vertex, int priority) {
        // Prevent overflow if capacity limit is reached.
        if (size == capacity)
            return;

        // Place new item at the next available slot.
        heap[size] = {vertex, priority};

        // Bubble up to restore the min-heap property.
        heapifyUp(size);
        size++;
    }

    // extractMin(vertex, priority): Removes and returns the vertex with lowest priority in O(log V) time.
    bool extractMin(int& vertex, int& priority) {
        // Return false if priority queue is empty.
        if (size == 0)
            return false;

        // Retrieve the root element (lowest priority).
        vertex = heap[0].vertex;
        priority = heap[0].priority;

        // Overwrite root with the last element.
        heap[0] = heap[size - 1];
        size--;

        // Sift down the new root element to restore heap order.
        if (size > 0)
            heapifyDown(0);

        return true;
    }

    // Destructor: Deallocates the dynamic heap buffer.
    ~PriorityQueue() {
        delete[] heap;
    }
};

#endif
