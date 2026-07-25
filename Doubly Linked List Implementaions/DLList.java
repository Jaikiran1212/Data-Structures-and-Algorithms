public class DLList {

    Node head;

    static class Node {

        int data;
        Node next;
        Node prev;

        Node(int data) {
            this.data = data;
            next = null;
            prev = null;
        }
    }

    public static Node create_dll(int n){
        if( n <= 0){
            return null;
        }

        Node head = new Node(1);
        Node curr = head;

        for(int i =2; i <=n; i++){
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

        Node current = head;

        while (current.next != null) {
            current = current.next;
        }

        current.next = newNode;
        newNode.prev = current;
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

        Node current = head;

        while (current.next != null) {
            current = current.next;
        }

        current.prev.next = null;
    }

    public void displayForward() {

        Node current = head;

        while (current != null) {
            System.out.print(current.data + " <-> ");
            current = current.next;
        }

        System.out.println("null");
    }

    public void displayBackward() {

        if (head == null)
            return;

        Node current = head;

        while (current.next != null) {
            current = current.next;
        }

        while (current != null) {
            System.out.print(current.data + " <-> ");
            current = current.prev;
        }

        System.out.println("null");
    }

    public boolean isEmpty() {
        return head == null;
    }

    public int size() {

        int count = 0;
        Node current = head;

        while (current != null) {
            count++;
            current = current.next;
        }

        return count;
    }

    public int findNode(int data) {

        Node current = head;
        int index = 0;

        while (current != null) {

            if (current.data == data)
                return index;

            current = current.next;
            index++;
        }

        return -1;
    }

}