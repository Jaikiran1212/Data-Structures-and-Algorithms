# Circular Linked List Implementation (Java)

A custom implementation of a **Circular Singly Linked List (CLL)** in Java. Built from first principles without using Java's built-in collections framework to demonstrate pointer cycling, loop termination patterns, and edge case management.

---

## 📁 Directory Structure

```text
Circular Linked List Implementations/
├── CLList.java       # Core Circular Linked List ADT implementation
└── README.md         # Documentation & usage guide
```

---

## ⚙️ Concept & Node Structure

In a Circular Linked List, the `next` pointer of the final node points back to `head` instead of `null`, forming an endless loop. Traversal relies on `do-while` loops with the termination condition `curr != head`.

```text
     +-----------------------------------------+
     |                                         |
     v                                         |
  +------+     +------+     +------+     +-----+
  | data |     | data |     | data |     | data|
  | next |---> | next |---> | next |---> | next|
  +------+     +------+     +------+     +-----+
   (Head)                                 (Last)
```

### Node Structure
```java
static class Node {
    int data;
    Node next;

    Node(int d) {
        data = d;
        next = null;
    }
}
```

---

## 🧰 Operations & Complexity Analysis

| Operation | Method Signature | Description | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Initialize List** | `create_cll(int n)` | Generates a circular list with values $1 \dots n$ | $O(n)$ | $O(1)$ auxiliary |
| **Insert First** | `insertFirst(int data)` | Inserts new node at head and updates the last node's link | $O(n)$ | $O(1)$ |
| **Insert Last** | `insertLast(int data)` | Appends new node at tail with `next` pointing to `head` | $O(n)$ | $O(1)$ |
| **Delete First** | `deleteFirst()` | Unlinks head and points the last node to the new head | $O(n)$ | $O(1)$ |
| **Delete Last** | `deleteLast()` | Traverses to second-to-last node and points its `next` to `head` | $O(n)$ | $O(1)$ |
| **Delete Item** | `deleteItem(int item)` | Removes the first node matching `item` | $O(n)$ | $O(1)$ |
| **Find Node** | `findNode(int data)` | Circular search for value; returns 0-based index or `-1` | $O(n)$ | $O(1)$ |
| **Print List** | `printList()` | Traverses the entire circle once and displays elements | $O(n)$ | $O(1)$ |
| **Size** | `size()` | Computes total node count in the circular chain | $O(n)$ | $O(1)$ |
| **Check Empty** | `isEmpty()` | Returns `true` if `head == null` | $O(1)$ | $O(1)$ |

---

## ▶️ Compilation & Execution

Compile using `javac` (requires JDK 8+):

```bash
javac CLList.java
```

### Usage Example:

```java
public class Demo {
    public static void main(String[] args) {
        CLList cll = new CLList();

        cll.insertLast(10);
        cll.insertLast(20);
        cll.insertFirst(5);

        System.out.println("List elements:");
        cll.printList(); // 5, 10, 20

        System.out.println("Size: " + cll.size()); // 3
        System.out.println("Index of 20: " + cll.findNode(20)); // 2

        cll.deleteItem(10);
        cll.printList(); // 5, 20
    }
}
```

---

## 💡 Key Highlights

- **Infinite Loop Avoidance**: Uses `do { ... } while (curr != head);` semantics to ensure every node is processed exactly once without infinite loops.
- **Single Node Cycle Handling**: Special edge case handling in `deleteFirst()` and `deleteLast()` when `head.next == head`, correctly setting `head = null`.
