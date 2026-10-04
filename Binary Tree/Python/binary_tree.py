"""
Binary Tree - Complete Template (Python)
----------------------------------------
Operations : level-order insert, preorder / inorder / postorder / level-order
             traversal, search, count nodes, count leaves, height
Restriction: no collections.deque / queue module - the queue is a plain list
             that is read with a moving front index.

Time complexity (n = number of nodes)
  insert_level ........ O(n)
  pre/in/post-order ... O(n)
  level_order ......... O(n)
  search .............. O(n)   (tree is NOT sorted, so every node may be checked)
  count_nodes/leaves .. O(n)
  height .............. O(n)

Run : python binary_tree.py
"""


class Node:
    """One node of the tree."""

    def __init__(self, data):
        self.data = data
        self.left = None            # a new node has no children yet
        self.right = None


class BinaryTree:
    def __init__(self):
        self.root = None

    # ---------- private recursive helpers ----------

    def _pre(self, p):
        """Preorder: Node -> Left -> Right"""
        if p is None:               # base case: empty subtree
            return
        print(p.data, end=" ")
        self._pre(p.left)
        self._pre(p.right)

    def _in(self, p):
        """Inorder: Left -> Node -> Right"""
        if p is None:
            return
        self._in(p.left)
        print(p.data, end=" ")
        self._in(p.right)

    def _post(self, p):
        """Postorder: Left -> Right -> Node"""
        if p is None:
            return
        self._post(p.left)
        self._post(p.right)
        print(p.data, end=" ")

    def _find(self, p, x):
        """Search every node for the value x."""
        if p is None:
            return False
        if p.data == x:
            return True
        if self._find(p.left, x):
            return True
        return self._find(p.right, x)

    def _nodes(self, p):
        """Total number of nodes."""
        if p is None:
            return 0
        return 1 + self._nodes(p.left) + self._nodes(p.right)

    def _leaves(self, p):
        """Number of leaf nodes (nodes with no children)."""
        if p is None:
            return 0
        if p.left is None and p.right is None:
            return 1
        return self._leaves(p.left) + self._leaves(p.right)

    def _ht(self, p):
        """Height = number of levels."""
        if p is None:
            return 0
        left_height = self._ht(p.left)
        right_height = self._ht(p.right)
        if left_height > right_height:
            return left_height + 1
        return right_height + 1

    # ---------- public operations ----------

    def get_root(self):
        return self.root

    def insert_level(self, x):
        """Level-order insertion: fills the first empty slot, left to right."""
        n = Node(x)
        if self.root is None:
            self.root = n
            return
        q = [self.root]             # list used as a queue
        f = 0                       # f = front index
        while f < len(q):
            p = q[f]                # take the front node
            f += 1
            if p.left is None:
                p.left = n
                return
            q.append(p.left)
            if p.right is None:
                p.right = n
                return
            q.append(p.right)

    def preorder(self):
        self._pre(self.root)

    def inorder(self):
        self._in(self.root)

    def postorder(self):
        self._post(self.root)

    def level_order(self):
        """Level-order (breadth-first) traversal using the list queue."""
        if self.root is None:
            return
        q = [self.root]
        f = 0
        while f < len(q):
            p = q[f]
            f += 1
            print(p.data, end=" ")
            if p.left is not None:
                q.append(p.left)
            if p.right is not None:
                q.append(p.right)

    def search(self, x):
        return self._find(self.root, x)

    def count_nodes(self):
        return self._nodes(self.root)

    def count_leaves(self):
        return self._leaves(self.root)

    def height(self):
        return self._ht(self.root)


if __name__ == "__main__":
    t = BinaryTree()
    for value in [1, 2, 3, 4, 5, 6]:
        t.insert_level(value)

    print("Preorder   : ", end="");  t.preorder();    print()
    print("Inorder    : ", end="");  t.inorder();     print()
    print("Postorder  : ", end="");  t.postorder();   print()
    print("Level order: ", end="");  t.level_order(); print()

    print("Search 5   :", "Found" if t.search(5) else "Not found")
    print("Nodes      :", t.count_nodes())
    print("Leaves     :", t.count_leaves())
    print("Height     :", t.height())
