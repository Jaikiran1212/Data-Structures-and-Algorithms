# Memory Manager Using Singly Linked List (Java)

## Overview

This project implements a simple **dynamic memory manager** using a **Singly Linked List** in Java. It simulates basic memory management operations similar to those provided by the C programming language, such as `malloc()`, `write()`, `delete()`, and `copy()`.

This project was developed as part of a **Data Structures and Algorithms (DSA)** laboratory exercise.

---

## Features

- Allocate memory blocks dynamically.
- Write data into allocated memory.
- Overloaded write method to write only a specified number of bytes.
- Delete (free) consecutive memory blocks.
- Copy data from one memory location to another.
- Display memory contents for verification.

---

## Data Structure Used

- **Singly Linked List**

Each node represents one memory block.

```java
class Node {
    int id;
    char data;
    Node next;
}
```

---

## Methods Implemented

### 1. `malloc(int n)`

Allocates `n` consecutive memory blocks.

**Returns:**
- Starting memory block ID.
- Returns `-1` for invalid allocation size.

---

### 2. `write(String s, int id)`

Writes the entire string into memory beginning from the specified block ID.

**Exceptions**
- Invalid ID
- Out of Memory

---

### 3. `write(String s, int id, int n)`

Overloaded version of `write()`.

Writes only the first `n` characters of the string into memory.

**Exceptions**
- Invalid ID
- Out of Memory

---

### 4. `delete(int id, int n)`

Deletes (frees) `n` consecutive memory blocks starting from the specified ID by unlinking them from the linked list.

**Exceptions**
- Invalid ID
- Invalid n
- Out of Bounds

---

### 5. `copy(int id1, int id2, int n)`

Copies data from `n` memory blocks starting at `id1` into `n` memory blocks starting at `id2`.

**Exceptions**
- Invalid ID
- Invalid n
- Out of Bounds

---

## Example

```java
MemoryManager manager = new MemoryManager();

int id1 = manager.malloc(5);
int id2 = manager.malloc(5);

manager.write("HELLO", id1);
manager.write("WORLD", id2);

manager.copy(id1, id2, 5);
```

Before Copy

```
ID : 1  H
ID : 2  E
ID : 3  L
ID : 4  L
ID : 5  O

ID : 6  W
ID : 7  O
ID : 8  R
ID : 9  L
ID : 10 D
```

After Copy

```
ID : 1  H
ID : 2  E
ID : 3  L
ID : 4  L
ID : 5  O

ID : 6  H
ID : 7  E
ID : 8  L
ID : 9  L
ID : 10 O
```

---

## Time Complexity

| Operation | Complexity |
|-----------|------------|
| malloc() | O(n) |
| write() | O(n) |
| write(s, id, n) | O(n) |
| delete() | O(n) |
| copy() | O(n) |

---

## Technologies Used

- Java
- Singly Linked List
- Object-Oriented Programming (OOP)

---

## Learning Outcomes

- Implementation of dynamic memory allocation using linked lists.
- Pointer manipulation in Java.
- Linked list traversal.
- Node insertion and deletion.
- Method overloading.
- Exception handling.
- Simulation of basic memory management operations.

---

## Author

**Jaikiran J**

B.Tech Computer Science and Engineering  
Amrita Vishwa Vidyapeetham