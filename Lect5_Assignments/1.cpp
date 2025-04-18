#include <iostream>

using namespace std;

// Cấu trúc Node biểu diễn mỗi nút trong cây
struct TreeNode {
    int data;               // Giá trị của nút
    TreeNode* firstChild;   // Con trỏ đến con đầu tiên
    TreeNode* nextSibling;  // Con trỏ đến anh chị em tiếp theo
};

// Hàm tạo một nút mới
TreeNode* createNode(int value) {
    TreeNode* newNode = new TreeNode();
    newNode->data = value;
    newNode->firstChild = nullptr;
    newNode->nextSibling = nullptr;
    return newNode;
}

// Hàm thêm một nút con vào nút cha
void addChild(TreeNode* parent, TreeNode* child) {
    if (parent->firstChild == nullptr) {
        parent->firstChild = child;
    } else {
        TreeNode* current = parent->firstChild;
        while (current->nextSibling != nullptr) {
            current = current->nextSibling;
        }
        current->nextSibling = child;
    }
}

// Hàm xây dựng cây từ danh sách cạnh
TreeNode* buildTree(int nodeCount, int edgeCount, int edges[][2]) {
    TreeNode* nodeList[100] = {nullptr};

    for (int i = 1; i <= nodeCount; i++) {
        nodeList[i] = createNode(i);
    }

    for (int i = 0; i < edgeCount; i++) {
        int parent = edges[i][0];
        int child = edges[i][1];
        addChild(nodeList[parent], nodeList[child]);
    }

    bool isChild[100] = {false};
    for (int i = 0; i < edgeCount; i++) {
        isChild[edges[i][1]] = true;
    }
    for (int i = 1; i <= nodeCount; i++) {
        if (!isChild[i]) {
            return nodeList[i];
        }
    }
    return nullptr;
}

// Hàm tính chiều cao của cây
int calculateHeight(TreeNode* root) {
    if (root == nullptr) return 0;

    int maxSubtreeHeight = 0;
    for (TreeNode* child = root->firstChild; child != nullptr; child = child->nextSibling) {
        int childHeight = calculateHeight(child);
        if (childHeight > maxSubtreeHeight) {
            maxSubtreeHeight = childHeight;
        }
    }
    return maxSubtreeHeight + 1;
}

// Hàm duyệt tiền thứ tự (Pre-order)
void preorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    cout << root->data << " ";
    for (TreeNode* child = root->firstChild; child != nullptr; child = child->nextSibling) {
        preorderTraversal(child);
    }
}

// Hàm duyệt hậu thứ tự (Post-order)
void postorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    for (TreeNode* child = root->firstChild; child != nullptr; child = child->nextSibling) {
        postorderTraversal(child);
    }
    cout << root->data << " ";
}

// Hàm kiểm tra cây nhị phân
bool isBinaryTree(TreeNode* root) {
    if (root == nullptr) return true;

    int childCount = 0;
    for (TreeNode* child = root->firstChild; child != nullptr; child = child->nextSibling) {
        childCount++;
        if (childCount > 2) return false;
    }

    for (TreeNode* child = root->firstChild; child != nullptr; child = child->nextSibling) {
        if (!isBinaryTree(child)) return false;
    }

    return true;
}

// Hàm duyệt trung thứ tự (In-order) cho cây nhị phân
void inorderTraversal(TreeNode* root) {
    if (root == nullptr) return;

    TreeNode* leftChild = root->firstChild;
    TreeNode* rightChild = (leftChild != nullptr) ? leftChild->nextSibling : nullptr;

    inorderTraversal(leftChild);
    cout << root->data << " ";
    inorderTraversal(rightChild);
}

int main() {
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);

    int nodeCount, edgeCount;
    cin >> nodeCount >> edgeCount;

    int edges[100][2];
    for (int i = 0; i < edgeCount; i++) {
        cin >> edges[i][0] >> edges[i][1];
    }

    TreeNode* root = buildTree(nodeCount, edgeCount, edges);

    cout << calculateHeight(root) - 1 << endl;
    preorderTraversal(root);
    cout << endl;
    postorderTraversal(root);
    cout << endl;

    if (isBinaryTree(root)) {
        inorderTraversal(root);
    } else {
        cout << "NOT BINARY TREE";
    }
}
