#include <iostream>
using namespace std;

// Lớp Node đại diện cho một nút trong cây nhị phân tìm kiếm
class Node {
public:
    int value;      // Giá trị của nút
    Node* left;     // Con trái
    Node* right;    // Con phải

    Node(int value) {
        this->value = value;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    void printInOrder() {
        inOrderTraversal(root);
        cout << endl;
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }

private:
    Node* insertRecursive(Node* current, int value) {
        if (current == nullptr) return new Node(value);

        if (value < current->value)
            current->left = insertRecursive(current->left, value);
        else
            current->right = insertRecursive(current->right, value);

        return current;
    }

    Node* removeRecursive(Node* current, int value) {
        if (current == nullptr) return nullptr;

        if (value < current->value) {
            current->left = removeRecursive(current->left, value);
        } else if (value > current->value) {
            current->right = removeRecursive(current->right, value);
        } else {
            // Nút cần xóa được tìm thấy
            if (current->left == nullptr) {
                Node* replacement = current->right;
                delete current;
                return replacement;
            }

            if (current->right == nullptr) {
                Node* replacement = current->left;
                delete current;
                return replacement;
            }

            // Có cả hai con
            Node* replacement = findMin(current->right);
            current->value = replacement->value;
            current->right = removeRecursive(current->right, replacement->value);
        }

        return current;
    }

    Node* findMin(Node* current) {
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void inOrderTraversal(Node* current) {
        if (current != nullptr) {
            inOrderTraversal(current->left);
            cout << current->value << " ";
            inOrderTraversal(current->right);
        }
    }
};

int main() {
    BST tree;

    int initialValues[] = {2, 1, 10, 6, 3, 8, 7, 13, 20};
    for (int value : initialValues)
        tree.insert(value);

    cout << "Cay ban dau: ";
    tree.printInOrder();

    int insertValues[] = {14, 0, 35};
    for (int value : insertValues)
        tree.insert(value);

    cout << "Sau khi chen 14, 0, 35: ";
    tree.printInOrder();

    int deleteValues[] = {6, 13, 35};
    for (int value : deleteValues)
        tree.remove(value);

    cout << "Sau khi xoa 6, 13, 35: ";
    tree.printInOrder();
}
