# Mirror a Stack Using a Queue — Python

## What it does
Reverses ("mirrors") the contents of a stack using only an auxiliary
queue as extra storage: drain the stack into the queue, then drain the
queue back into the stack. That single round trip reverses the order
exactly once.

## How to run
```
python3 mirror_stack_using_queue.py
```

The `main()` function runs a small built-in demo (no stdin input
needed):
```
Before mirror: [1, 2, 3, 4, 5]
After mirror: [5, 4, 3, 2, 1]
```

## Status — completed / fixed
This file was **empty** in the original assignment. It has been
written from scratch, using the same `stack2queue` / `queue2stack`
helper-function structure that the Java version of this problem
already used.

While completing it, a bug was found in the reference logic (the
Java version): after the initial stack→queue→stack round trip (which
already mirrors the stack correctly), it performed several more
redundant round trips and a re-insertion loop that ended up
**duplicating elements** — a 5-element stack came out with 10
elements instead of a clean mirror. This version uses the minimal,
correct form instead: one round trip through the queue and nothing
more.
