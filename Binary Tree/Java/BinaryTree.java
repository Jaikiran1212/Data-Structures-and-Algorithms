/*
 * Binary Tree - Complete Template (Java)
 * --------------------------------------
 * Operations : level-order insert, preorder / inorder / postorder / level-order
 *              traversal, search, count nodes, count leaves, height
 * Restriction: no java.util collections - the queue is a plain array.
 *
 * Time complexity (n = number of nodes)
 *   insertLevel ........ O(n)
 *   pre/in/post-order .. O(n)
 *   levelorder ......... O(n)
 *   search ............. O(n)   (tree is NOT sorted, so every node may be checked)
 *   countNodes/Leaves .. O(n)
 *   height ............. O(n)
 *
 * Compile : javac BinaryTree.java
 * Run     : java BinaryTree
 */
public class BinaryTree {

    static final int QMAX = 100;        // maximum size of the array-based queue

    // One node of the tree
    static class Node {
        int data;
        Node left, right;

        Node(int x) {
            data = x;
            left = right = null;        // a new node has no children yet
        }
    }

    private Node root;

    public BinaryTree() {
        root = null;
    }

    public Node getRoot() {
        return root;
    }

    // ---------- private recursive helpers ----------

    // Preorder: Node -> Left -> Right
    private void pre(Node p) {
        if (p == null) return;          // base case: empty subtree
        System.out.print(p.data + " ");
        pre(p.left);
        pre(p.right);
    }

    // Inorder: Left -> Node -> Right
    private void in(Node p) {
        if (p == null) return;
        in(p.left);
        System.out.print(p.data + " ");
        in(p.right);
    }

    // Postorder: Left -> Right -> Node
    private void post(Node p) {
        if (p == null) return;
        post(p.left);
        post(p.right);
        System.out.print(p.data + " ");
    }

    // Search every node for the value x
    private boolean find(Node p, int x) {
        if (p == null) return false;
        if (p.data == x) return true;
        if (find(p.left, x)) return true;
        return find(p.right, x);
    }

    // Total number of nodes
    private int nodes(Node p) {
        if (p == null) return 0;
        return 1 + nodes(p.left) + nodes(p.right);
    }

    // Number of leaf nodes (nodes with no children)
    private int leaves(Node p) {
        if (p == null) return 0;
        if (p.left == null && p.right == null) return 1;
        return leaves(p.left) + leaves(p.right);
    }

    // Height = number of levels
    private int ht(Node p) {
        if (p == null) return 0;
        int leftHeight = ht(p.left);
        int rightHeight = ht(p.right);
        if (leftHeight > rightHeight) return leftHeight + 1;
        return rightHeight + 1;
    }

    // ---------- public operations ----------

    // Level-order insertion: fills the first empty slot, left to right.
    public void insertLevel(int x) {
        Node n = new Node(x);
        if (root == null) {
            root = n;
            return;
        }
        Node[] q = new Node[QMAX];      // array used as a queue
        int f = 0, r = 0;               // f = front index, r = rear index
        q[r++] = root;
        while (f < r) {
            Node p = q[f++];            // take the front node
            if (p.left == null) {
                p.left = n;
                return;
            }
            q[r++] = p.left;
            if (p.right == null) {
                p.right = n;
                return;
            }
            q[r++] = p.right;
        }
    }

    public void preorder()  { pre(root); }
    public void inorder()   { in(root); }
    public void postorder() { post(root); }

    // Level-order (breadth-first) traversal using the array queue
    public void levelorder() {
        if (root == null) return;
        Node[] q = new Node[QMAX];
        int f = 0, r = 0;
        q[r++] = root;
        while (f < r) {
            Node p = q[f++];
            System.out.print(p.data + " ");
            if (p.left != null)  q[r++] = p.left;
            if (p.right != null) q[r++] = p.right;
        }
    }

    public boolean search(int x) { return find(root, x); }
    public int countNodes()      { return nodes(root); }
    public int countLeaves()     { return leaves(root); }
    public int height()          { return ht(root); }

    public static void main(String[] args) {
        BinaryTree t = new BinaryTree();
        int[] a = {1, 2, 3, 4, 5, 6};
        for (int i = 0; i < 6; i++) t.insertLevel(a[i]);

        System.out.print("Preorder   : ");  t.preorder();   System.out.println();
        System.out.print("Inorder    : ");  t.inorder();    System.out.println();
        System.out.print("Postorder  : ");  t.postorder();  System.out.println();
        System.out.print("Level order: ");  t.levelorder(); System.out.println();

        System.out.println("Search 5   : " + (t.search(5) ? "Found" : "Not found"));
        System.out.println("Nodes      : " + t.countNodes());
        System.out.println("Leaves     : " + t.countLeaves());
        System.out.println("Height     : " + t.height());
    }
}
