# Checks whether a string is a palindrome using two stacks: push
# everything onto stack1, then move the second half onto stack2 so
# stack2 ends up holding the mirror image of the first half, and
# compare the two stacks element by element.
def is_palindrome(text: str) -> bool:
    # --- Step 1: push all characters into stack1 ---
    stack1 = []
    for char in text:
        stack1.append(char)
    # --- Step 2: move half the characters from stack1 to stack2 ---
    stack2 = []
    length = len(text)
    half = length // 2
    for _ in range(half):
        stack2.append(stack1.pop())
    # --- Step 3: if odd length, discard the middle character ---
    if length % 2 != 0:
        stack1.pop()
    # --- Step 4: compare stack1 and stack2 element by element ---
    while stack1:
        c1 = stack1.pop()
        c2 = stack2.pop()
        if c1 != c2:
            return False  # found a mismatch!
    return True  # all characters matched!


test1 = "racecar"
test2 = "malayalam"
test3 = "hello"

print(f"{test1} -> {is_palindrome(test1)}")
print(f"{test2} -> {is_palindrome(test2)}")
print(f"{test3} -> {is_palindrome(test3)}")
