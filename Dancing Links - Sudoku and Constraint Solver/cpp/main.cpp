/*
 * main.cpp
 * ---------
 * Runs several test cases for the Dancing Links solver.
 *
 *   Part 1: the classic exact cover example from Knuth's paper
 *   Part 2: Sudoku puzzles (easy, very hard, no solution, many solutions)
 */
#include <iostream>
#include <string>
#include <chrono>
#include "DancingLinks.h"
#include "SudokuSolver.h"

using namespace std;

// Knuth's example: 7 columns (0..6) and 6 rows (A..F).
//   A covers 0,3,6   B covers 0,3   C covers 3,4,6
//   D covers 2,4,5   E covers 1,2,5,6   F covers 1,6
// The only exact cover is B, D, F.
void testKnuthExample() {
    DancingLinks dlx(7, 30);
    string names[6] = { "A", "B", "C", "D", "E", "F" };

    int a[] = { 0, 3, 6 };
    int b[] = { 0, 3 };
    int c[] = { 3, 4, 6 };
    int d[] = { 2, 4, 5 };
    int e[] = { 1, 2, 5, 6 };
    int f[] = { 1, 6 };

    dlx.addRow(0, a, 3);
    dlx.addRow(1, b, 2);
    dlx.addRow(2, c, 3);
    dlx.addRow(3, d, 3);
    dlx.addRow(4, e, 4);
    dlx.addRow(5, f, 2);

    int found = dlx.solve(10);
    cout << "Knuth example -> solutions found: " << found << " (expected 1)" << endl;

    int answer[7];
    int length = dlx.getFirstSolution(answer);
    cout << "Chosen rows: ";
    for (int i = 0; i < length; i++) {
        cout << names[answer[i]] << " ";
    }
    cout << "(expected B, D, F in some order)" << endl;
}

// Column 2 is not covered by any row, so no solution can exist.
void testNoSolutionExample() {
    DancingLinks dlx(3, 10);
    int a[] = { 0, 1 };
    int b[] = { 0 };
    dlx.addRow(0, a, 2);
    dlx.addRow(1, b, 1);

    int found = dlx.solve(1);
    cout << "Impossible example -> solutions found: " << found << " (expected 0)" << endl;
}

// Independent check (does not use DLX): every row, column and box must have 1..9 once
bool isValidSolution(const int grid[9][9]) {
    for (int i = 0; i < 9; i++) {
        bool seenInRow[10] = { false };
        bool seenInColumn[10] = { false };
        bool seenInBox[10] = { false };

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
bool matchesClues(const int puzzle[9][9], const int solved[9][9]) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (puzzle[r][c] != 0 && puzzle[r][c] != solved[r][c]) {
                return false;
            }
        }
    }
    return true;
}

void runSudokuTest(const string& title, const string& puzzleText) {
    cout << endl << title << endl;

    int puzzle[9][9];
    int solved[9][9];
    SudokuSolver::parse(puzzleText, puzzle);
    SudokuSolver solver;

    cout << "Puzzle:" << endl;
    SudokuSolver::print(puzzle);

    auto startTime = chrono::steady_clock::now();
    bool ok = solver.solve(puzzle, solved);
    auto endTime = chrono::steady_clock::now();
    double milliseconds = chrono::duration<double, milli>(endTime - startTime).count();

    if (!ok) {
        cout << "Result: no solution exists." << endl;
        cout << "Time: " << milliseconds << " ms" << endl;
        return;
    }

    cout << "Solution:" << endl;
    SudokuSolver::print(solved);

    bool valid = isValidSolution(solved) && matchesClues(puzzle, solved);
    int count = solver.countSolutions(puzzle);

    cout << "Valid Sudoku? " << (valid ? "true" : "false") << endl;
    cout << "Unique solution? " << (count == 1 ? "yes" : "no (more than one exists)") << endl;
    cout << "Row attempts made by DLX: " << solver.getLastSearchSteps() << endl;
    cout << "Time: " << milliseconds << " ms" << endl;
}

int main(int argc, char* argv[]) {
    cout << "=== PART 1: Generic exact cover ===" << endl;
    testKnuthExample();
    testNoSolutionExample();

    cout << endl << "=== PART 2: Sudoku ===" << endl;
    runSudokuTest("Test 1: Easy puzzle",
        "530070000600195000098000060800060003400803001700020006060000280000419005000080079");

    runSudokuTest("Test 2: Very hard puzzle (Arto Inkala)",
        "800000000003600000070090200050007000000045700000100030001000068008500010090000400");

    runSudokuTest("Test 3: Puzzle with NO solution (two 5s in the first row)",
        "550070000600195000098000060800060003400803001700020006060000280000419005000080079");

    runSudokuTest("Test 4: Empty grid (many solutions, we just show one)",
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000");

    // Solve your own puzzle: ./dlx <81 characters>
    if (argc == 2 && string(argv[1]).length() == 81) {
        runSudokuTest("Your puzzle", argv[1]);
    }

    return 0;
}
