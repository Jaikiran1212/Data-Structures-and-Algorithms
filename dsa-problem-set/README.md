# DSA Problem Set — Linked Lists, Stacks & Queues

Implementations of three data structures problems, each written in
Python, Java, and C++. Every source file lives in its own folder next
to a README explaining what it does, how to run it, and (where
relevant) what was fixed to get it working.

## Structure

```
.
├── python/
│   ├── add_two_numbers_linked_list/
│   │   ├── add_two_numbers_linked_list.py
│   │   └── README.md
│   ├── playlist_manager/
│   │   ├── playlist_manager.py
│   │   └── README.md
│   └── mirror_stack_using_queue/
│       ├── mirror_stack_using_queue.py
│       └── README.md
├── java/
│   ├── add_two_numbers_linked_list/
│   │   ├── AddTwoNumbersLinkedList.java
│   │   └── README.md
│   ├── playlist_manager/
│   │   ├── PlaylistManager.java
│   │   └── README.md
│   └── mirror_stack_using_queue/
│       ├── MirrorStackUsingQueue.java
│       └── README.md
├── cpp/
│   ├── add_two_numbers_linked_list/
│   │   ├── add_two_numbers_linked_list.cpp
│   │   └── README.md
│   ├── playlist_manager/
│   │   ├── playlist_manager.cpp
│   │   └── README.md
│   └── mirror_stack_using_queue/
│       ├── mirror_stack_using_queue.cpp
│       └── README.md
├── .gitignore
└── README.md
```

## Problems

1. **Add Two Numbers (Linked List)** — sums two numbers represented as
   singly linked lists (one digit per node), digit-wise with carry.
2. **Playlist Manager** — a doubly-linked-list playlist with play
   tracking, skip/go-back navigation, undo/redo, and favourite-song
   tracking.
3. **Mirror a Stack Using a Queue** — reverses a stack's contents using
   only an auxiliary queue as extra storage.

See each folder's own README for exact run instructions, input/output
format, and examples.

## Fixes made while completing this set

The original files were at different stages of completeness across
the three languages. Full details are in each affected folder's
README; in short:

- **C++ / Add Two Numbers**: fixed a null-pointer bug, a missing
  `return` statement, and a double-decrement of the test-case counter
  that silently skipped every other test case.
- **Java / Add Two Numbers**: fixed a missing decrement of the
  test-case counter that caused a crash on more than one test case.
- **Python / Mirror Stack**: the file was empty — implemented from
  scratch using the same helper-function structure as the Java
  version.
- **C++ / Mirror Stack**: the file didn't compile — rewritten with
  `std::stack`/`std::queue`, same helper-function structure.
- **Mirror Stack logic (all three)**: the original logic corrupted the
  stack (5 elements in, 10 out) instead of mirroring it. All three
  versions now use the minimal, correct form of the same approach.

Everything else — variable names, control flow, class layout, and the
overall approach for each problem — is unchanged from the original
files.
