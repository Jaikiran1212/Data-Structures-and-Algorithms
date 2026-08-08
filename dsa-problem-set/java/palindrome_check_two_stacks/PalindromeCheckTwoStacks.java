import java.util.Stack;

public class PalindromeCheckTwoStacks {

    // Checks whether a string is a palindrome using two stacks: push
    // everything onto stack1, then move the second half onto stack2
    // so stack2 ends up holding the mirror image of the first half,
    // and compare the two stacks element by element.
    public static boolean isPalindrome(String text) {

        // --- STEP 1: Push all characters into stack1 ---
        Stack<Character> stack1 = new Stack<>();
        for (int i = 0; i < text.length(); i++) {
            stack1.push(text.charAt(i));
        }

        // --- STEP 2: Move HALF the characters from stack1 to stack2 ---
        Stack<Character> stack2 = new Stack<>();
        int length = text.length();
        int half = length / 2;

        for (int i = 0; i < half; i++) {
            stack2.push(stack1.pop());
        }

        // --- STEP 3: If odd length, discard the middle character ---
        if (length % 2 != 0) {
            stack1.pop();
        }

        // --- STEP 4: Compare stack1 and stack2 element by element ---
        while (!stack1.isEmpty()) {
            char c1 = stack1.pop();
            char c2 = stack2.pop();

            if (c1 != c2) {
                return false; // Found a mismatch!
            }
        }
        return true; // All characters matched!
    }

    public static void main(String[] args) {
        String test1 = "racecar";
        String test2 = "malayalam";

        System.out.println(test1 + " -> " + isPalindrome(test1));
        System.out.println(test2 + " -> " + isPalindrome(test2));
    }
}
