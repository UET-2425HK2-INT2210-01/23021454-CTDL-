#include <iostream>
using namespace std;

// Cấu trúc một nút trong cây nhị phân tìm kiếm (BST)
struct Node {
    int value;        // Giá trị của nút
    Node* left;       // Con trỏ đến nút con bên trái
    Node* right;      // Con trỏ đến nút con bên phải

    Node(int targetValue) {
        value = targetValue;
        left = right = nullptr;
    }
};

// Hàm thêm một giá trị mới vào cây BST
Node* insert(Node* current, int targetValue) {
    if (current == nullptr)
        return new Node(targetValue);
    if (targetValue < current->value)
        current->left = insert(current->left, targetValue);
    else
        current->right = insert(current->right, targetValue);
    return current;
}

// Hàm tìm nút có giá trị nhỏ nhất trong cây con
Node* getMin(Node* current) {
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// Hàm xóa một giá trị khỏi cây BST
Node* remove(Node* current, int targetValue) {
    if (current == nullptr)
        return nullptr;
    if (targetValue < current->value)
        current->left = remove(current->left, targetValue);
    else if (targetValue > current->value)
        current->right = remove(current->right, targetValue);
    else {
        // Tìm thấy nút cần xóa
        if (current->left == nullptr) {
            Node* replacementNode = current->right;
            delete current;
            return replacementNode;
        } else if (current->right == nullptr) {
            Node* replacementNode = current->left;
            delete current;
            return replacementNode;
        }

        Node* replacementNode = getMin(current->right);
        current->value = replacementNode->value;
        current->right = remove(current->right, replacementNode->value);
    }
    return current;
}

// Hàm duyệt cây theo thứ tự LNR (in-order)
void inorder(Node* current) {
    if (current == nullptr) return;
    inorder(current->left);
    cout << current->value << " ";
    inorder(current->right);
}

// Hàm chính
int main() {
    Node* root = nullptr;

    int initialValues[] = {2, 1, 10, 6, 3, 8, 7, 13, 20};
    for (int targetValue : initialValues)
        root = insert(root, targetValue);

    cout << "BST ban dau (in-order): ";
    inorder(root);
    cout << endl;

    int valuesToAdd[] = {14, 0, 35};
    for (int targetValue : valuesToAdd)
        root = insert(root, targetValue);

    cout << "BST sau khi them 14, 0, 35: ";
    inorder(root);
    cout << endl;

    int valuesToRemove[] = {6, 13, 35};
    for (int targetValue : valuesToRemove)
        root = remove(root, targetValue);

    cout << "BST sau khi xoa 6, 13, 35: ";
    inorder(root);
    cout << endl;
}
