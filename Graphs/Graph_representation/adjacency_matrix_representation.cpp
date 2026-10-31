// This program represents a weighted graph using a matrix with O(V^2) space.

#include <iostream>
using namespace std;

class AdjacencyMatrix {
    int** matrix;
    int vertices;

public:
    AdjacencyMatrix(int n) {
        vertices = n;
        matrix = new int*[n];

        for (int i = 0; i < n; i++) {
            matrix[i] = new int[n];

            for (int j = 0; j < n; j++)
                matrix[i][j] = 0;
        }
    }

    void insertEdge(int u, int v, int w) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices)
            return;

        matrix[u][v] = w;
        matrix[v][u] = w;
    }

    void display() {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++)
                cout << matrix[i][j] << " ";

            cout << endl;
        }
    }

    ~AdjacencyMatrix() {
        for (int i = 0; i < vertices; i++)
            delete[] matrix[i];

        delete[] matrix;
    }
};

int main() {
    AdjacencyMatrix g(4);

    g.insertEdge(0, 1, 10);
    g.insertEdge(0, 2, 20);
    g.insertEdge(1, 3, 30);

    g.display();
    return 0;
}