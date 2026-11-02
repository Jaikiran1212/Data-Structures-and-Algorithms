#include <iostream>

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    explicit Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

int height(const Node* node) {
    return node ? node->height : 0;
}

void updateHeight(Node* node) {
    const int leftHeight = height(node->left);
    const int rightHeight = height(node->right);
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

Node* rotateRight(Node* unbalanced) {
    Node* newRoot = unbalanced->left;
    Node* transferredSubtree = newRoot->right;

    newRoot->right = unbalanced;
    unbalanced->left = transferredSubtree;

    updateHeight(unbalanced);
    updateHeight(newRoot);
    return newRoot;
}

Node* rotateLeft(Node* unbalanced) {
    Node* newRoot = unbalanced->right;
    Node* transferredSubtree = newRoot->left;

    newRoot->left = unbalanced;
    unbalanced->right = transferredSubtree;

    updateHeight(unbalanced);
    updateHeight(newRoot);
    return newRoot;
}

void printInorder(const Node* node) {
    if (!node) return;
    printInorder(node->left);
    std::cout << node->key << ' ';
    printInorder(node->right);
}

void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

void printCase(const char* name, Node* root) {
    std::cout << name << " -> root " << root->key << ", inorder: ";
    printInorder(root);
    std::cout << '\n';
    destroy(root);
}

int main() {
    Node* ll = new Node(30);
    ll->left = new Node(20);
    ll->left->left = new Node(10);
    updateHeight(ll->left);
    updateHeight(ll);
    printCase("LL (right rotation)", rotateRight(ll));

    Node* rr = new Node(10);
    rr->right = new Node(20);
    rr->right->right = new Node(30);
    updateHeight(rr->right);
    updateHeight(rr);
    printCase("RR (left rotation)", rotateLeft(rr));

    Node* lr = new Node(30);
    lr->left = new Node(10);
    lr->left->right = new Node(20);
    updateHeight(lr->left);
    updateHeight(lr);
    lr->left = rotateLeft(lr->left);
    printCase("LR (left, then right)", rotateRight(lr));

    Node* rl = new Node(10);
    rl->right = new Node(30);
    rl->right->left = new Node(20);
    updateHeight(rl->right);
    updateHeight(rl);
    rl->right = rotateRight(rl->right);
    printCase("RL (right, then left)", rotateLeft(rl));

    return 0;
}
