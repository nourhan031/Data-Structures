#include <iostream>
#include <stdexcept>
#include <stack>

using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T data;
        Node *left;
        Node *right;

        Node(Node *left, Node *right, const T &elem) : data(elem), left(left), right(right) {}
    };

    int nodeCount;
    Node *root;

    Node *add(Node *node, const T &elem) {
        if (node == nullptr) {
            node = new Node(nullptr, nullptr, elem);
        } else {
            if (elem < node->data) {
                node->left = add(node->left, elem);
            } else {
                node->right = add(node->right, elem);
            }
        }
        return node;
    }

    Node *remove(Node *node, const T &elem) {
        if (node == nullptr) return nullptr;

        if (elem < node->data) {
            node->left = remove(node->left, elem);
        } else if (elem > node->data) {
            node->right = remove(node->right, elem);
        } else {
            if (node->left == nullptr) {
                Node *rightChild = node->right;
                delete node;
                return rightChild;
            } else if (node->right == nullptr) {
                Node *leftChild = node->left;
                delete node;
                return leftChild;
            } else {
                Node *tmp = findMin(node->right);
                node->data = tmp->data;
                node->right = remove(node->right, tmp->data);
            }
        }
        return node;
    }

    Node *findMin(Node *node) {
        while (node->left != nullptr) node = node->left;
        return node;
    }

    Node *findMax(Node *node) {
        while (node->right != nullptr) node = node->right;
        return node;
    }

    bool contains(Node *node, const T &elem) {
        if (node == nullptr) return false;

        if (elem < node->data) return contains(node->left, elem);
        else if (elem > node->data) return contains(node->right, elem);
        else return true; // Element found in the tree
    }

    int height(Node *node) {
        if (node == nullptr) return 0;
        return max(height(node->left), height(node->right)) + 1;
    }

public:
    BST() : nodeCount(0), root(nullptr) {}

    bool isEmpty() const {
        return size() == 0;
    }

    int size() const {
        return nodeCount;
    }

    bool add(const T &elem) {
        if (contains(root, elem)) {
            return false;
        } else {
            root = add(root, elem);
            nodeCount++;
            return true;
        }
    }

    bool remove(const T &elem) {
        if (contains(root, elem)) {
            root = remove(root, elem);
            nodeCount--;
            return true;
        }
        return false;
    }

    bool contains(const T &elem) const {
        return contains(elem);
    }

    int height() const {
        return height(root);
    }

    enum TreeTraversalOrder {
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER,
        LEVEL_ORDER
    };
};