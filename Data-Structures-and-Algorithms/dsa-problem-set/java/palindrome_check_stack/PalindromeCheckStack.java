import java.util.Stack;

public class PalindromeCheckStack {

    // Checks whether a string is a palindrome by pushing every
    // character onto a stack, then popping them back off (reverse
    // order) while comparing against the original string
    // left-to-right.
    public static boolean isPalindrome(String theString) {
        if (theString == null) {
            return false;
        }

        Stack<Character> stack = new Stack<>();

        for (int i = 0; i < theString.length(); i++) {
            stack.push(theString.charAt(i));
        }

        for (int i = 0; i < theString.length(); i++) {
            if (stack.pop() != theString.charAt(i)) {
                return false;
            }
        }
        return true;
    }

    public static void main(String[] args) {
        System.out.println(isPalindrome("malayalam"));
        System.out.println(isPalindrome("hello"));
    }
}
