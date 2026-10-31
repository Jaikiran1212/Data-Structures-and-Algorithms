# Stack Implementations

A collection of **Stack Data Structure** implementations and practical algorithmic applications across multiple programming languages (**C**, **C++**, **Java**, and **Python**).

---

## 📁 Directory Structure

```text
Stack Implementations/
├── CPP.cpp                     # Array-based Stack ADT in C++
├── README.md                   # Stack overview & usage guide
└── Bracket Matching/           # Application: balanced bracket validation
    ├── Bracket_matching_c.c        # C implementation
    ├── Bracket_matching_c++.cpp    # C++ implementation
    ├── Bracket_matching_python.py  # Python implementation
    ├── Main.java                   # Java implementation
    └── README.md                   # Dedicated application guide
```

---

## 🧱 Implementations Included

### 1. Array-Based Stack ADT (`CPP.cpp`)
A fixed-capacity LIFO (Last-In, First-Out) stack implemented from scratch using a static array:
- Capacity: 100 elements
- Zero external container dependencies (no `std::stack`, no `std::vector`)
- Overflow and Underflow detection

#### Core Operations:
| Operation | Method | Description | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Push** | `push(int x)` | Adds element `x` to the top of the stack | $O(1)$ | $O(1)$ |
| **Pop** | `pop()` | Removes and returns the top element | $O(1)$ | $O(1)$ |
| **Peek / Top** | `peek()` | Inspects top element without removal | $O(1)$ | $O(1)$ |
| **Empty Check** | `isEmpty()` | Returns `true` if `top == -1` | $O(1)$ | $O(1)$ |
| **Size** | `size()` | Returns current number of elements (`top + 1`) | $O(1)$ | $O(1)$ |

### 2. Bracket Matching (`Bracket Matching/`)
A classic stack application validating syntax delimiters: parentheses `()`, curly braces `{}`, and square brackets `[]`. Available in **C**, **C++**, **Java**, and **Python**. See [`Bracket Matching/README.md`](./Bracket%20Matching/README.md) for detailed documentation.

---

## ▶️ How to Run

### Array-Based Stack (`CPP.cpp`)
```bash
g++ -std=c++11 CPP.cpp -o stack_demo
./stack_demo
```

**Sample Output:**
```text
Pushed 100 to stack.
Pushed 200 to stack.
Pushed 300 to stack.

Popped Element: 300
Top Element: 200
Size of Stack: 2
Stack is Not Empty
```

### Bracket Matching
Navigate to `Bracket Matching/` and refer to [`Bracket Matching/README.md`](./Bracket%20Matching/README.md) for compilation and execution across C, C++, Java, and Python.

---

## 💡 Key Takeaways

- **LIFO Behavior**: Stacks provide $O(1)$ constant time access and removal only at the top element.
- **Error Handling**: Explicit boundary validation prevents memory violations (`Stack Overflow` at capacity and `Stack Underflow` on empty stack pop).
