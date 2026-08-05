# Stack Implementations

This folder contains implementations of the **Stack** data structure and its applications in multiple programming languages. The programs are written in a simple and beginner-friendly style for learning Data Structures and Algorithms (DSA).

## Folder Structure

```text
Stack Implementations/
│
├── CPP.cpp
│
└── Bracket Matching/
    ├── Bracket_matching_c.c
    ├── Bracket_matching_c++.cpp
    ├── Bracket_matching_python.py
    └── Main.java
```

## Programs Included

### 1. Stack Implementation (C++)

* Array-based stack implementation.
* Operations:

  * Push
  * Pop
  * Peek
  * isEmpty
  * Size

### 2. Bracket Matching

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

### Stack Operations

* **Push**

  * Inserts an element at the top of the stack.
* **Pop**

  * Removes the top element from the stack.
* **Peek**

  * Returns the top element without removing it.
* **isEmpty**

  * Checks whether the stack is empty.
* **Size**

  * Returns the number of elements currently in the stack.

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
