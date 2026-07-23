public class Insertion_Sort_node {

    class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    Node head;

    public void insertionSort() {

        if (head == null || head.next == null) {
            return;
        }

        Node sorted = null;
        Node current = head;

        while (current != null) {

            Node next = current.next;

            // Insert at beginning
            if (sorted == null || current.data < sorted.data) {

                current.next = sorted;
                sorted = current;

            } else {

                Node temp = sorted;

                while (temp.next != null && temp.next.data < current.data) {
                    temp = temp.next;
                }

                current.next = temp.next;
                temp.next = current;
            }

            current = next;
        }

        head = sorted;
    }
}