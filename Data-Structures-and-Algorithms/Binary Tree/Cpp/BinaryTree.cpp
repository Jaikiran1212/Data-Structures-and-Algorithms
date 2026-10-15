/*
 * Binary Tree - Complete Template (C++)
 * -------------------------------------
 * Operations : level-order insert, preorder / inorder / postorder / level-order
 *              traversal, search, count nodes, count leaves, height
 * Restriction: no STL containers - the queue is a plain array.
 *
 * Time complexity (n = number of nodes)
 *   insertLevel ........ O(n)
 *   pre/in/post-order .. O(n)
 *   levelorder ......... O(n)
 *   search ............. O(n)   (tree is NOT sorted, so every node may be checked)
 *   countNodes/Leaves .. O(n)
 *   height ............. O(n)
 *
 * Compile : g++ BinaryTree.cpp -o binarytree
 * Run     : ./binarytree
 */
#include <iostream>
using namespace std;

const int QMAX = 100;               // maximum size of the array-based queue

// One node of the tree
struct Node {
    int data;
    Node *left, *right;

    Node(int x) {
        data = x;
        left = right = NULL;        // a new node has no children yet
    }
};

class BinaryTree {
    Node* root;

    // ---------- private recursive helpers ----------

    // Preorder: Node -> Left -> Right
    void pre(Node* p) {
        if (!p) return;             // base case: empty subtree
        cout << p->data << ' ';
        pre(p->left);
        pre(p->right);
    }

    // Inorder: Left -> Node -> Right
    void in(Node* p) {
        if (!p) return;
        in(p->left);
        cout << p->data << ' ';
        in(p->right);
    }

    // Postorder: Left -> Right -> Node
    void post(Node* p) {
        if (!p) return;
        post(p->left);
        post(p->right);
        cout << p->data << ' ';
    }

    // Search every node for the value x
    bool find(Node* p, int x) {
        if (p == NULL) return false;
        if (p->data == x) return true;
        if (find(p->left, x)) return true;
        return find(p->right, x);
    }

    // Total number of nodes
    int nodes(Node* p) {
        if (p == NULL) return 0;
        return 1 + nodes(p->left) + nodes(p->right);
    }

    // Number of leaf nodes (nodes with no children)
    int leaves(Node* p) {
        if (p == NULL) return 0;
        if (p->left == NULL && p->right == NULL) return 1;
        return leaves(p->left) + leaves(p->right);
    }

    // Height = number of levels
    int ht(Node* p) {
        if (p == NULL) return 0;
        int leftHeight = ht(p->left);
        int rightHeight = ht(p->right);
        if (leftHeight > rightHeight) return leftHeight + 1;
        return rightHeight + 1;
    }

public:
    BinaryTree() {
        root = NULL;
    }

    Node* getRoot() {
        return root;
    }

    // Level-order insertion: fills the first empty slot, left to right.
    void insertLevel(int x) {
        Node* n = new Node(x);
        if (!root) {
            root = n;
            return;
        }
        Node* q[QMAX];              // array used as a queue
        int f = 0, r = 0;           // f = front index, r = rear index
        q[r++] = root;
        while (f < r) {
            Node* p = q[f++];       // take the front node
            if (!p->left) {
                p->left = n;
                return;
            }
            q[r++] = p->left;
            if (!p->right) {
                p->right = n;
                return;
            }
            q[r++] = p->right;
        }
    }

    void preorder()  { pre(root); }
    void inorder()   { in(root); }
    void postorder() { post(root); }

    // Level-order (breadth-first) traversal using the array queue
    void levelorder() {
        if (!root) return;
        Node* q[QMAX];
        int f = 0, r = 0;
        q[r++] = root;
        while (f < r) {
            Node* p = q[f++];
            cout << p->data << ' ';
            if (p->left)  q[r++] = p->left;
            if (p->right) q[r++] = p->right;
        }
    }

    bool search(int x)  { return find(root, x); }
    int countNodes()    { return nodes(root); }
    int countLeaves()   { return leaves(root); }
    int height()        { return ht(root); }
};

int main() {
    BinaryTree t;
    int a[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; i++) t.insertLevel(a[i]);

    cout << "Preorder   : ";  t.preorder();   cout << '\n';
    cout << "Inorder    : ";  t.inorder();    cout << '\n';
    cout << "Postorder  : ";  t.postorder();  cout << '\n';
    cout << "Level order: ";  t.levelorder(); cout << '\n';

    cout << "Search 5   : " << (t.search(5) ? "Found" : "Not found") << '\n';
    cout << "Nodes      : " << t.countNodes()  << '\n';
    cout << "Leaves     : " << t.countLeaves() << '\n';
    cout << "Height     : " << t.height()      << '\n';
    return 0;
}
