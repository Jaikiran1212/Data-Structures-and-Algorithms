
#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

// This program implements a min priority queue using an array-based binary heap.

class PriorityQueue {
    struct Item {
        int vertex;
        int priority;
    };

    Item* heap;
    int size;
    int capacity;

    void swapItems(int i, int j) {
        Item temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (heap[parent].priority <= heap[i].priority)
                break;

            swapItems(parent, i);
            i = parent;
        }
    }

    void heapifyDown(int i) {
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < size &&
                heap[left].priority < heap[smallest].priority)
                smallest = left;

            if (right < size &&
                heap[right].priority < heap[smallest].priority)
                smallest = right;

            if (smallest == i)
                break;

            swapItems(i, smallest);
            i = smallest;
        }
    }

public:
    PriorityQueue(int maxSize) {
        capacity = maxSize;
        size = 0;
        heap = new Item[capacity];
    }

    bool empty() {
        return size == 0;
    }

    // Insert a vertex with its priority.
    void insert(int vertex, int priority) {
        if (size == capacity)
            return;

        heap[size] = {vertex, priority};
        heapifyUp(size);
        size++;
    }

    // Return the vertex and priority with the smallest priority.
    bool extractMin(int& vertex, int& priority) {
        if (size == 0)
            return false;

        vertex = heap[0].vertex;
        priority = heap[0].priority;

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return true;
    }

    ~PriorityQueue() {
        delete[] heap;
    }
};

#endif
