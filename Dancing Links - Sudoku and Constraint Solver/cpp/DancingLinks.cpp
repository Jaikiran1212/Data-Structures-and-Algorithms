#include "DancingLinks.h"

DancingLinks::DancingLinks(int columns, int maxNodes) {
    numColumns = columns;
    int total = numColumns + 1 + maxNodes;

    left = new int[total];
    right = new int[total];
    up = new int[total];
    down = new int[total];
    columnOf = new int[total];
    rowIdOf = new int[total];
    columnSize = new int[numColumns + 1];
    chosenRows = new int[numColumns + 1];
    firstSolution = new int[numColumns + 1];

    // Build the header row: root(0) <-> 1 <-> 2 <-> ... <-> numColumns <-> root
    for (int c = 0; c <= numColumns; c++) {
        up[c] = c;              // empty column: points to itself
        down[c] = c;
        columnOf[c] = c;
        left[c] = c - 1;
        right[c] = c + 1;
        columnSize[c] = 0;
    }
    left[0] = numColumns;       // make the header list circular
    right[numColumns] = 0;

    nodeCount = numColumns + 1;
    firstSolutionLength = 0;
    solutionCount = 0;
    maxSolutions = 1;
    searchSteps = 0;
}

DancingLinks::~DancingLinks() {
    delete[] left;
    delete[] right;
    delete[] up;
    delete[] down;
    delete[] columnOf;
    delete[] rowIdOf;
    delete[] columnSize;
    delete[] chosenRows;
    delete[] firstSolution;
}

void DancingLinks::addRow(int rowId, const int columns[], int count) {
    int firstNodeInRow = -1;

    for (int i = 0; i < count; i++) {
        int col = columns[i] + 1;       // +1 because node 0 is the root
        int node = nodeCount;
        nodeCount++;

        columnOf[node] = col;
        rowIdOf[node] = rowId;

        // put the node at the BOTTOM of its column
        up[node] = up[col];
        down[node] = col;
        down[up[col]] = node;
        up[col] = node;
        columnSize[col]++;

        // link the node into the circular list for this row
        if (firstNodeInRow == -1) {
            firstNodeInRow = node;
            left[node] = node;
            right[node] = node;
        } else {
            left[node] = left[firstNodeInRow];
            right[node] = firstNodeInRow;
            right[left[firstNodeInRow]] = node;
            left[firstNodeInRow] = node;
        }
    }
}

int DancingLinks::solve(int limit) {
    maxSolutions = limit;
    solutionCount = 0;
    searchSteps = 0;
    firstSolutionLength = 0;

    search(0);
    return solutionCount;
}

int DancingLinks::getFirstSolution(int answer[]) const {
    for (int i = 0; i < firstSolutionLength; i++) {
        answer[i] = firstSolution[i];
    }
    return firstSolutionLength;
}

long long DancingLinks::getSearchSteps() const {
    return searchSteps;
}

// ------------------------------------------------------------------
// The recursive search (Knuth's Algorithm X)
// ------------------------------------------------------------------
void DancingLinks::search(int depth) {
    // No columns left in the header list -> everything is covered -> a solution!
    if (right[0] == 0) {
        solutionCount++;
        if (solutionCount == 1) {
            for (int i = 0; i < depth; i++) {
                firstSolution[i] = chosenRows[i];
            }
            firstSolutionLength = depth;
        }
        return;
    }

    // Pick the column with the FEWEST nodes. This is what makes DLX fast:
    // we always attack the most constrained column first.
    int bestColumn = right[0];
    for (int c = right[0]; c != 0; c = right[c]) {
        if (columnSize[c] < columnSize[bestColumn]) {
            bestColumn = c;
        }
    }

    // A column with zero rows can never be covered -> dead end, go back.
    if (columnSize[bestColumn] == 0) {
        return;
    }

    cover(bestColumn);

    // Try every row that covers this column
    for (int r = down[bestColumn]; r != bestColumn; r = down[r]) {
        searchSteps++;
        chosenRows[depth] = rowIdOf[r];

        // choosing row r means all its other columns are now covered too
        for (int j = right[r]; j != r; j = right[j]) {
            cover(columnOf[j]);
        }

        search(depth + 1);

        // undo in the OPPOSITE order (this order is important!)
        for (int j = left[r]; j != r; j = left[j]) {
            uncover(columnOf[j]);
        }

        if (solutionCount >= maxSolutions) {
            break;      // we have enough solutions, stop trying more rows
        }
    }

    uncover(bestColumn);
}

// Remove a column from the header list, and remove every row that
// uses this column from all the OTHER columns.
void DancingLinks::cover(int col) {
    right[left[col]] = right[col];
    left[right[col]] = left[col];

    for (int i = down[col]; i != col; i = down[i]) {
        for (int j = right[i]; j != i; j = right[j]) {
            down[up[j]] = down[j];
            up[down[j]] = up[j];
            columnSize[columnOf[j]]--;
        }
    }
}

// Exactly undoes cover(). Everything goes in reverse order.
void DancingLinks::uncover(int col) {
    for (int i = up[col]; i != col; i = up[i]) {
        for (int j = left[i]; j != i; j = left[j]) {
            columnSize[columnOf[j]]++;
            down[up[j]] = j;
            up[down[j]] = j;
        }
    }

    right[left[col]] = col;
    left[right[col]] = col;
}
