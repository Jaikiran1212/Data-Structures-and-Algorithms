# Palindrome Check (Single Stack) — Java

## What it does
Checks whether a string is a palindrome by pushing every character
onto a `Stack<Character>`, then popping them back off (which comes
out in reverse order) while comparing against the original string
read left-to-right. If every character matches its mirrored
counterpart, the string is a palindrome.

## How to run
```
javac PalindromeCheckStack.java
java PalindromeCheckStack
```

Output:
```
true
false
```
(`"malayalam"` is a palindrome, `"hello"` is not.)

## Status — completed
The original file only had the `isPalindrome()` method with no `main`
method to actually run it. A `main()` was added that calls it on the
same two example strings used in the Python version, so the file can
be run and produces visible output. No changes were made to
`isPalindrome()` itself.
