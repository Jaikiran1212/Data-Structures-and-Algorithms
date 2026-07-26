public class MemoryManager {

    static class Node {

        int id;
        char data;
        Node next;

        Node(int id) {
            this.id = id;
            this.data = '\0';
            this.next = null;
        }
    }

    Node head = null;
    int count = 1;

    // 1. malloc(int n)
    public int malloc(int n) {

        if (n <= 0)
            return -1;

        Node firstNew = new Node(count++);
        Node curr = firstNew;

        for (int i = 2; i <= n; i++) {
            curr.next = new Node(count++);
            curr = curr.next;
        }

        if (head == null) {
            head = firstNew;
        } else {
            curr = head;

            while (curr.next != null) {
                curr = curr.next;
            }

            curr.next = firstNew;
        }

        return firstNew.id;
    }

    // 2. write(String s, int id)
    public void write(String s, int id) throws Exception {

        Node curr = head;

        while (curr != null && curr.id != id) {
            curr = curr.next;
        }

        if (curr == null) {
            throw new Exception("Invalid ID");
        }

        for (int i = 0; i < s.length(); i++) {

            if (curr == null) {
                throw new Exception("Out of Memory");
            }

            curr.data = s.charAt(i);
            curr = curr.next;
        }
    }

    // 3. write(String s, int id, int n)
    public void write(String s, int id, int n) throws Exception {

        if (n > s.length()) {
            n = s.length();
        }

        Node curr = head;

        while (curr != null && curr.id != id) {
            curr = curr.next;
        }

        if (curr == null) {
            throw new Exception("Invalid ID");
        }

        for (int i = 0; i < n; i++) {

            if (curr == null) {
                throw new Exception("Out of Memory");
            }

            curr.data = s.charAt(i);
            curr = curr.next;
        }
    }

    // 4. delete(int id, int n)
    public void delete(int id, int n) throws Exception {

        if (n <= 0) {
            throw new Exception("Invalid n");
        }

        Node prev = null;
        Node curr = head;

        while (curr != null && curr.id != id) {
            prev = curr;
            curr = curr.next;
        }

        if (curr == null) {
            throw new Exception("Invalid ID");
        }

        Node temp = curr;

        for (int i = 0; i < n; i++) {

            if (temp == null) {
                throw new Exception("Out of Bounds");
            }

            temp = temp.next;
        }

        if (prev == null) {
            head = temp;
        } else {
            prev.next = temp;
        }
    }

    // 5. copy(int id1, int id2, int n)
    public void copy(int id1  , int id2 , int n) throws Exception{
        
        Node curr = head;
        Node temp = head;

        if(n <= 0){
            throw new Exception("Invalid n");
        }
        if(curr == null || temp == null){
            throw new Exception("Invalid ID");
        }

        while(curr != null && curr.id != id1){
            curr = curr.next;
        }

        while(temp != null && temp.id != id2){
            temp = temp.next;
        }

        if (curr == null || temp == null){
            throw new Exception ("Invalid id");
        }
        for (int i = 0; i < n; i++){
            if(curr == null || temp == null){
                throw new Exception("Out of bounds");
            }
            temp.data = curr.data;
            curr = curr.next;
            temp = temp.next;
        }
    }
}