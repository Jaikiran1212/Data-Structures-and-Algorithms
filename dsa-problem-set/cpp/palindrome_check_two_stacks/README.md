# Palindrome Check (Two Stacks) — C++

## What it does
Checks whether a string is a palindrome using two stacks: every
character is pushed onto `stack1`, then the second half is moved
onto `stack2` (which reverses that half). If the length is odd, the
middle character is discarded. `stack1` (first half, now on top in
reverse) and `stack2` (second half, reversed back to forward order)
are then compared element by element — if they match all the way
through, the string is a palindrome.

## How to run
```
g++ -std=c++17 -o palindrome_check_two_stacks palindrome_check_two_stacks.cpp
./palindrome_check_two_stacks
```

Output:
```
racecar -> true
malayalam -> true
```

## Status — bug fixed
The original file did not compile: it called `stack1.pop()` and
expected it to return a value (`char c1 = stack1.pop();`), but in
C++, `std::stack::pop()` returns `void` — you have to read the value
with `.top()` first and then call `.pop()` separately. Fixed in both
places this pattern occurred (the half-copy loop already did this
correctly with `.top()`/`.pop()`; the final comparison loop did not).
No other logic was changed.
