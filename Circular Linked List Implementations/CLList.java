public class CLList {

    Node head;

    static class Node {

        int data;
        Node next;

        Node(int d) {
            data = d;
            next = null;
        }
    }

    public static Node create_cll(int n) {

        if (n <= 0)
            return null;

        Node head = new Node(1);
        Node curr = head;

        for (int i = 2; i <= n; i++) {
            Node newNode = new Node(i);
            curr.next = newNode;
            curr = newNode;
        }

        curr.next = head;

        return head;
    }

    public void insertFirst(int data) {

        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            head.next = head;
            return;
        }

        Node last = head;

        while (last.next != head)
            last = last.next;

        newNode.next = head;
        last.next = newNode;
        head = newNode;
    }

    public void insertLast(int data) {

        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            head.next = head;
            return;
        }

        Node curr = head;

        while (curr.next != head)
            curr = curr.next;

        curr.next = newNode;
        newNode.next = head;
    }

    public void deleteFirst() {

        if (head == null)
            return;

        if (head.next == head) {
            head = null;
            return;
        }

        Node last = head;

        while (last.next != head)
            last = last.next;

        head = head.next;
        last.next = head;
    }

    public void deleteLast() {

        if (head == null)
            return;

        if (head.next == head) {
            head = null;
            return;
        }

        Node curr = head;

        while (curr.next.next != head)
            curr = curr.next;

        curr.next = head;
    }

    public void printList() {

        if (head == null)
            return;

        Node curr = head;

        do {
            System.out.println(curr.data);
            curr = curr.next;
        } while (curr != head);
    }

    public boolean isEmpty() {
        return head == null;
    }

    public int size() {

        if (head == null)
            return 0;

        int count = 0;
        Node curr = head;

        do {
            count++;
            curr = curr.next;
        } while (curr != head);

        return count;
    }

    public int findNode(int data) {

        if (head == null)
            return -1;

        Node curr = head;
        int index = 0;

        do {

            if (curr.data == data)
                return index;

            curr = curr.next;
            index++;

        } while (curr != head);

        return -1;
    }

    public void deleteItem(int item) {

        if (head == null)
            return;

        if (head.data == item) {
            deleteFirst();
            return;
        }

        Node prev = head;
        Node curr = head.next;

        while (curr != head) {

            if (curr.data == item) {
                prev.next = curr.next;
                return;
            }

            prev = curr;
            curr = curr.next;
        }
    }
}