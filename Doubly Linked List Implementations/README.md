# Doubly Linked List Implementation (Java)

A complete, custom implementation of a **Doubly Linked List (DLL)** in Java. Built from first principles without Java's built-in `LinkedList` or `java.util` collections to demonstrate low-level bidirectional pointer manipulation.

---

## 📁 Directory Structure

```text
Doubly Linked List Implementations/
├── DLList.java       # Core Doubly Linked List ADT implementation
└── README.md         # Documentation & usage guide
```

---

## ⚙️ Node Structure

Each node maintains a data payload and dual pointers to both its predecessor (`prev`) and successor (`next`):

```java
static class Node {
    int data;
    Node next;
    Node prev;

    Node(int d) {
        data = d;
        next = null;
        prev = null;
    }
}
```

```text
       +------+      +------+      +------+
NULL <-| prev |<-..->| prev |<-..->| prev |
       | data |      | data |      | data |
       | next |->..->| next |->..->| next |-> NULL
       +------+      +------+      +------+
        (Head)                      (Tail)
```

---

## 🧰 Operations & Complexity Analysis

| Operation | Method Signature | Description | Time Complexity | Space Complexity |
|---|---|---|---|---|
| **Initialize List** | `create_dll(int n)` | Generates a sequential list with values $1 \dots n$ | $O(n)$ | $O(1)$ auxiliary |
| **Insert First** | `insertFirst(int data)` | Prepends element at head | $O(1)$ | $O(1)$ |
| **Insert Last** | `insertLast(int data)` | Appends element at tail | $O(n)$ | $O(1)$ |
| **Delete First** | `deleteFirst()` | Removes the current head node | $O(1)$ | $O(1)$ |
| **Delete Last** | `deleteLast()` | Traverses to and removes the tail node | $O(n)$ | $O(1)$ |
| **Delete Item** | `deleteItem(int item)` | Finds and removes the first node containing `item` | $O(n)$ | $O(1)$ |
| **Find Node** | `findNode(int data)` | Linear search for value; returns 0-based index or `-1` | $O(n)$ | $O(1)$ |
| **Reverse List** | `reverseList()` | In-place reversal by swapping `next` and `prev` pointers | $O(n)$ | $O(1)$ |
| **Print List** | `printList()` | Traverses and prints all nodes in forward order | $O(n)$ | $O(1)$ |
| **Size** | `size()` | Counts total number of nodes in list | $O(n)$ | $O(1)$ |
| **Check Empty** | `isEmpty()` | Returns `true` if `head == null` | $O(1)$ | $O(1)$ |

---

## ▶️ Compilation & Execution

Compile and run via command line (requires JDK 8+):

```bash
javac DLList.java
```

### Usage Example:

```java
public class Demo {
    public static void main(String[] args) {
        DLList list = new DLList();
        
        // Insert elements
        list.insertLast(10);
        list.insertLast(20);
        list.insertFirst(5);
        
        System.out.println("Size: " + list.size()); // 3
        list.printList(); // 5, 10, 20
        
        // Reverse
        list.reverseList();
        list.printList(); // 20, 10, 5
        
        // Delete
        list.deleteItem(10);
        list.printList(); // 20, 5
    }
}
```

---

## 💡 Key Highlights

- **Bidirectional Relinking**: Operations such as `deleteItem` carefully update both `prev.next` and `next.prev` while handling edge cases (single node, head deletion, tail deletion).
- **In-place Reversal**: `reverseList()` swaps the `prev` and `next` references of every node in a single pass without allocating any new nodes.
