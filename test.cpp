#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr)             return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr)             return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* z) {
        Node* y = z->left;
        Node* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* rotateLeft(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insertNodeRecursive(Node* current, int value) {
        if (current == nullptr) {
            return new Node(value);
        }

        if (value < current->data) {
            current->left = insertNodeRecursive(current->left, value);
        } else {
            current->right = insertNodeRecursive(current->right, value);
        }

        current->height = 1 + max(getHeight(current->left), getHeight(current->right));

        int balanceFactor = getBalanceFactor(current);

        // Left Left Case
        if (balanceFactor > 1 && value < current->left->data) {
            return rotateRight(current);
        }

        // Right Right Case
        if (balanceFactor < -1 && value > current->right->data) {
            return rotateLeft(current);
        }

        // Left Right Case
        if (balanceFactor > 1 && value > current->left->data) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }

        // Right Left Case
        if (balanceFactor < -1 && value < current->right->data) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }

        return current;
    }

    void levelOrderTraversal(Node* current) {
        if (current == nullptr) {
            return;
        }

        queue<Node*> q;
        q.push(current);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            cout << node->data << " ";

            if (node->left != nullptr) {
                q.push(node->left);
            }

            if (node->right != nullptr) {
                q.push(node->right);
            }
        }

        cout << endl;
    }

    int getHeightRecursive(Node* current) {
        if (current == nullptr) {
            return 0;
        }
        return 1 + max(getHeightRecursive(current->left), getHeightRecursive(current->right));
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insertNode(int value) {
        root = insertNodeRecursive(root, value);
    }

    void levelOrderTraversal() {
        levelOrderTraversal(root);
    }

    void printHeight() {
        int height = getHeightRecursive(root);
        cout << "Height of the tree: " << height << endl;
    }
};

int main() {
    AVLTree tree;
    int n, value;

    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the values of the nodes: ";
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree.insertNode(value);
    }

    cout << "Level Order Traversal: ";
    tree.levelOrderTraversal();

    tree.printHeight();

    return 0;
}
