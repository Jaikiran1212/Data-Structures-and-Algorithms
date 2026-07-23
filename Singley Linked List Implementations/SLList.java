public class SLList{ 
  
    Node head; 
  
    static class Node { 
  
        int data; 
        Node next; 

        Node(int d) 
        { 
            data = d; 
            next = null; 
        } 
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