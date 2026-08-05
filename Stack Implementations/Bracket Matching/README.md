# Bracket Matching

This folder contains implementations of the **Bracket Matching** problem using the **Stack** data structure in multiple programming languages. These programs demonstrate how stacks are used to validate balanced parentheses, braces, and brackets, following a simple and beginner-friendly approach for learning Data Structures and Algorithms (DSA).


## Folder Structure

```text
Stack Implementations/
└── Bracket Matching/
    ├── Bracket_matching_c.c
    ├── Bracket_matching_c++.cpp
    ├── Bracket_matching_python.py
    └── Main.java
```

## Programs Included

### 1. Bracket Matching

Checks whether the brackets in an expression are balanced using a stack.

Supported brackets:

* `()`
* `{}`
* `[]`

Available in:

* C
* C++
* Java
* Python

## Algorithms

### Bracket Matching Algorithm

1. Create an empty stack.
2. Traverse the input string one character at a time.
3. Push every opening bracket onto the stack.
4. For every closing bracket:

   * If the stack is empty, the expression is not balanced.
   * Otherwise, pop the top element.
   * Verify that the popped opening bracket matches the closing bracket.
5. After traversing the string:

   * If the stack is empty, the expression is balanced.
   * Otherwise, it is not balanced.

## Time Complexity

### Stack Operations

| Operation | Time Complexity |
| --------- | --------------- |
| Push      | O(1)            |
| Pop       | O(1)            |
| Peek      | O(1)            |
| isEmpty   | O(1)            |
| Size      | O(1)            |

### Bracket Matching

| Operation | Complexity |
| --------- | ---------- |
| Time      | O(n)       |
| Space     | O(n)       |

## Sample Input

```text
{[()]}
```

## Sample Output

```text
The brackets are balanced.
```

## Purpose

This repository is intended for:

* Data Structures and Algorithms (DSA) practice
* College laboratory exercises
* Coding interview preparation
* Learning stack operations and their applications
