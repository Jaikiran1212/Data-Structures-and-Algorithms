# Palindrome Check (Two Stacks) — Java

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
javac PalindromeCheckTwoStacks.java
java PalindromeCheckTwoStacks
```

Output:
```
racecar -> true
malayalam -> true
```

## Status
Complete and tested — no changes needed to this file's logic.
