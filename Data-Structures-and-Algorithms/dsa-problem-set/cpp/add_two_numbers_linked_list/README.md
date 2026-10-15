# Add Two Numbers (Linked List) — C++

## What it does
Reads `T` test cases from stdin. Each test case gives two numbers, each
represented as a singly linked list with one digit per node, and prints
their digit-wise sum (with carry) as a linked list, in `a -> b -> c`
format.

## How to run
```
g++ -std=c++17 -o add_two_numbers_linked_list add_two_numbers_linked_list.cpp
./add_two_numbers_linked_list
```

## Input format
```
T
N M
<N digits of list 1, space-separated>
<M digits of list 2, space-separated>
... (repeated T times)
```

- `T`: number of test cases (1–10)
- `N`, `M`: length of list 1 and list 2 (1–100000 each)
- each digit must be between 0 and 9

## Example
Input:
```
1
2 2
5 5
5 5
```
Output:
```
0 -> 1 -> 1
```

## Status — bugs fixed
The original file did not compile and would have crashed even if it
had. Fixed, without changing the overall approach:

- `temp1`/`current1` and `temp2`/`current2` were left as `nullptr`
  instead of dummy head nodes, so `current1 -> next = ...` dereferenced
  a null pointer. Now initialized with `new Node(0)`, matching the
  Java/Python versions.
- `addTwoNUmber()` never returned a value despite its `Node*` return
  type. Added `return temp->next;`.
- The test-case loop decremented `T` twice per iteration
  (`while(T-- > 0)` *and* `T--` inside the loop body), which silently
  skipped every other test case. Changed the loop condition to
  `while(T > 0)`, keeping the single `T--` at the end.
