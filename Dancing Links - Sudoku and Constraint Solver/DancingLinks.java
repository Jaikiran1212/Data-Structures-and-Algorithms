/*
 * DancingLinks.java
 * ------------------
 * A general "exact cover" solver using Knuth's Dancing Links (DLX) idea.
 *
 * What is exact cover?
 *   We have some COLUMNS (things that must be covered) and some ROWS
 *   (choices). Each row covers a few columns. We must pick rows so that
 *   EVERY column is covered EXACTLY ONCE.
 *
 * How the data is stored (all raw arrays, no objects):
 *   Every "1" in the matrix is a node. A node has 4 links:
 *   left, right, up, down  -> they form circular doubly linked lists.
 *   Node 0                 -> the root (the start of the column-header list)
 *   Nodes 1..numColumns    -> the column headers
 *   Nodes after that       -> the real data nodes (one per "1")
 *
 * The "dancing" trick:
 *   Removing a node from a doubly linked list is easy:
 *       right[left[x]] = right[x];   left[right[x]] = left[x];
 *   and x still remembers its own left/right, so putting it back is easy too.
 *   That makes undoing (backtracking) very cheap.
 */
public class DancingLinks {

    // ---- the 4 link arrays + extra info about every node ----
    private int[] left;
    private int[] right;
    private int[] up;
    private int[] down;
    private int[] columnOf;     // which column header does this node belong to?
    private int[] rowIdOf;      // which user-given row id does this node belong to?
    private int[] columnSize;   // how many nodes are still in each column

    private int numColumns;
    private int nodeCount;      // next free node index

    // ---- search state ----
    private int[] chosenRows;           // row ids chosen so far (the current partial solution)
    private int[] firstSolution;        // copy of the first full solution we find
    private int firstSolutionLength;
    private int solutionCount;
    private int maxSolutions;           // stop searching once we reach this many
    private long searchSteps;           // how many times we tried a row (for statistics)

    /**
     * @param numColumns number of constraints (columns) to cover
     * @param maxNodes   the maximum number of "1"s that will be added in total
     */
    public DancingLinks(int numColumns, int maxNodes) {
        this.numColumns = numColumns;
        int total = numColumns + 1 + maxNodes;

        left = new int[total];
        right = new int[total];
        up = new int[total];
        down = new int[total];
        columnOf = new int[total];
        rowIdOf = new int[total];
        columnSize = new int[numColumns + 1];

        // Build the header row: root(0) <-> 1 <-> 2 <-> ... <-> numColumns <-> root
        for (int c = 0; c <= numColumns; c++) {
            up[c] = c;              // empty column: points to itself
            down[c] = c;
            columnOf[c] = c;
            left[c] = c - 1;
            right[c] = c + 1;
        }
        left[0] = numColumns;       // make the header list circular
        right[numColumns] = 0;

        nodeCount = numColumns + 1;
    }

    /**
     * Adds one row (one choice) to the matrix.
     *
     * @param rowId   any number that identifies this row (we get it back in the answer)
     * @param columns the columns this row covers, numbered from 0 (so 0..numColumns-1)
     */
    public void addRow(int rowId, int[] columns) {
        int firstNodeInRow = -1;

        for (int i = 0; i < columns.length; i++) {
            int col = columns[i] + 1;           // +1 because node 0 is the root
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

    /**
     * Searches for solutions.
     *
     * @param limit stop after finding this many solutions (use 1 to just solve,
     *              2 to check "is the solution unique?")
     * @return how many solutions were found (at most limit)
     */
    public int solve(int limit) {
        maxSolutions = limit;
        solutionCount = 0;
        searchSteps = 0;
        firstSolution = new int[numColumns + 1];
        firstSolutionLength = 0;
        chosenRows = new int[numColumns + 1];

        search(0);
        return solutionCount;
    }

    /** Returns the row ids of the first solution found (empty array if none). */
    public int[] getFirstSolution() {
        int[] answer = new int[firstSolutionLength];
        for (int i = 0; i < firstSolutionLength; i++) {
            answer[i] = firstSolution[i];
        }
        return answer;
    }

    /** How many row attempts the last search made. */
    public long getSearchSteps() {
        return searchSteps;
    }

    // ------------------------------------------------------------------
    // The recursive search (Knuth's Algorithm X)
    // ------------------------------------------------------------------
    private void search(int depth) {
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

        // Pick the column with the FEWEST nodes (the "S heuristic").
        // This is what makes DLX fast: we always attack the most constrained column.
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
    private void cover(int col) {
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
    private void uncover(int col) {
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
}
