# Dancing Links (DLX) & Sudoku Solver — C++

A high-performance C++ implementation of Donald Knuth's **Dancing Links (Algorithm X)** technique for solving **exact cover** problems, featuring a complete 9x9 **Sudoku solver**.

Implemented from first principles using raw fixed-size arrays without high-level STL containers or dynamic node allocations in the search loop.

---

## 📁 Directory Structure

```text
cpp/
├── DancingLinks.h      # DLX interface & constraint matrix definitions
├── DancingLinks.cpp    # DLX algorithm & backtracking search implementation
├── SudokuSolver.h      # Sudoku modeling & validator declarations
├── SudokuSolver.cpp    # Sudoku constraint reduction & translation logic
├── main.cpp            # Test suite & CLI entry point
└── README.md           # Documentation & build instructions
```

---

## ⚙️ Architecture & Design

- **Static Array Memory Layout**: The 4-way circular doubly linked list (left, right, up, down) is represented entirely through 1D arrays indexed by integer IDs. This maximizes CPU cache locality and eliminates heap allocation overhead during search recursion.
- **Minimum Remaining Values (MRV) Heuristic**: Always selects the column with the minimum candidate count (`size`), drastically pruning search branches.
- **Fast Backtracking Unwinding**: Node removal and restoration executes in $O(1)$ pointer assignments:
  ```cpp
  // Cover column
  right[left[c]] = right[c];
  left[right[c]] = left[c];
  ```

---

## ▶️ Compilation & Execution

Compile with optimization enabled (`-O2` or `-O3`) using C++11 or later:

```bash
g++ -std=c++11 -O2 *.cpp -o dlx
./dlx
```

### Solve a Custom Puzzle
Pass an 81-character string (`0` or `.` denotes empty cells) directly via CLI:

```bash
./dlx 530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

---

## 🧪 Included Test Suite

1. **Knuth 7-Column Exact Cover**: Asserts unique solution matching rows `B D F`.
2. **Impossible Exact Cover**: Confirms 0 solutions for matrix with unreachable column.
3. **Easy Sudoku**: Solved in ~0.1 ms (81 row attempts).
4. **Arto Inkala's "Hardest Sudoku"**: Solved in ~1.0 ms (~1500 row attempts).
5. **Invalid Sudoku**: Gracefully identifies invalid clue conflicts (no solution).
6. **Empty 9x9 Grid**: Validates non-uniqueness and yields valid arrangement.

---

## ⏱ Performance

| Problem | Row Attempts | Typical Runtime |
|---|---|---|
| Knuth 7-Column Exact Cover | 3 | < 0.01 ms |
| Easy Sudoku | 81 | ~0.10 ms |
| Arto Inkala (World's Hardest) | ~1492 | ~0.98 ms |
