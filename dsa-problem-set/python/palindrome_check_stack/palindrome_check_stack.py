# Checks whether a string is a palindrome by pushing every character
# onto a stack, then popping them back off (reverse order) while
# comparing against the original string read left-to-right.
def isPalindrome(theString: str) -> bool:
    if theString is None:
        return False
    stack = []

    # Step 1: Push all characters onto the stack
    for char in theString:
        stack.append(char)

    # Step 2: Pop characters (last-in-first-out, i.e. reverse order)
    # and compare with the string left-to-right
    for char in theString:
        if stack.pop() != char:
            return False

    return True


print(isPalindrome("malayalam"))
print(isPalindrome("hello"))
