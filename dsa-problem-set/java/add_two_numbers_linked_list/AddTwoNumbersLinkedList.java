import java.util.Scanner;

// A single node of a singly linked list. Each node stores one digit.
class Node {
    int data;
    Node next;

    Node(int data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedListAdd {
    // Adds two numbers that are represented as linked lists (one digit
    // per node) and returns the head of the resulting linked list.
    public static Node addTwoNumber(Node l1, Node l2) {
        Node temp = new Node(0); // dummy head node, makes list building easier
        Node current = temp;
        int carry = 0;

        // Keep going while either list still has nodes, or there is a
        // leftover carry to push into a new node.
        while (l1 != null || l2 != null || carry != 0) {
            int x;
            if (l1 != null) {
                x = l1.data;
            } else {
                x = 0;
            }
            int y;
            if (l2 != null) {
                y = l2.data;
            } else {
                y = 0;
            }
            int sum = (x + y + carry);
            carry = sum / 10;

            current.next = new Node(sum % 10);
            current = current.next;

            if (l1 != null) {
                l1 = l1.next;
            }
            if (l2 != null) {
                l2 = l2.next;
            }
        }
        return temp.next; // skip the dummy head
    }

}

public class AddTwoNumbersLinkedList {

    // Prints a linked list in "a -> b -> c" format.
    public static void printlist(Node head) {
        Node current = head;
        while (current != null) {
            System.out.print(current.data);

            if (current.next != null) {
                System.out.print(" -> ");
            }
            current = current.next;
        }
        System.out.println();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        if (!sc.hasNextInt()) {
            return;
        }

        int T = sc.nextInt();
        // Constraint check for T
        if (T < 1 || T > 10) {
            System.err.println("T must be between 1 and 10.");
            sc.close();
            return;
        }

        while (T > 0) {
            int N = sc.nextInt();
            // Constraint check for N
            if (N < 1 || N > 100000) {
                System.err.println("N must be between 1 and 10^5.");
                sc.close();
                T--;
                return;
            }
            int M = sc.nextInt();
            // Constraint check for M
            if (M < 1 || M > 100000) {
                System.err.println("M must be between 1 and 10^5.");
                sc.close();
                T--;
                return;
            }

            // Build the first linked list from N input digits.
            Node temp1 = new Node(0);
            Node current1 = temp1;
            for (int i = 0; i < N; i++) {
                int data = sc.nextInt();
                // Constraint check for List1
                if (data < 0 || data > 9) {
                    System.err.println("List1 elements must be between 0 and 9.");
                    sc.close();
                    T--;
                    return;
                }
                current1.next = new Node(data);
                current1 = current1.next;
            }

            // Build the second linked list from M input digits.
            Node temp2 = new Node(0);
            Node current2 = temp2;
            for (int i = 0; i < M; i++) {
                int data = sc.nextInt();
                // Constraint check for List2
                if (data < 0 || data > 9) {
                    System.err.println("List2 elements must be between 0 and 9.");
                    sc.close();
                    T--;
                    return;
                }
                current2.next = new Node(data);
                current2 = current2.next;
            }

            // Add the two lists and print the result.
            Node result = LinkedListAdd.addTwoNumber(temp1.next, temp2.next);
            printlist(result);
            T--;
        }
        sc.close();

    }
}
