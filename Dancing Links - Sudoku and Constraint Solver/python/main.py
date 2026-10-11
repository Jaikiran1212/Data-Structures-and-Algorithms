"""
main.py
--------
Runs several test cases for the Dancing Links solver.

    Part 1: the classic exact cover example from Knuth's paper
    Part 2: Sudoku puzzles (easy, very hard, no solution, many solutions)

Run:  python3 main.py
Your own puzzle:  python3 main.py <81 characters>
"""

import sys
import time

from dancing_links import DancingLinks
from sudoku_solver import SudokuSolver, parse, print_grid


# Knuth's example: 7 columns (0..6) and 6 rows (A..F).
#   A covers 0,3,6   B covers 0,3   C covers 3,4,6
#   D covers 2,4,5   E covers 1,2,5,6   F covers 1,6
# The only exact cover is B, D, F.
def test_knuth_example():
    dlx = DancingLinks(7, 30)
    names = ["A", "B", "C", "D", "E", "F"]

    dlx.add_row(0, [0, 3, 6])
    dlx.add_row(1, [0, 3])
    dlx.add_row(2, [3, 4, 6])
    dlx.add_row(3, [2, 4, 5])
    dlx.add_row(4, [1, 2, 5, 6])
    dlx.add_row(5, [1, 6])

    found = dlx.solve(10)
    print("Knuth example -> solutions found:", found, "(expected 1)")

    answer = dlx.get_first_solution()
    chosen = ""
    for row_id in answer:
        chosen += names[row_id] + " "
    print("Chosen rows:", chosen + "(expected B, D, F in some order)")


# Column 2 is not covered by any row, so no solution can exist.
def test_no_solution_example():
    dlx = DancingLinks(3, 10)
    dlx.add_row(0, [0, 1])
    dlx.add_row(1, [0])

    found = dlx.solve(1)
    print("Impossible example -> solutions found:", found, "(expected 0)")


# Independent check (does not use DLX): every row, column and box must have 1..9 once
def is_valid_solution(grid):
    for i in range(9):
        seen_in_row = [False] * 10
        seen_in_column = [False] * 10
        seen_in_box = [False] * 10

        for j in range(9):
            row_value = grid[i][j]
            column_value = grid[j][i]
            box_value = grid[(i // 3) * 3 + j // 3][(i % 3) * 3 + j % 3]

            if row_value < 1 or seen_in_row[row_value]:
                return False
            if column_value < 1 or seen_in_column[column_value]:
                return False
            if box_value < 1 or seen_in_box[box_value]:
                return False

            seen_in_row[row_value] = True
            seen_in_column[column_value] = True
            seen_in_box[box_value] = True
    return True


# The solution must keep every original clue
def matches_clues(puzzle, solved):
    for r in range(9):
        for c in range(9):
            if puzzle[r][c] != 0 and puzzle[r][c] != solved[r][c]:
                return False
    return True


def run_sudoku_test(title, puzzle_text):
    print()
    print(title)

    puzzle = parse(puzzle_text)
    solver = SudokuSolver()

    print("Puzzle:")
    print_grid(puzzle)

    start_time = time.perf_counter()
    solved = solver.solve(puzzle)
    end_time = time.perf_counter()
    milliseconds = (end_time - start_time) * 1000

    if solved is None:
        print("Result: no solution exists.")
        print("Time:", round(milliseconds, 3), "ms")
        return

    print("Solution:")
    print_grid(solved)

    valid = is_valid_solution(solved) and matches_clues(puzzle, solved)
    count = solver.count_solutions(puzzle)

    print("Valid Sudoku?", valid)
    if count == 1:
        print("Unique solution? yes")
    else:
        print("Unique solution? no (more than one exists)")
    print("Row attempts made by DLX:", solver.last_search_steps)
    print("Time:", round(milliseconds, 3), "ms")


def main():
    print("=== PART 1: Generic exact cover ===")
    test_knuth_example()
    test_no_solution_example()

    print()
    print("=== PART 2: Sudoku ===")
    run_sudoku_test("Test 1: Easy puzzle",
        "530070000600195000098000060800060003400803001700020006060000280000419005000080079")

    run_sudoku_test("Test 2: Very hard puzzle (Arto Inkala)",
        "800000000003600000070090200050007000000045700000100030001000068008500010090000400")

    run_sudoku_test("Test 3: Puzzle with NO solution (two 5s in the first row)",
        "550070000600195000098000060800060003400803001700020006060000280000419005000080079")

    run_sudoku_test("Test 4: Empty grid (many solutions, we just show one)",
        "000000000000000000000000000000000000000000000000000000000000000000000000000000000")

    # Solve your own puzzle: python3 main.py <81 characters>
    if len(sys.argv) == 2 and len(sys.argv[1]) == 81:
        run_sudoku_test("Your puzzle", sys.argv[1])


if __name__ == "__main__":
    main()
