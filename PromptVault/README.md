# PromptVault

PromptVault is a Java application that manages AI prompt history using a **custom Doubly Linked List** implementation. The application allows users to store, organize, and manage prompts without using arrays or Java's built-in collection framework.

## Features

- Add a new prompt
- Delete a prompt using Prompt ID
- Display all prompts in insertion order
- Display prompts in reverse order
- Sort prompts based on priority (High → Medium → Low)

## Data Structure Used

- Custom Doubly Linked List
- No arrays
- No Java Collections Framework
- Each node stores:
  - Prompt ID
  - Prompt Name
  - Category
  - Priority
  - Previous Node Reference
  - Next Node Reference

## Project Structure

```
PromptVault/
│
├── Prompt.java
├── PromptVault.java
├── Main.java
├── TestCase1.txt
├── TestCase2.txt
├── TestCase3.txt
└── README.md
```

## Operations

| Operation | Description | Time Complexity |
|-----------|-------------|----------------|
| Add Prompt | Inserts a new prompt at the end | O(1) |
| Delete Prompt | Deletes a prompt using Prompt ID | O(n) |
| Print Prompts | Displays prompts in insertion order | O(n) |
| Reverse Print | Displays prompts from tail to head | O(n) |
| Sort by Priority | Rearranges prompts as High → Medium → Low | O(n) |

## Input Format

The first line contains an integer **N**, representing the number of operations.

The supported operations are:

### Add Prompt

```
A <PromptID> <PromptName> <Category> <Priority>
```

Example:

```
A P101 Explain_Linked_List Coding High
```

### Delete Prompt

```
D <PromptID>
```

Example:

```
D P101
```

### Print Prompt History

```
P
```

### Reverse Print

```
REV
```

### Sort by Priority

```
S
```

## Sample Operations

```
A P101 Explain_Linked_List Coding High
A P102 Generate_Viva ExamPrep Medium
A P103 Improve_Resume Career Low
P
S
REV
D P102
```

## Technologies Used

- Java
- Object-Oriented Programming
- Custom Doubly Linked List

## Learning Objectives

This project demonstrates:

- Implementation of a custom Doubly Linked List
- Object-Oriented Design
- Pointer manipulation
- Data Structure operations
- Time complexity analysis
- Java ADT implementation

## Author

Jaikiran J