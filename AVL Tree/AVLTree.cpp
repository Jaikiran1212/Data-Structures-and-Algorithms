#include <iostream>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    explicit Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
    Node* root;

    static int height(const Node* node) {
        return node ? node->height : 0;
    }

    static int balanceFactor(const Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    static void updateHeight(Node* node) {
        const int leftHeight = height(node->left);
        const int rightHeight = height(node->right);
        node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    static Node* rotateRight(Node* unbalanced) {
        Node* newRoot = unbalanced->left;
        Node* transferredSubtree = newRoot->right;

        newRoot->right = unbalanced;
        unbalanced->left = transferredSubtree;

        updateHeight(unbalanced);
        updateHeight(newRoot);
        return newRoot;
    }

    static Node* rotateLeft(Node* unbalanced) {
        Node* newRoot = unbalanced->right;
        Node* transferredSubtree = newRoot->left;

        newRoot->left = unbalanced;
        unbalanced->right = transferredSubtree;

        updateHeight(unbalanced);
        updateHeight(newRoot);
        return newRoot;
    }

    static Node* rebalance(Node* node) {
        if (!node) return nullptr;

        updateHeight(node);
        const int balance = balanceFactor(node);

        if (balance > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        if (balance < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    static Node* insert(Node* node, int key) {
        if (!node) return new Node(key);

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        return rebalance(node);
    }

    static Node* minimum(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    static Node* remove(Node* node, int key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            if (!node->left || !node->right) {
                Node* child = node->left ? node->left : node->right;
                delete node;
                return child;
            }

            Node* successor = minimum(node->right);
            node->key = successor->key;
            node->right = remove(node->right, successor->key);
        }

        return rebalance(node);
    }

    static bool contains(const Node* node, int key) {
        while (node) {
            if (key == node->key) return true;
            node = key < node->key ? node->left : node->right;
        }
        return false;
    }

    static void inorder(const Node* node) {
        if (!node) return;
        inorder(node->left);
        std::cout << node->key << ' ';
        inorder(node->right);
    }

    static void preorder(const Node* node) {
        if (!node) return;
        std::cout << node->key << ' ';
        preorder(node->left);
        preorder(node->right);
    }

    static void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroy(root);
    }

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    void insert(int key) {
        root = insert(root, key);
    }

    void remove(int key) {
        root = remove(root, key);
    }

    bool contains(int key) const {
        return contains(root, key);
    }

    void printInorder() const {
        inorder(root);
        std::cout << '\n';
    }

    void printPreorder() const {
        preorder(root);
        std::cout << '\n';
    }
};

int main() {
    AVLTree tree;
    const int keys[] = {30, 20, 10, 25, 28, 27, 40, 50};

    for (int key : keys) tree.insert(key);

    std::cout << "Inorder   : ";
    tree.printInorder();
    std::cout << "Preorder  : ";
    tree.printPreorder();
    std::cout << "Contains 25: " << (tree.contains(25) ? "Yes" : "No") << '\n';

    tree.remove(30);
    std::cout << "After removing 30: ";
    tree.printInorder();

    return 0;
}
