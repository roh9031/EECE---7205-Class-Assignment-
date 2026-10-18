#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;
    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

Node* insertNode(Node* root, int value)
{
    if (root == nullptr) return new Node(value);
    if (value < root->data) root->left = insertNode(root->left, value);
    else root->right = insertNode(root->right, value);
    return root;
}

Node* buildT()
{
    Node* root = nullptr;
    int keys[] = {40, 20, 60, 10, 30, 50, 70};
    for (int k : keys) root = insertNode(root, k);
    return root;
}

int main()
{
    Node* root = buildT();

    cout << "Before: "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    // First remove 50 so that 60 has only one child (70)
    delete root->right->left;
    root->right->left = nullptr;
    cout << "Middle: ";
    printInorder(root);
    cout << " (60 now has one child, 70)" << endl;

    // Case 3: delete 60 (node with one child)
    Node* parent = nullptr;
    Node* cur = root;
    int key = 60;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }

    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent->left == cur) parent->left = child;
    else parent->right = child;
    delete cur;

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}