# Mirror a Stack Using a Queue — Java

## What it does
Reverses ("mirrors") the contents of a `Stack<Integer>` using only an
auxiliary `Queue<Integer>` as extra storage: drain the stack into the
queue, then drain the queue back into the stack. That single round
trip reverses the order exactly once.

## How to run
```
javac MirrorStackUsingQueue.java
java MirrorStackUsingQueue
```

The `main()` method runs a small built-in demo (no stdin input
needed):
```
Before mirror: [1, 2, 3, 4, 5]
After mirror: [5, 4, 3, 2, 1]
```

## Status — bug fixed
The original `mirror()` method compiled and ran, but its logic was
wrong: after the initial stack→queue→stack round trip (which already
mirrors the stack correctly), it performed several more redundant
round trips and a re-insertion loop that ended up **duplicating
elements** — a 5-element stack came out with 10 elements instead of a
clean mirror (verified by running the original logic). This version
keeps the same `stack2queue()` / `queue2stack()` helper structure but
uses the minimal, correct form: one round trip through the queue and
nothing more.
