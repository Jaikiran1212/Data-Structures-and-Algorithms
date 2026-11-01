
#ifndef MINHEAP_H
#define MINHEAP_H

// This program implements a MinHeap with O(log n) insertion and extraction.

class MinHeap {
    struct Edge {
        int u, v, w;
    };

    Edge* heap;
    int size;
    int capacity;

    void swapEdges(int i, int j) {
        Edge temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent].w <= heap[i].w)
                break;

            swapEdges(parent, i);
            i = parent;
        }
    }

    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size && heap[left].w < heap[smallest].w)
                smallest = left;

            if (right < size && heap[right].w < heap[smallest].w)
                smallest = right;

            if (smallest == i)
                break;

            swapEdges(i, smallest);
            i = smallest;
        }
    }

public:
    MinHeap(int maxSize) {
        capacity = maxSize;
        size = 0;
        heap = new Edge[capacity];
    }

    bool empty() {
        return size == 0;
    }

    int getSize() {
        return size;
    }

    // Insert an edge and restore the heap property.
    void insert(int u, int v, int w) {
        if (size == capacity)
            return;

        heap[size] = {u, v, w};
        heapifyUp(size);
        size++;
    }

    // Return the minimum-weight edge without removing it.
    void getMin(int& u, int& v, int& w) {
        if (size == 0)
            return;

        u = heap[0].u;
        v = heap[0].v;
        w = heap[0].w;
    }

    // Remove and return the minimum-weight edge.
    bool extractMin(int& u, int& v, int& w) {
        if (size == 0)
            return false;

        u = heap[0].u;
        v = heap[0].v;
        w = heap[0].w;

        heap[0] = heap[size - 1];
        size--;
        if (size > 0)
            heapifyDown(0);

        return true;
    }

    ~MinHeap() {
        delete[] heap;
    }
};

#endif
