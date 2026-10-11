#include "SudokuSolver.h"
#include <iostream>

const int NUM_COLUMNS = 324;
const int MAX_NODES = 729 * 4;      // 9 * 9 * 9 moves, 4 columns each

SudokuSolver::SudokuSolver() {
    lastSearchSteps = 0;
}

bool SudokuSolver::solve(const int puzzle[9][9], int solved[9][9]) {
    DancingLinks* dlx = buildMatrix(puzzle);
    int found = dlx->solve(1);
    lastSearchSteps = dlx->getSearchSteps();

    if (found == 0) {
        delete dlx;
        return false;
    }

    // Turn the chosen row ids back into a filled grid
    int chosen[NUM_COLUMNS];
    int length = dlx->getFirstSolution(chosen);

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            solved[r][c] = 0;
        }
    }
    for (int i = 0; i < length; i++) {
        int id = chosen[i];
        int r = id / 81;
        int c = (id / 9) % 9;
        int digit = id % 9 + 1;
        solved[r][c] = digit;
    }

    delete dlx;
    return true;
}

int SudokuSolver::countSolutions(const int puzzle[9][9]) {
    DancingLinks* dlx = buildMatrix(puzzle);
    int found = dlx->solve(2);
    delete dlx;
    return found;
}

long long SudokuSolver::getLastSearchSteps() const {
    return lastSearchSteps;
}

// Turn the puzzle into the exact cover matrix
DancingLinks* SudokuSolver::buildMatrix(const int puzzle[9][9]) {
    DancingLinks* dlx = new DancingLinks(NUM_COLUMNS, MAX_NODES);

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (puzzle[r][c] != 0) {
                // Cell already has a clue -> only ONE move is possible here
                addMove(dlx, r, c, puzzle[r][c] - 1);
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
void SudokuSolver::addMove(DancingLinks* dlx, int r, int c, int digit) {
    int box = (r / 3) * 3 + (c / 3);

    int covers[4];
    covers[0] = r * 9 + c;                  // cell constraint
    covers[1] = 81 + r * 9 + digit;         // row constraint
    covers[2] = 162 + c * 9 + digit;        // column constraint
    covers[3] = 243 + box * 9 + digit;      // box constraint

    int rowId = r * 81 + c * 9 + digit;     // we can decode r, c, digit from this later
    dlx->addRow(rowId, covers, 4);
}

void SudokuSolver::parse(const std::string& text, int grid[9][9]) {
    for (int i = 0; i < 81; i++) {
        char ch = text[i];
        int value = 0;
        if (ch >= '1' && ch <= '9') {
            value = ch - '0';
        }
        grid[i / 9][i % 9] = value;
    }
}

void SudokuSolver::print(const int grid[9][9]) {
    for (int r = 0; r < 9; r++) {
        if (r % 3 == 0 && r != 0) {
            std::cout << "------+-------+------" << std::endl;
        }
        for (int c = 0; c < 9; c++) {
            if (c % 3 == 0 && c != 0) {
                std::cout << "| ";
            }
            if (grid[r][c] == 0) {
                std::cout << ". ";
            } else {
                std::cout << grid[r][c] << " ";
            }
        }
        std::cout << std::endl;
    }
}
