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
    // Tree: insert 10, 20, 30 (a chain going right)
    Node* root = nullptr;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);

    cout << "Before: "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    // Delete the root 10 (one child). parent stays nullptr!
    Node* parent = nullptr;
    Node* cur = root;
    int key = 10;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }

    Node* child = (cur->left != nullptr) ? cur->left : cur->right;

    // FIX (rule B6): if there is no parent, the ROOT POINTER changes
    if (parent == nullptr)
        root = child;
    else if (parent->left == cur)
        parent->left = child;
    else
        parent->right = child;
    delete cur;

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}