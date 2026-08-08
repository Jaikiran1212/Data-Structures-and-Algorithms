#include <iostream>
#include <string>
#include <stack>

using namespace std;

class PalindromeCheckTwoStacks {
public:
    // Checks whether a string is a palindrome using two stacks: push
    // everything onto stack1, then move the second half onto stack2
    // so stack2 ends up holding the mirror image of the first half,
    // and compare the two stacks element by element.
    static bool isPalindrome(string text) {

        // --- STEP 1: Push all characters into stack1 ---
        stack<char> stack1;
        for (int i = 0; i < (int)text.length(); i++) {
            stack1.push(text[i]);
        }

        // --- STEP 2: Move HALF the characters from stack1 to stack2 ---
        stack<char> stack2;
        int length = text.length();
        int half = length / 2;

        for (int i = 0; i < half; i++) {
            stack2.push(stack1.top()); // Get top element
            stack1.pop();              // Remove top element
        }

        // --- STEP 3: If odd length, discard the middle character ---
        if (length % 2 != 0) {
            stack1.pop();
        }

        // --- STEP 4: Compare stack1 and stack2 element by element ---
        while (!stack1.empty()) {
            char c1 = stack1.top();
            stack1.pop();
            char c2 = stack2.top();
            stack2.pop();
            if (c1 != c2) {
                return false; // Found a mismatch!
            }
        }
        return true; // All characters matched!
    }
};

int main() {
    string test1 = "racecar";
    string test2 = "malayalam";

    // boolalpha formats boolean output as "true"/"false" instead of 1/0
    cout << boolalpha;
    cout << test1 << " -> " << PalindromeCheckTwoStacks::isPalindrome(test1) << endl;
    cout << test2 << " -> " << PalindromeCheckTwoStacks::isPalindrome(test2) << endl;

    return 0;
}
