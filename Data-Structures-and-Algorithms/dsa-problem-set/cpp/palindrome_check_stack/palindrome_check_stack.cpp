#include <iostream>
#include <string>
#include <stack>

using namespace std;

// Checks whether a string is a palindrome by pushing every character
// onto a stack, then popping them back off (reverse order) while
// comparing against the original string left-to-right.
bool isPalindrome(const string& theString) {
    stack<char> s;

    // Step 1: Push all characters onto the stack
    for (int i = 0; i < (int)theString.length(); i++) {
        s.push(theString[i]);
    }

    // Step 2: Pop characters (last-in-first-out, i.e. reverse order)
    // and compare with the string left-to-right
    for (int i = 0; i < (int)theString.length(); i++) {
        char top = s.top();
        s.pop();
        if (top != theString[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    cout << boolalpha;
    cout << isPalindrome("malayalam") << endl;
    cout << isPalindrome("hello") << endl;
    return 0;
}
