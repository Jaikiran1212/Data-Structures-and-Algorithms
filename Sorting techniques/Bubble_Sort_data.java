public class Bubble_Sort_data {

    class Node{
        Node next;
        int data;

        Node(int data){
            this.data = data;
            this.next = null;
        }
    }
    Node head;

    public void bubbleSortdata(){

        if (head == null || head.next == null){
            return;
        }

        boolean swapped;
        do{
            swapped = false;
            Node curr = head;
            while(curr.next != null){
                if(curr.data > curr.next.data){

                    int temp = curr.data;
                    curr.data = curr.next.data;
                    curr.next.data = temp;

                    swapped = true;
                }
                curr = curr.next;
            }
        }while(swapped);
    }
}
