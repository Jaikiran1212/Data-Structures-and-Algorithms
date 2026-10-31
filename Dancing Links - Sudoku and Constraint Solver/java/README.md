# Dancing Links (DLX) & Sudoku Solver — Java

A high-speed Java implementation of Donald Knuth's **Dancing Links (Algorithm X)** technique for solving **exact cover** problems, featuring a complete 9x9 **Sudoku solver**.

Built as a low-level DSA case study using primitive 1D `int[]` arrays for pointer tables rather than Java `Object` instances, maximizing garbage collection efficiency and cache performance.

---

## 📁 Directory Structure

```text
java/
├── DancingLinks.java   # Generic exact cover solver (DLX engine)
├── SudokuSolver.java   # Sudoku-to-exact-cover translator & validator
├── Main.java           # Demo runner, unit tests & CLI parser
└── README.md           # Documentation & compilation instructions
```

---

## ⚙️ Architecture & Design

- **Primitive Array Pointers**: Eliminates millions of node object allocations by tracking nodes as indices within contiguous integer arrays (`left[]`, `right[]`, `up[]`, `down[]`, `col[]`, `row[]`).
- **MRV (Minimum Remaining Values)**: Heuristic selection of the column with the minimum candidate rows drastically minimizes branch exploration.
- **Constant Time Splicing**:
  ```java
  // Cover column c
  right[left[c]] = right[c];
  left[right[c]] = left[c];
  ```

---

## ▶️ Compilation & Execution

Requires **JDK 8 or newer**:

```bash
# Compile
javac *.java

# Run test suite
java Main
```

### Solve a Custom Puzzle
Pass an 81-character puzzle string (`0` or `.` denotes blank cells):

```bash
java Main 530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

---

## 🧪 Included Test Suite

1. **Knuth 7-Column Exact Cover**: Asserts unique solution matching rows `B D F`.
2. **Impossible Exact Cover**: Confirms 0 solutions for matrix with unreachable column.
3. **Easy Sudoku**: Solved in ~0.5 ms (81 row attempts).
4. **Arto Inkala's "Hardest Sudoku"**: Solved in ~5 ms (~1500 row attempts).
5. **Invalid Sudoku**: Gracefully identifies invalid clue conflicts (no solution).
6. **Empty 9x9 Grid**: Validates non-uniqueness and yields valid arrangement.
