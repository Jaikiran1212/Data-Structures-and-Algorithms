/*
 * SudokuSolver.h
 * ---------------
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
 */
#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include <string>
#include "DancingLinks.h"

class SudokuSolver {
private:
    long long lastSearchSteps;

    DancingLinks* buildMatrix(const int puzzle[9][9]);
    void addMove(DancingLinks* dlx, int r, int c, int digit);

public:
    SudokuSolver();

    // Solves the puzzle (0 = empty cell). Returns true and fills solved[][] if a solution exists.
    bool solve(const int puzzle[9][9], int solved[9][9]);

    // Counts solutions but stops at 2 (we only care about 0, 1 or "many").
    int countSolutions(const int puzzle[9][9]);

    long long getLastSearchSteps() const;

    // Helpers for reading and printing grids
    static void parse(const std::string& text, int grid[9][9]);   // 81 characters, 0 or . = empty
    static void print(const int grid[9][9]);
};

#endif
