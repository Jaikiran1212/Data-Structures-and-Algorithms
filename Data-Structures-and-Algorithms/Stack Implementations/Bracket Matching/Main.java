import java.util.Stack;
import java.util.Scanner;

public class Main {
    public static boolean isBalanced(String str){
        Stack<Character> stack = new Stack<>();
        for(int i = 0; i < str.length();i++){
            char ch = str.charAt(i);
            if(ch == '(' || ch == '[' || ch == '{'){
                stack.push(ch);
            }else if ( ch == ')' || ch == ']' || ch =='}'){
                if(stack.isEmpty()){
                    return false;
                }
                char top = stack.pop();
                if((ch == ')' && top!= '(') || (ch == '}' && top != '{') || (ch == ']' && top!= '[')){
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String str = sc.next();

        if(isBalanced(str)){
            System.out.println("Balanced");
        }else{
            System.out.println("Not Balanced");
        }
        sc.close();
    }
}