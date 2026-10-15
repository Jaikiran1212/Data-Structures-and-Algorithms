# Add Two Numbers (Linked List) — Python

## What it does
Reads `T` test cases from stdin. Each test case gives two numbers, each
represented as a singly linked list with one digit per node, and prints
their digit-wise sum (with carry) as a linked list, in `a -> b -> c`
format.

## How to run
```
python3 add_two_numbers_linked_list.py
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

## Status
Complete and tested — no changes needed to this file's logic.
