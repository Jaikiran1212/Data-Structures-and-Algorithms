public class SLList{ 
  
    Node head; 
  
    static class Node { 
  
        int data; 
        Node next;
        Node prev; 

        Node(int d) 
        { 
            data = d; 
            next = null;
            prev = null; 
        } 
    }

    public static Node create_sll(int n){
        if(n <= 0){
            return null;
        }
        
        Node head = new Node(1);
        Node curr = head;

        for(int i = 2 ; i <= n ; i++){
            Node newNode = new Node(i);
            curr.next = newNode;
            curr = newNode;
        }
        return head;
    }

    public static Node create_dll(int n){
        if(n <= 0){
            return null;
        }

        Node head = new Node (1);
        Node curr = head;

        for(int i = 2 ; i <= n; i++){
            Node newNode = new Node(i);
            curr.next = newNode;
            newNode.prev = curr;
            curr = newNode;
        }
        return head;
    }

    public static Node create_cdll(int n){
        if(n <= 0){
            return null;
        }

        Node head = new Node(1);
        Node curr = head;

        for(int i = 2; i <= n; i++){
            Node newNode = new Node(i);
            curr.next = newNode;
            newNode.prev = curr;
            curr = newNode;
        }
        curr.next = head;
        head.prev = curr;
        return head;

    }

        public static Node create_csll(int n){
        if(n <= 0){
            return null;
        }

        Node head = new Node(1);
        Node curr = head;

        for(int i = 2; i <= n; i++){
            Node newNode = new Node(i);
            curr.next = newNode;
            curr = newNode;
        }
        curr.next = head;
        return head;

    }

    public void insertLast(int data){
        Node newNode = new Node(data);

        if ( head == null ) {
            head = newNode;
            return;
        }
        Node current = head;
        while(current.next != null){
            current = current.next;
        }
        current.next = newNode;
    }

    public void insertFirst(int data){
        Node newNode = new Node(data);

        newNode.next = head;
        head = newNode;
    }

    public void deleteFirst(){
        if (head == null){
            return;
        }
        head = head.next;
    }

    public void deleteLast(){

        Node current = head;
        if (head == null){
            return;
        }

        if(head.next == null){
            head = null;
            return;
        }
    
        while(current.next.next != null){
            current = current.next;
        }
        current.next = null;
    }

    public void printlist(){
        Node current = head;

        while(current != null){
            System.out.println(current.data);
            current = current.next;
            
        }
    }

    public boolean isEmpty(){
        return head == null;
        
    }

    public int size(){
        Node current = head;
        int count = 0;
        while(current != null){
            count += 1;
            current = current.next;
        }
        return count;
    }

    public int FindNode(int data){
        Node current = head;
        int index = 0;

        while (current != null){
            if (current.data == data){
                return index;
            }
            current = current.next;
            index++;
        }
        return -1;

    }
}