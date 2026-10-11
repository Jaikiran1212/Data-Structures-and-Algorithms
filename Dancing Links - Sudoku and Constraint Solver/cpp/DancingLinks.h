/*
 * DancingLinks.h
 * ---------------
 * A general "exact cover" solver using Knuth's Dancing Links (DLX) idea.
 *
 * What is exact cover?
 *   We have some COLUMNS (things that must be covered) and some ROWS
 *   (choices). Each row covers a few columns. We must pick rows so that
 *   EVERY column is covered EXACTLY ONCE.
 *
 * How the data is stored (all raw arrays, no STL containers):
 *   Every "1" in the matrix is a node. A node has 4 links:
 *   left, right, up, down  -> they form circular doubly linked lists.
 *   Node 0                 -> the root (the start of the column-header list)
 *   Nodes 1..numColumns    -> the column headers
 *   Nodes after that       -> the real data nodes (one per "1")
 */
#ifndef DANCING_LINKS_H
#define DANCING_LINKS_H

class DancingLinks {
private:
    // ---- the 4 link arrays + extra info about every node ----
    int* left;
    int* right;
    int* up;
    int* down;
    int* columnOf;      // which column header does this node belong to?
    int* rowIdOf;       // which user-given row id does this node belong to?
    int* columnSize;    // how many nodes are still in each column

    int numColumns;
    int nodeCount;      // next free node index

    // ---- search state ----
    int* chosenRows;            // row ids chosen so far (the current partial solution)
    int* firstSolution;         // copy of the first full solution we find
    int firstSolutionLength;
    int solutionCount;
    int maxSolutions;           // stop searching once we reach this many
    long long searchSteps;      // how many times we tried a row (for statistics)

    void search(int depth);
    void cover(int col);
    void uncover(int col);

    // Copying is not allowed (the class owns raw arrays)
    DancingLinks(const DancingLinks&);
    DancingLinks& operator=(const DancingLinks&);

public:
    // numColumns = number of constraints, maxNodes = total number of "1"s we will add
    DancingLinks(int columns, int maxNodes);
    ~DancingLinks();

    // Adds one row. rowId is any number you choose, columns are numbered from 0.
    void addRow(int rowId, const int columns[], int count);

    // Searches for solutions. Stops after "limit" solutions.
    // Use 1 to just solve, 2 to check "is the solution unique?".
    // Returns how many solutions were found.
    int solve(int limit);

    // Copies the row ids of the first solution into answer[] and returns how many there are.
    // answer[] must have room for at least (numColumns) numbers.
    int getFirstSolution(int answer[]) const;

    // How many row attempts the last search made
    long long getSearchSteps() const;
};

#endif
