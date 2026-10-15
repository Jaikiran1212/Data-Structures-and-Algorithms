import java.util.Stack;
import java.util.Queue;
import java.util.LinkedList;

public class MirrorStackUsingQueue {

    // Empties the stack into the queue, one element at a time.
    public static void stack2queue(Stack<Integer> s, Queue<Integer> q) {
        while (!s.isEmpty()) {
            q.add(s.pop());
        }
    }

    // Empties the queue into the stack, one element at a time.
    public static void queue2stack(Queue<Integer> q, Stack<Integer> s) {
        while (!q.isEmpty()) {
            s.push(q.remove());
        }
    }

    // Reverses ("mirrors") the contents of a stack using only an
    // auxiliary queue as extra storage.
    public static void mirror(Stack<Integer> s) {
        if (s == null) {
            throw new IllegalArgumentException("Stack can't be null");
        }
        if (s.isEmpty()) {
            return;
        }

        Queue<Integer> q = new LinkedList<>();

        // Draining the stack into a queue (LIFO -> FIFO) and then
        // draining that queue back into the stack (FIFO -> LIFO)
        // reverses the order of the elements exactly once, which
        // mirrors the stack.
        stack2queue(s, q);
        queue2stack(q, s);
    }

    public static void main(String[] args) {
        Stack<Integer> s = new Stack<>();
        int[] elements = { 1, 2, 3, 4, 5 };
        for (int num : elements) {
            s.push(num);
        }

        System.out.println("Before mirror: " + s);
        mirror(s);
        System.out.println("After mirror: " + s);
    }

}
