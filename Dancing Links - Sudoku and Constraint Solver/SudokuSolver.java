/*
 * SudokuSolver.java
 * ------------------
 * Solves a 9x9 Sudoku by turning it into an exact cover problem and giving
 * it to DancingLinks.
 *
 * The 4 rules of Sudoku become 4 groups of 81 columns = 324 columns:
 *   Group 0 (cols   0..80 ) : every CELL has exactly one digit
 *   Group 1 (cols  81..161) : every ROW contains each digit exactly once
 *   Group 2 (cols 162..242) : every COLUMN contains each digit exactly once
 *   Group 3 (cols 243..323) : every 3x3 BOX contains each digit exactly once
 *
 * Every possible move "put digit d in cell (r, c)" is one row of the matrix.
 * It covers exactly 4 columns (one from each group).
 * There are 9 * 9 * 9 = 729 possible moves, so at most 729 rows.
 */
public class SudokuSolver {

    private static final int NUM_COLUMNS = 324;
    private static final int MAX_NODES = 729 * 4;

    private long lastSearchSteps = 0;

    /**
     * Solves the puzzle.
     *
     * @param puzzle 9x9 grid, 0 means empty cell
     * @return the solved 9x9 grid, or null if the puzzle has no solution
     */
    public int[][] solve(int[][] puzzle) {
        DancingLinks dlx = buildMatrix(puzzle);
        int found = dlx.solve(1);
        lastSearchSteps = dlx.getSearchSteps();

        if (found == 0) {
            return null;
        }
        return decode(dlx.getFirstSolution());
    }

    /**
     * Counts solutions, but stops at 2 (we only care about 0, 1, or "many").
     * A proper Sudoku has exactly 1 solution.
     */
    public int countSolutions(int[][] puzzle) {
        DancingLinks dlx = buildMatrix(puzzle);
        return dlx.solve(2);
    }

    public long getLastSearchSteps() {
        return lastSearchSteps;
    }

    // Turn the puzzle into the exact cover matrix
    private DancingLinks buildMatrix(int[][] puzzle) {
        DancingLinks dlx = new DancingLinks(NUM_COLUMNS, MAX_NODES);

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {

                if (puzzle[r][c] != 0) {
                    // Cell already has a clue -> only ONE move is possible here
                    int digit = puzzle[r][c] - 1;      // 0..8 inside the code
                    addMove(dlx, r, c, digit);
                } else {
                    // Empty cell -> any of the 9 digits could go here
                    for (int digit = 0; digit < 9; digit++) {
                        addMove(dlx, r, c, digit);
                    }
                }
            }
        }
        return dlx;
    }

    // Adds the row for "put digit in cell (r, c)"
    private void addMove(DancingLinks dlx, int r, int c, int digit) {
        int box = (r / 3) * 3 + (c / 3);

        int cellColumn = r * 9 + c;
        int rowColumn = 81 + r * 9 + digit;
        int colColumn = 162 + c * 9 + digit;
        int boxColumn = 243 + box * 9 + digit;

        int rowId = r * 81 + c * 9 + digit;     // we can decode r, c, digit from this later

        int[] covers = { cellColumn, rowColumn, colColumn, boxColumn };
        dlx.addRow(rowId, covers);
    }

    // Turn the chosen row ids back into a filled grid
    private int[][] decode(int[] chosenRowIds) {
        int[][] grid = new int[9][9];

        for (int i = 0; i < chosenRowIds.length; i++) {
            int id = chosenRowIds[i];
            int r = id / 81;
            int c = (id / 9) % 9;
            int digit = id % 9 + 1;
            grid[r][c] = digit;
        }
        return grid;
    }

    // ------------------------------------------------------------------
    // Small helper methods for reading and printing grids
    // ------------------------------------------------------------------

    /** Reads a puzzle from an 81-character string. Use 0 or . for empty cells. */
    public static int[][] parse(String text) {
        int[][] grid = new int[9][9];
        for (int i = 0; i < 81; i++) {
            char ch = text.charAt(i);
            int value = 0;
            if (ch >= '1' && ch <= '9') {
                value = ch - '0';
            }
            grid[i / 9][i % 9] = value;
        }
        return grid;
    }

    /** Prints the grid with box lines so it is easy to read. */
    public static void print(int[][] grid) {
        for (int r = 0; r < 9; r++) {
            if (r % 3 == 0 && r != 0) {
                System.out.println("------+-------+------");
            }
            for (int c = 0; c < 9; c++) {
                if (c % 3 == 0 && c != 0) {
                    System.out.print("| ");
                }
                if (grid[r][c] == 0) {
                    System.out.print(". ");
                } else {
                    System.out.print(grid[r][c] + " ");
                }
            }
            System.out.println();
        }
    }
}
