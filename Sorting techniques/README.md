# Sorting Techniques on Linked Lists

Java implementations of classic comparison-based sorting algorithms adapted specifically for **Singly Linked Lists**.

Unlike arrays where elements reside in contiguous memory, linked lists pose unique sorting challenges. This module explores two fundamentally different sorting paradigms:
1. **`_data` (Value Swapping)** — Keeps node topology intact and exchanges the `data` values held inside nodes.
2. **`_node` (Pointer Relinking)** — Preserves node data integrity and physically rearranges the `next` pointers to reorder nodes.

---

## 📁 Directory Structure

```text
Sorting techniques/
├── Bubble_Sort_data.java       # Bubble Sort via value swapping
├── Bubble_Sort_node.java       # Bubble Sort via pointer manipulation & demo main
├── Insertion_Sort_data.java    # Insertion Sort via value swapping (placeholder)
├── Insertion_Sort_node.java    # Insertion Sort via pointer manipulation
├── Selection_Sort_data.java    # Selection Sort via value swapping (placeholder)
├── Selection_Sort_node.java    # Selection Sort via pointer manipulation
└── README.md                   # Documentation & comparative analysis
```

---

## ⚖️ Value Swapping vs. Pointer Relinking

| Aspect | Data Swapping (`_data`) | Pointer Manipulation (`_node`) |
|---|---|---|
| **Concept** | Swaps node contents (`int temp = a.data; a.data = b.data; ...`) | Reconfigures `next` references (`prev.next`, `curr.next`, `head`) |
| **Memory Access** | Simple, resembles array sorting logic | Complex, requires tracking predecessor (`prev`) pointers |
| **Object Overhead** | Cheap for primitives (`int`), very expensive for heavy payload objects | $O(1)$ pointer assignment regardless of payload size |
| **Identity Preservation**| Changes object values; node identities/references are scrambled | Preserves exact object identity and memory address of each node |

---

## 📊 Algorithm Overview & Complexity

| Algorithm | File | Approach | Best Time | Average Time | Worst Time | Space | Stable? |
|---|---|---|---|---|---|---|---|
| **Bubble Sort** | `Bubble_Sort_data.java` | Adjacent value swap | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| **Bubble Sort** | `Bubble_Sort_node.java` | Adjacent pointer swap | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| **Insertion Sort** | `Insertion_Sort_node.java`| Sorted sublist insertion | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | Yes |
| **Selection Sort** | `Selection_Sort_node.java`| Min search & pointer swap | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ | No |

---

## 🔬 Pointer Manipulation Mechanisms

### 1. Bubble Sort by Node Relinking (`Bubble_Sort_node.java`)
When `curr.data > curr.next.data`, the nodes are swapped by adjusting three pointers:
```text
Before Swap:  prev -> curr -> temp -> nextNode
After Swap:   prev -> temp -> curr -> nextNode
```
Special handling is included when `prev == null` (swapping the head node).

### 2. Insertion Sort by Node Relinking (`Insertion_Sort_node.java`)
Iterates through the unsorted list, extracting one node at a time (`current`) and inserting it into its correct position within an initially empty `sorted` sublist:
- If `sorted == null || current.data < sorted.data`: prepend to `sorted`.
- Else: traverse `sorted` to find `temp` where `temp.next.data >= current.data`, then splice `current` in.

### 3. Selection Sort by Node Relinking (`Selection_Sort_node.java`)
Finds the minimum node in the remaining unsorted portion and splices it into the current position. Differentiates two structural cases:
- **Adjacent nodes (`current -> min`)**: Direct pointer inversion.
- **Non-adjacent nodes (`current -> ... -> minPrev -> min`)**: Full four-pointer relinking.

---

## ▶️ Compilation & Execution

Compile and run using JDK 8+:

```bash
# Example: Bubble Sort with demonstration
javac Bubble_Sort_node.java
java Bubble_Sort_node
```

**Sample Output (`Bubble_Sort_node`):**
```text
Before Sorting:
30 -> 10 -> 40 -> 20 -> 5 -> NULL

After Sorting:
5 -> 10 -> 20 -> 30 -> 40 -> NULL
```
