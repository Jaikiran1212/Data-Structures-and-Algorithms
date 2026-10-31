# Singly Linked List Implementation (Java)

A complete, custom implementation of a **Singly Linked List (SLL)** in Java. Built from first principles without using Java's built-in `LinkedList` or `java.util` collection classes to demonstrate fundamental pointer manipulation and dynamic node linking.

---

## 📁 Directory Structure

```text
Singly Linked List Implementations/
├── SLList.java       # Core Singly Linked List ADT implementation
└── README.md         # Documentation & operations guide
```

---

## ⚙️ Node Structure

Each node stores an integer payload and a reference pointing to the subsequent node in the sequence (`null` at the tail):

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

```text
+------+     +------+     +------+
| data |     | data |     | data |
| next |---> | next |---> | next |---> NULL
+------+     +------+     +------+
 (Head)                    (Tail)
```

---

## 🧰 Operations & Complexity Analysis

| Operation | Method Signature | Description | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Initialize List** | `create_sll(int n)` | Generates a sequential list with values $1 \dots n$ | $O(n)$ | $O(1)$ auxiliary |
| **Insert First** | `insertFirst(int data)` | Prepends element at head | $O(1)$ | $O(1)$ |
| **Insert Last** | `insertLast(int data)` | Appends element at tail | $O(n)$ | $O(1)$ |
| **Delete First** | `deleteFirst()` | Unlinks and drops the head node | $O(1)$ | $O(1)$ |
| **Delete Last** | `deleteLast()` | Traverses to second-to-last node and sets its `next` to `null` | $O(n)$ | $O(1)$ |
| **Delete Item** | `deleteItem(int item)` | Removes the first occurrence of `item` from the list | $O(n)$ | $O(1)$ |
| **Reverse List** | `reverseList()` | In-place iterative reversal using 3-pointer technique | $O(n)$ | $O(1)$ |
| **Find Node** | `FindNode(int data)` | Linear search for `data`; returns 0-based index or `-1` | $O(n)$ | $O(1)$ |
| **Print List** | `printlist()` | Traverses and prints all node values sequentially | $O(n)$ | $O(1)$ |
| **Size** | `size()` | Counts total number of nodes in the list | $O(n)$ | $O(1)$ |
| **Check Empty** | `isEmpty()` | Returns `true` if `head == null` | $O(1)$ | $O(1)$ |

---

## ▶️ Compilation & Execution

Compile using `javac` (requires JDK 8+):

```bash
javac SLList.java
```

### Usage Example:

```java
public class Demo {
    public static void main(String[] args) {
        SLList list = new SLList();

        list.insertLast(10);
        list.insertLast(20);
        list.insertFirst(5);

        System.out.println("List contents:");
        list.printlist(); // 5, 10, 20

        System.out.println("Size: " + list.size()); // 3
        System.out.println("Index of 20: " + list.FindNode(20)); // 2

        // Reverse the list in-place
        list.reverseList();
        System.out.println("After reversal:");
        list.printlist(); // 20, 10, 5

        // Delete an element
        list.deleteItem(10);
        System.out.println("After deleting 10:");
        list.printlist(); // 20, 5
    }
}
```

---

## 💡 Key Highlights

- **Iterative 3-Pointer Reversal**: `reverseList()` reverses the direction of all `next` pointers using `prev`, `curr`, and `nextNode` pointers without allocating extra memory ($O(1)$ auxiliary space).
- **Graceful Boundary Handling**: All removal and traversal operations handle empty lists, single-element lists, and non-existent search targets without throwing unhandled `NullPointerException`s.