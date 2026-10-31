# Data Structures and Algorithms

A structured collection of fundamental and advanced **Data Structures and Algorithms (DSA)** implementations, systems simulations, and competitive problem solutions across **C++**, **Java**, **Python**, and **C**.

Every implementation emphasizes foundational computer science principles: zero reliance on high-level collection libraries (`std::vector`, `java.util.*`, `collections.deque`) where data structures are taught, explicit pointer manipulation, manual dynamic memory management, and rigorous time/space complexity analysis.

---

## 📑 Repository Structure & Module Index

| Topic / Folder | Primary Languages | Description |
|---|---|---|
| [`Binary Tree/`](./Binary%20Tree) | C++, Java, Python | Complete binary tree template with custom queue level-order insertion, BFS/DFS traversals, node/leaf counters, and height calculation. |
| [`binary-tree-paths/`](./binary-tree-paths) | C++17, CMake | Optimized DFS backtracking solution for LeetCode #257 with memory-efficient string resizing and unit test assertions. |
| [`Circular Linked List Implementations/`](./Circular%20Linked%20List%20Implementations) | Java | Circular singly linked list ADT with cyclical pointer traversals, insertion, deletion, and search. |
| [`Dancing Links - Sudoku and Constraint Solver/`](./Dancing%20Links%20-%20Sudoku%20and%20Constraint%20Solver) | C++, Java, Python | Donald Knuth's Dancing Links (Algorithm X) for exact cover problems and high-speed 9x9 Sudoku solving. |
| [`Doubly Linked List Implementations/`](./Doubly%20Linked%20List%20Implementations) | Java | Custom doubly linked list ADT featuring bidirectional pointer management and in-place reversal. |
| [`dsa-problem-set/`](./dsa-problem-set) | C++, Java, Python | 5 classic algorithmic problems implemented across 3 languages (Add Two Numbers, Playlist Manager, Stack Mirroring, and Palindrome Validation). |
| [`Graphs/`](./Graphs) | C++ | Low-level Undirected Weighted Graph ADT, storage representations (Matrix, List, Edge List), and iterative BFS & DFS traversals. |
| [`Linked List Memory Manager/`](./Linked%20List%20Memory%20Manager) | Java | Operating system dynamic memory manager simulation (`malloc`, `write`, `delete`, `copy`) using custom linked list memory blocks. |
| [`PromptVault/`](./PromptVault) | Java | AI prompt history management system utilizing a custom doubly linked list with priority sorting. |
| [`Singly Linked List Implementations/`](./Singly%20Linked%20List%20Implementations) | Java | Foundational singly linked list ADT with insertion, deletion, iterative 3-pointer reversal, and search. |
| [`Sorting techniques/`](./Sorting%20techniques) | Java | Bubble Sort, Insertion Sort, and Selection Sort implemented on linked lists, contrasting value swapping with pointer relinking. |
| [`Stack Implementations/`](./Stack%20Implementations) | C, C++, Java, Python | Fixed-capacity array-based Stack ADT in C++ and a multi-language bracket matching delimiter validator. |

---

## 🛠 Prerequisites & Tooling

To run the implementations across this repository, ensure you have the following toolchains installed:

- **C / C++**: `gcc` / `g++` (supporting C++11 or C++17) & `cmake` (v3.14+)
- **Java**: Java Development Kit (JDK 8 or newer)
- **Python**: Python 3.6 or newer

---

## ▶️ General How-To-Run Guide

Each subfolder contains its own dedicated `README.md` with detailed instructions. Below are standard execution commands:

### C++ Executables
```bash
# General C++ source
g++ -std=c++17 <filename>.cpp -o output
./output

# CMake projects (e.g. binary-tree-paths)
cd binary-tree-paths
mkdir -p build && cd build
cmake .. && make
./run_tests
```

### Java Programs
```bash
javac <Filename>.java
java <MainClassName>
```

### Python Scripts
```bash
python3 <script_name>.py
```

### C Programs
```bash
gcc -std=c11 <filename>.c -o output
./output
```

---

## 💡 Engineering Highlights & Architecture

1. **Bare-Metal Fundamentals**: Core data structures (Stacks, Queues, Linked Lists, Graphs) avoid library containers to build a direct understanding of pointer logic, memory layouts, and edge-case handling.
2. **Proper Resource Cleanup**: C++ implementations include full destructors (`~Graph()`, `deleteTree()`) to systematically eliminate heap memory leaks.
3. **Cross-Language Parity**: Core algorithms (such as DLX, Binary Tree traversals, and the DSA Problem Set) are implemented equivalently in C++, Java, and Python.

---

## 👤 Author

**Jaikiran J**  
B.Tech Computer Science and Engineering  
Amrita Vishwa Vidyapeetham

---

## 📄 License

This repository is maintained for educational and reference purposes. Feel free to reference and learn from this codebase.
