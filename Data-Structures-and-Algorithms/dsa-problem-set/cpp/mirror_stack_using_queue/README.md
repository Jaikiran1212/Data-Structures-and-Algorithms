# Mirror a Stack Using a Queue — C++

## What it does
Reverses ("mirrors") the contents of a `std::stack<int>` using only an
auxiliary `std::queue<int>` as extra storage: drain the stack into the
queue, then drain the queue back into the stack. That single round
trip reverses the order exactly once.

## How to run
```
g++ -std=c++17 -o mirror_stack_using_queue mirror_stack_using_queue.cpp
./mirror_stack_using_queue
```

The `main()` function runs a small built-in demo (no stdin input
needed):
```
Before mirror: [5, 4, 3, 2, 1]
After mirror: [1, 2, 3, 4, 5]
```
(Printed top-to-bottom, so this is the same underlying result as the
Python/Java versions, which print bottom-to-top.)

## Status — completed
This file did not compile in the original assignment: it used a
`Queue<int>` type that doesn't exist in the STL, was missing the
`<stack>`/`<queue>` includes, and called `.pop()` as if it returned a
value (in C++, `pop()` on `std::stack`/`std::queue` returns `void`;
you read the value with `.top()`/`.front()` first). Rewritten with
`std::stack<int>` and `std::queue<int>`, keeping the same
`stack2queue()` / `queue2stack()` helper-function structure as the
other two languages.

The original (Java) version of the `mirror()` logic also had a real
bug — several redundant round trips after the correct one, which
duplicated elements instead of cleanly mirroring the stack. This
version uses the minimal, correct form: one round trip through the
queue and nothing more.
