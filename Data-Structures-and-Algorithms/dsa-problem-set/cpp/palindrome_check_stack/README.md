# Palindrome Check (Single Stack) — C++

## What it does
Checks whether a string is a palindrome by pushing every character
onto a `std::stack<char>`, then popping them back off (which comes
out in reverse order) while comparing against the original string
read left-to-right. If every character matches its mirrored
counterpart, the string is a palindrome.

## How to run
```
g++ -std=c++17 -o palindrome_check_stack palindrome_check_stack.cpp
./palindrome_check_stack
```

Output:
```
true
false
```
(`"malayalam"` is a palindrome, `"hello"` is not.)

## Status — completed
This file was empty in the original assignment. Implemented from
scratch, following the same push-everything-then-pop-and-compare
approach as the Java/Python versions of this problem, using
`std::stack<char>`.
