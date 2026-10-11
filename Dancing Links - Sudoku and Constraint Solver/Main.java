/*
 * Main.java
 * ----------
 * Runs several test cases for the Dancing Links solver.
 *
 *   Part 1: the classic exact cover example from Knuth's paper
 *   Part 2: Sudoku puzzles (easy, very hard, no solution, many solutions)
 */
public class Main {

    public static void main(String[] args) {
        System.out.println("=== PART 1: Generic exact cover ===");
        testKnuthExample();
        testNoSolutionExample();

        System.out.println();
        System.out.println("=== PART 2: Sudoku ===");
        runSudokuTest("Test 1: Easy puzzle",
            "530070000600195000098000060800060003400803001700020006060000280000419005000080079");

        runSudokuTest("Test 2: Very hard puzzle (Arto Inkala)",
            "800000000003600000070090200050007000000045700000100030001000068008500010090000400");

        runSudokuTest("Test 3: Puzzle with NO solution (two 5s in the first row)",
            "550070000600195000098000060800060003400803001700020006060000280000419005000080079");

        runSudokuTest("Test 4: Empty grid (many solutions, we just show one)",
            "000000000000000000000000000000000000000000000000000000000000000000000000000000000");

        // If you want to solve your own puzzle, change args or paste a string here
        if (args.length == 1 && args[0].length() == 81) {
            runSudokuTest("Your puzzle", args[0]);
        }
    }

    // ------------------------------------------------------------------
    // Part 1 tests
    // ------------------------------------------------------------------

    // Knuth's example: 7 columns (0..6) and 6 rows (A..F).
    //   A covers columns 0, 3, 6
    //   B covers columns 0, 3
    //   C covers columns 3, 4, 6
    //   D covers columns 2, 4, 5
    //   E covers columns 1, 2, 5, 6
    //   F covers columns 1, 6
    // The only exact cover is B, D, F.
    private static void testKnuthExample() {
        DancingLinks dlx = new DancingLinks(7, 30);
        String[] names = { "A", "B", "C", "D", "E", "F" };

        dlx.addRow(0, new int[] { 0, 3, 6 });
        dlx.addRow(1, new int[] { 0, 3 });
        dlx.addRow(2, new int[] { 3, 4, 6 });
        dlx.addRow(3, new int[] { 2, 4, 5 });
        dlx.addRow(4, new int[] { 1, 2, 5, 6 });
        dlx.addRow(5, new int[] { 1, 6 });

        int found = dlx.solve(10);
        System.out.println("Knuth example -> solutions found: " + found + " (expected 1)");

        int[] answer = dlx.getFirstSolution();
        System.out.print("Chosen rows: ");
        for (int i = 0; i < answer.length; i++) {
            System.out.print(names[answer[i]] + " ");
        }
        System.out.println("(expected B, D, F in some order)");
    }

    // Column 2 is not covered by any row, so no solution can exist.
    private static void testNoSolutionExample() {
        DancingLinks dlx = new DancingLinks(3, 10);
        dlx.addRow(0, new int[] { 0, 1 });
        dlx.addRow(1, new int[] { 0 });

        int found = dlx.solve(1);
        System.out.println("Impossible example -> solutions found: " + found + " (expected 0)");
    }

    // ------------------------------------------------------------------
    // Part 2 tests
    // ------------------------------------------------------------------

    private static void runSudokuTest(String title, String puzzleText) {
        System.out.println();
        System.out.println(title);

        int[][] puzzle = SudokuSolver.parse(puzzleText);
        SudokuSolver solver = new SudokuSolver();

        System.out.println("Puzzle:");
        SudokuSolver.print(puzzle);

        long startTime = System.nanoTime();
        int[][] solved = solver.solve(puzzle);
        long endTime = System.nanoTime();
        double milliseconds = (endTime - startTime) / 1000000.0;

        if (solved == null) {
            System.out.println("Result: no solution exists.");
            System.out.println("Time: " + milliseconds + " ms");
            return;
        }

        System.out.println("Solution:");
        SudokuSolver.print(solved);

        boolean valid = isValidSolution(solved) && matchesClues(puzzle, solved);
        int count = solver.countSolutions(puzzle);

        System.out.println("Valid Sudoku? " + valid);
        if (count == 1) {
            System.out.println("Unique solution? yes");
        } else {
            System.out.println("Unique solution? no (more than one exists)");
        }
        System.out.println("Row attempts made by DLX: " + solver.getLastSearchSteps());
        System.out.println("Time: " + milliseconds + " ms");
    }

    // Independent check (does not use DLX): every row, column and box must have 1..9 once
    private static boolean isValidSolution(int[][] grid) {
        for (int i = 0; i < 9; i++) {
            boolean[] seenInRow = new boolean[10];
            boolean[] seenInColumn = new boolean[10];
            boolean[] seenInBox = new boolean[10];

            for (int j = 0; j < 9; j++) {
                int rowValue = grid[i][j];
                int columnValue = grid[j][i];
                int boxValue = grid[(i / 3) * 3 + j / 3][(i % 3) * 3 + j % 3];

                if (rowValue < 1 || seenInRow[rowValue]) return false;
                if (columnValue < 1 || seenInColumn[columnValue]) return false;
                if (boxValue < 1 || seenInBox[boxValue]) return false;

                seenInRow[rowValue] = true;
                seenInColumn[columnValue] = true;
                seenInBox[boxValue] = true;
            }
        }
        return true;
    }

    // The solution must keep every original clue
    private static boolean matchesClues(int[][] puzzle, int[][] solved) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (puzzle[r][c] != 0 && puzzle[r][c] != solved[r][c]) {
                    return false;
                }
            }
        }
        return true;
    }
}
