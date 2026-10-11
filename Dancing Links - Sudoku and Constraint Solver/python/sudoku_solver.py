"""
sudoku_solver.py
-----------------
Solves a 9x9 Sudoku by turning it into an exact cover problem and giving
it to DancingLinks.

The 4 rules of Sudoku become 4 groups of 81 columns = 324 columns:
    Group 0 (cols   0..80 ) : every CELL has exactly one digit
    Group 1 (cols  81..161) : every ROW contains each digit exactly once
    Group 2 (cols 162..242) : every COLUMN contains each digit exactly once
    Group 3 (cols 243..323) : every 3x3 BOX contains each digit exactly once

Every possible move "put digit d in cell (r, c)" is one row of the matrix.
It covers exactly 4 columns (one from each group).
There are 9 * 9 * 9 = 729 possible moves.
"""

from dancing_links import DancingLinks

NUM_COLUMNS = 324
MAX_NODES = 729 * 4


class SudokuSolver:

    def __init__(self):
        self.last_search_steps = 0

    def solve(self, puzzle):
        """
        puzzle = 9x9 list of lists, 0 means empty cell.
        Returns the solved 9x9 grid, or None if there is no solution.
        """
        dlx = self._build_matrix(puzzle)
        found = dlx.solve(1)
        self.last_search_steps = dlx.get_search_steps()

        if found == 0:
            return None

        # Turn the chosen row ids back into a filled grid
        grid = [[0] * 9 for _ in range(9)]
        for row_id in dlx.get_first_solution():
            r = row_id // 81
            c = (row_id // 9) % 9
            digit = row_id % 9 + 1
            grid[r][c] = digit
        return grid

    def count_solutions(self, puzzle):
        """Counts solutions but stops at 2 (we only care about 0, 1 or "many")."""
        dlx = self._build_matrix(puzzle)
        return dlx.solve(2)

    # Turn the puzzle into the exact cover matrix
    def _build_matrix(self, puzzle):
        dlx = DancingLinks(NUM_COLUMNS, MAX_NODES)

        for r in range(9):
            for c in range(9):
                if puzzle[r][c] != 0:
                    # Cell already has a clue -> only ONE move is possible here
                    self._add_move(dlx, r, c, puzzle[r][c] - 1)
                else:
                    # Empty cell -> any of the 9 digits could go here
                    for digit in range(9):
                        self._add_move(dlx, r, c, digit)
        return dlx

    # Adds the row for "put digit in cell (r, c)"
    def _add_move(self, dlx, r, c, digit):
        box = (r // 3) * 3 + (c // 3)

        covers = [
            r * 9 + c,                  # cell constraint
            81 + r * 9 + digit,         # row constraint
            162 + c * 9 + digit,        # column constraint
            243 + box * 9 + digit,      # box constraint
        ]
        row_id = r * 81 + c * 9 + digit     # we can decode r, c, digit from this later
        dlx.add_row(row_id, covers)


# ------------------------------------------------------------------
# Small helper functions for reading and printing grids
# ------------------------------------------------------------------

def parse(text):
    """Reads a puzzle from an 81-character string. Use 0 or . for empty cells."""
    grid = [[0] * 9 for _ in range(9)]
    for i in range(81):
        ch = text[i]
        value = 0
        if ch >= '1' and ch <= '9':
            value = int(ch)
        grid[i // 9][i % 9] = value
    return grid


def print_grid(grid):
    """Prints the grid with box lines so it is easy to read."""
    for r in range(9):
        if r % 3 == 0 and r != 0:
            print("------+-------+------")
        line = ""
        for c in range(9):
            if c % 3 == 0 and c != 0:
                line += "| "
            if grid[r][c] == 0:
                line += ". "
            else:
                line += str(grid[r][c]) + " "
        print(line)
