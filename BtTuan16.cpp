#include <algorithm> 
#include <iostream>  
#include <queue>     

using namespace std; 

using node = struct node {
    int data;          // Dữ liệu của node
    int height;        // Chiều cao của node
    struct node *left; // Con trỏ tới con trái
    struct node *right;// Con trỏ tới con phải
};

// Tạo một node mới
node *createNode(int data) {
    node *nn = new node();
    nn->data = data;
    nn->height = 1; // Khởi tạo chiều cao của node là 1 (cho node lá)
    nn->left = nullptr;
    nn->right = nullptr;
    return nn;
}

// Lấy chiều cao của cây
int height(node *root) {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}

// Cập nhật chiều cao của node
void updateHeight(node *root) {
    root->height = 1 + max(height(root->left), height(root->right));
}

// Lấy hệ số cân bằng (balance factor) của node
int getBalance(node *root) {
    return height(root->left) - height(root->right);
}

// Quay phải cây tại node
node *rightRotate(node *root) {
    node *t = root->left;
    node *u = t->right;
    t->right = root;
    root->left = u;
    updateHeight(root);
    updateHeight(t);
    return t;
}

// Quay trái cây tại node
node *leftRotate(node *root) {
    node *t = root->right;
    node *u = t->left;
    t->left = root;
    root->right = u;
    updateHeight(root);
    updateHeight(t);
    return t;
}

// Xoay kép (Left-Right)
node *leftRightRotate(node *root) {
    root->left = leftRotate(root->left);  // Quay trái cây con trái
    return rightRotate(root);  // Sau đó quay phải cây gốc
}

// Xoay kép (Right-Left)
node *rightLeftRotate(node *root) {
    root->right = rightRotate(root->right);  // Quay phải cây con phải
    return leftRotate(root);  // Sau đó quay trái cây gốc
}

// Duyệt cây theo thứ tự vào ô (In-order)
void inOrder(node *root) {
    if (root == nullptr) {
        return;
    }
    // Duyệt cây con trái
    inOrder(root->left);
    // In ra dữ liệu của node hiện tại
    cout << root->data << " ";
    // Duyệt cây con phải
    inOrder(root->right);
}

// Duyệt cây theo thứ tự trước (Pre-order)
void preOrder(node *root) {
    if (root == nullptr) {
        return;
    }
    // In ra dữ liệu của node hiện tại
    cout << root->data << " ";
    // Duyệt cây con trái
    preOrder(root->left);
    // Duyệt cây con phải
    preOrder(root->right);
}

// Duyệt cây theo thứ tự sau (Post-order)
void postOrder(node *root) {
    if (root == nullptr) {
        return;
    }
    // Duyệt cây con trái
    postOrder(root->left);
    // Duyệt cây con phải
    postOrder(root->right);
    // In ra dữ liệu của node hiện tại
    cout << root->data << " ";
}

int main() {
    node *root = nullptr;

    // Tạo cây với các node và thực hiện quay
    root = createNode(30);
    root->left = createNode(20);
    root->right = createNode(40);
    root->left->left = createNode(10);
    root->left->right = createNode(25);
    
    // Cây hiện tại sẽ không cân bằng, ta sẽ thực hiện quay
    root = leftRotate(root); // Quay trái cây gốc

    // In ra kết quả duyệt cây theo các cách khác nhau
    cout << "InOrder: ";
    inOrder(root);
    cout << "\n";

    cout << "PreOrder: ";
    preOrder(root);
    cout << "\n";

    cout << "PostOrder: ";
    postOrder(root);
    cout << "\n";

    return 0;
}
