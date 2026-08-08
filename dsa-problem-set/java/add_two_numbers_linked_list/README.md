# Add Two Numbers (Linked List) — Java

## What it does
Reads `T` test cases from stdin. Each test case gives two numbers, each
represented as a singly linked list with one digit per node, and prints
their digit-wise sum (with carry) as a linked list, in `a -> b -> c`
format.

## How to run
```
javac AddTwoNumbersLinkedList.java
java AddTwoNumbersLinkedList
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
2
2 2
5 5
5 5
1 1
9
9
```
Output:
```
0 -> 1 -> 1
8 -> 1
```

## Status — bug fixed
The original main loop never decremented `T` after a successful test
case (only on the early-return error paths). With more than one test
case, it would try to read past the end of input and crash with a
`NoSuchElementException`. A `T--;` was added at the end of the loop
body (matching how the Python version already handled this) so
multiple test cases work correctly. No other logic was changed.
