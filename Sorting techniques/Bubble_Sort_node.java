public class Bubble_Sort_node{

    class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    Node head;

    // Insert at end
    public void insertLast(int data) {

        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            return;
        }

        Node temp = head;

        while (temp.next != null) {
            temp = temp.next;
        }

        temp.next = newNode;
    }

    // Bubble Sort by swapping nodes
    public void bubbleSort() {

        if (head == null || head.next == null) {
            return;
        }

        boolean swapped;

        do {

            swapped = false;

            Node prev = null;
            Node curr = head;

            while (curr != null && curr.next != null) {

                if (curr.data > curr.next.data) {

                    Node temp = curr.next;

                    // Swap links
                    curr.next = temp.next;
                    temp.next = curr;

                    if (prev == null) {
                        head = temp;
                    } else {
                        prev.next = temp;
                    }

                    prev = temp;
                    swapped = true;

                } else {

                    prev = curr;
                    curr = curr.next;
                }
            }

        } while (swapped);
    }

    // Display the list
    public void printList() {

        Node temp = head;

        while (temp != null) {
            System.out.print(temp.data + " -> ");
            temp = temp.next;
        }

        System.out.println("NULL");
    }

    public static void main(String[] args) {

        BubbleSortNodes list = new BubbleSortNodes();

        list.insertLast(30);
        list.insertLast(10);
        list.insertLast(40);
        list.insertLast(20);
        list.insertLast(5);

        System.out.println("Before Sorting:");
        list.printList();

        list.bubbleSort();

        System.out.println("\nAfter Sorting:");
        list.printList();
    }
}