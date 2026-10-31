# Bracket Matching

A multi-language implementation of the classic **Balanced Bracket Matching Problem** using the **Stack** data structure in **C**, **C++**, **Java**, and **Python**.

---

## 📁 Folder Structure

```text
Bracket Matching/
├── Bracket_matching_c.c        # C implementation (function)
├── Bracket_matching_c++.cpp    # C++ implementation with CLI demo
├── Bracket_matching_python.py  # Python 3 script with CLI demo
├── Main.java                   # Java console application
└── README.md                   # Documentation & run instructions
```

---

## 🔍 Problem Overview

Given a string containing bracket characters, determine if the bracket delimiters are properly nested and balanced.

### Supported Bracket Pairs:
- Parentheses: `()`
- Curly Braces: `{}`
- Square Brackets: `[]`

### Balance Conditions:
1. Every opening bracket must be closed by the same type of bracket.
2. Opening brackets must be closed in the correct order (LIFO - Last-In First-Out).
3. Every closing bracket must correspond to an earlier unclosed opening bracket.

---

## 🧠 Algorithm

```text
Input String:  { [ ( ) ] }
Stack Trace:
1. Read '{' -> Push '{'   | Stack: ['{']
2. Read '[' -> Push '['   | Stack: ['{', '[']
3. Read '(' -> Push '('   | Stack: ['{', '[', '(']
4. Read ')' -> Pop '(', matches ')' | Stack: ['{', '[']
5. Read ']' -> Pop '[', matches ']' | Stack: ['{']
6. Read '}' -> Pop '{', matches '}' | Stack: []
Result: Stack is empty -> BALANCED
```

1. Initialize an empty stack.
2. Traverse through each character in the string:
   - If the character is an opening delimiter (`(`, `{`, `[`), push it onto the stack.
   - If the character is a closing delimiter (`)`, `}`, `]`):
     - If the stack is empty, return `false` (premature closing bracket).
     - Pop the top character from the stack.
     - If the popped character is not the corresponding matching opening bracket, return `false` (mismatched pair).
3. After the entire string has been scanned, return `true` if the stack is completely empty, otherwise `false` (unclosed opening brackets remain).

---

## ⏱ Complexity Analysis

| Metric | Complexity | Explanation |
|---|---|---|
| **Time Complexity** | $O(n)$ | Each character is visited once and pushed/popped at most once |
| **Auxiliary Space** | $O(n)$ | In the worst case (e.g. `((((((`), the stack stores all $n$ characters |

---

## ▶️ Compilation & Execution

### C++
```bash
g++ -std=c++11 Bracket_matching_c++.cpp -o bracket_cpp
./bracket_cpp
```

### Python
```bash
python3 Bracket_matching_python.py
```

### Java
```bash
javac Main.java
java Main
```

### C
```bash
# Compile with a test driver or include as a helper in your C project
gcc -c Bracket_matching_c.c
```

---

## 🧪 Test Cases & Sample I/O

| Input | Expected Output | Status |
|---|---|---|
| `{[()]}` | `The brackets are balanced.` / `Balanced` | Valid nested brackets |
| `{[(])}` | `The brackets are not balanced.` / `Not Balanced` | Mismatched pair (`]` before `)`) |
| `{{[[` | `The brackets are not balanced.` / `Not Balanced` | Unclosed opening brackets |
| `]` | `The brackets are not balanced.` / `Not Balanced` | Stack underflow / premature closing |
| `()` | `The brackets are balanced.` / `Balanced` | Simple pair |
