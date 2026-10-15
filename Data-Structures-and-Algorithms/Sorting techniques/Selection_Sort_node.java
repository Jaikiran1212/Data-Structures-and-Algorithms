public class Selection_Sort_node {

    static class Node {
        int data;
        Node next;

        Node(int data) {
            this.data = data;
            this.next = null;
        }
    }

    Node head;

    public void selectionSortNode() {
        if (head == null || head.next == null) {
            return;
        }

        Node current = head;
        Node currentPrev = null;

        while (current != null) {
            Node min = current;
            Node minPrev = currentPrev;

            Node prev = current;
            Node temp = current.next;

            // Find minimum node and its predecessor
            while (temp != null) {
                if (temp.data < min.data) {
                    min = temp;
                    minPrev = prev;
                }
                prev = temp;
                temp = temp.next;
            }

            // Swap nodes if min is different from current
            if (min != current) {
                if (minPrev == current) {
                    // CASE 1: Nodes are adjacent (current -> min)
                    current.next = min.next;
                    min.next = current;

                    if (currentPrev == null) {
                        head = min;
                    } else {
                        currentPrev.next = min;
                    }
                } else {
                    // CASE 2: Nodes are NOT adjacent (current -> ... -> minPrev -> min)
                    Node minNext = min.next;

                    min.next = current.next;
                    minPrev.next = current;
                    current.next = minNext;

                    if (currentPrev == null) {
                        head = min;
                    } else {
                        currentPrev.next = min;
                    }
                }

                // Prepare pointers for next iteration
                currentPrev = min;
                current = min.next;
            } else {
                // No swap needed
                currentPrev = current;
                current = current.next;
            }
        }
    }
}