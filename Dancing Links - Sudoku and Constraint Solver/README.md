# Dancing Links: Sudoku & Constraint Solver

Java, C++ and Python implementations of Donald Knuth's **Dancing Links (DLX)** technique for solving
**exact cover** problems, with a **Sudoku solver** built on top of it.
Built as a DSA case study. All versions use only plain arrays/lists (no collections, STL containers or node objects).

## The problem: Exact Cover

You are given a set of **columns** (constraints) and a set of **rows** (choices), where each
row covers some of the columns. Pick rows so that **every column is covered exactly once**.

Many puzzles (Sudoku, N-Queens, pentomino tiling, scheduling) can be written this way.

## Algorithm X and Dancing Links

- **Algorithm X** is a backtracking search: pick a column, try each row that covers it,
  remove everything that conflicts, recurse, then undo.
- **Dancing Links** is the data structure that makes undoing cheap. Every `1` in the matrix is a
  node in circular doubly linked lists (left/right/up/down). Removing a node is
  `right[left[x]] = right[x]; left[right[x]] = left[x];` and because `x` still remembers its
  neighbours, putting it back is just as easy.
- **Heuristic:** always choose the column with the fewest remaining rows. This prunes the
  search tree massively.

## How Sudoku becomes exact cover

Each possible move "digit `d` in cell `(r, c)`" is a row. There are 9 x 9 x 9 = 729 rows.
Each move covers 4 columns, giving 4 x 81 = 324 columns:

| Columns   | Rule                                     |
|-----------|------------------------------------------|
| 0 - 80    | each cell holds exactly one digit        |
| 81 - 161  | each row has each digit exactly once     |
| 162 - 242 | each column has each digit exactly once  |
| 243 - 323 | each 3x3 box has each digit exactly once |

Clue cells only get one row (their given digit); empty cells get nine.

## Project structure

```
Dancing Links - Sudoku and Constraint Solver/
├── java/
│   └── src/
│       ├── DancingLinks.java   # generic exact cover solver (DLX)
│       ├── SudokuSolver.java   # Sudoku -> exact cover -> Sudoku
│       └── Main.java           # demo and test cases
├── cpp/
│   ├── DancingLinks.h / .cpp   # generic exact cover solver (DLX)
│   ├── SudokuSolver.h / .cpp   # Sudoku -> exact cover -> Sudoku
│   └── main.cpp                # demo and test cases
├── python/
│   ├── dancing_links.py        # generic exact cover solver (DLX)
│   ├── sudoku_solver.py        # Sudoku -> exact cover -> Sudoku
│   └── main.py                 # demo and test cases
├── README.md
└── .gitignore
```

All three versions use the same algorithm and the same test cases, and print the same results.

## How to run

### Java (JDK 8 or newer)

```bash
cd java
javac -d out src/*.java
java -cp out Main
```

### C++ (g++ with C++11 or newer)

```bash
cd cpp
g++ -std=c++11 -O2 *.cpp -o dlx
./dlx
```

### Python (3.6 or newer)

```bash
cd python
python3 main.py
```

Solve your own puzzle (81 characters, `0` or `.` for empty cells):

```bash
java -cp out Main 530070000600195000098000060800060003400803001700020006060000280000419005000080079
./dlx 530070000600195000098000060800060003400803001700020006060000280000419005000080079
python3 main.py 530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

## Test cases included

1. Knuth's classic 7-column exact cover example (answer: rows B, D, F)
2. An impossible exact cover (an uncoverable column)
3. Easy Sudoku
4. Very hard Sudoku (Arto Inkala's puzzle), solved in about 1500 row attempts
5. Invalid Sudoku (duplicate clue), correctly reports no solution
6. Empty grid, reports that many solutions exist

Every solved grid is checked by an independent validator that does not use DLX.

## Complexity

Exact cover is NP-complete, so the worst case is exponential. In practice, the
fewest-rows-first heuristic keeps standard 9x9 Sudoku solving in milliseconds.
Building the matrix is O(729 x 4) and each cover/uncover is proportional to the
number of nodes it touches.

## Possible extensions

- N-Queens (needs "secondary" columns that may be covered at most once)
- Pentomino tiling
- 16x16 Sudoku
- Puzzle generator that uses `countSolutions` to guarantee a unique answer

## Reference

Donald E. Knuth, *Dancing Links*, 2000 (arXiv:cs/0011047).
