# Dancing Links (DLX) & Sudoku Solver — Python

A clean, idiomatic Python 3 implementation of Donald Knuth's **Dancing Links (Algorithm X)** technique for solving **exact cover** problems, featuring a complete 9x9 **Sudoku solver**.

Implemented using flat primitive lists for linked-list pointer tables (`left`, `right`, `up`, `down`) to ensure maximum speed in Python without custom object instantiation overhead.

---

## 📁 Directory Structure

```text
python/
├── dancing_links.py    # Core DLX exact cover engine (Algorithm X)
├── sudoku_solver.py    # 9x9 Sudoku constraint formulation & independent validator
├── main.py             # Test suite execution & CLI puzzle runner
└── README.md           # Documentation & execution guide
```

---

## ⚙️ Architecture & Design

- **Index-Based Circular Doubly Linked Matrix**: In place of heavy Python class instances, links are tracked using flat `list[int]` lookups.
- **Backtracking Unwinding**: Uses Knuth's bidirectional link dancing:
  ```python
  # Cover column c
  right[left[c]] = right[c]
  left[right[c]] = left[c]
  ```
- **Sudoku Constraint Reduction**:
  - 4 constraints per placed digit: Cell constraint, Row constraint, Column constraint, and 3x3 Box constraint.
  - Generates a 729 x 324 binary exact cover matrix.

---

## ▶️ Execution & Usage

Requires **Python 3.6+** (no third-party dependencies required):

```bash
python3 main.py
```

### Solve a Custom Puzzle
Pass an 81-character puzzle string (`0` or `.` denotes blank cells):

```bash
python3 main.py 530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

---

## 🧪 Included Test Suite

1. **Knuth 7-Column Exact Cover**: Asserts unique solution matching rows `B D F`.
2. **Impossible Exact Cover**: Confirms 0 solutions for matrix with unreachable column.
3. **Easy Sudoku**: Solved in ~1.8 ms (81 row attempts).
4. **Arto Inkala's "Hardest Sudoku"**: Solved in ~18 ms (~1500 row attempts).
5. **Invalid Sudoku**: Gracefully identifies invalid clue conflicts (no solution).
6. **Empty 9x9 Grid**: Validates non-uniqueness and yields valid arrangement.

---

## ⏱ Performance

| Problem | Row Attempts | Typical Runtime |
|---|---|---|
| Knuth 7-Column Exact Cover | 3 | < 0.1 ms |
| Easy Sudoku | 81 | ~1.8 ms |
| Arto Inkala (World's Hardest) | ~1492 | ~17.8 ms |
