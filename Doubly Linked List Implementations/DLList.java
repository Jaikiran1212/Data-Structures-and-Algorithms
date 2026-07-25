public class DLList {

    Node head;

    static class Node {

        int data;
        Node next;
        Node prev;

        Node(int d) {
            data = d;
            next = null;
            prev = null;
        }
    }

    public static Node create_dll(int n) {

        if (n <= 0)
            return null;

        Node head = new Node(1);
        Node curr = head;

        for (int i = 2; i <= n; i++) {
            Node newNode = new Node(i);
            curr.next = newNode;
            newNode.prev = curr;
            curr = newNode;
        }

        return head;
    }

    public void insertFirst(int data) {

        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            return;
        }

        newNode.next = head;
        head.prev = newNode;
        head = newNode;
    }

    public void insertLast(int data) {

        Node newNode = new Node(data);

        if (head == null) {
            head = newNode;
            return;
        }

        Node curr = head;

        while (curr.next != null)
            curr = curr.next;

        curr.next = newNode;
        newNode.prev = curr;
    }

    public void deleteFirst() {

        if (head == null)
            return;

        if (head.next == null) {
            head = null;
            return;
        }

        head = head.next;
        head.prev = null;
    }

    public void deleteLast() {

        if (head == null)
            return;

        if (head.next == null) {
            head = null;
            return;
        }

        Node curr = head;

        while (curr.next != null)
            curr = curr.next;

        curr.prev.next = null;
    }

    public void printList() {

        Node curr = head;

        while (curr != null) {
            System.out.println(curr.data);
            curr = curr.next;
        }
    }

    public boolean isEmpty() {
        return head == null;
    }

    public int size() {

        int count = 0;
        Node curr = head;

        while (curr != null) {
            count++;
            curr = curr.next;
        }

        return count;
    }

    public int findNode(int data) {

        Node curr = head;
        int index = 0;

        while (curr != null) {

            if (curr.data == data)
                return index;

            curr = curr.next;
            index++;
        }

        return -1;
    }

    public void reverseList() {

        Node curr = head;
        Node temp = null;

        while (curr != null) {

            temp = curr.prev;
            curr.prev = curr.next;
            curr.next = temp;
            curr = curr.prev;
        }

        if (temp != null)
            head = temp.prev;
    }

    public void deleteItem(int item) {

        if (head == null)
            return;

        if (head.data == item) {
            deleteFirst();
            return;
        }

        Node curr = head.next;

        while (curr != null) {

            if (curr.data == item) {

                if (curr.next != null)
                    curr.next.prev = curr.prev;

                curr.prev.next = curr.next;
                return;
            }

            curr = curr.next;
        }
    }
}