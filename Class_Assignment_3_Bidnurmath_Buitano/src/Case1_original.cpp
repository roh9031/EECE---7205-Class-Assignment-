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

    // Case 1: delete the root (40). It has two children.
    Node* parent = root;
    Node* succ = root->right; // go right once (60)
    while (succ->left != nullptr) // then left as far as possible
    {
        parent = succ;
        succ = succ->left;
    }

    root->data = succ->data; // root now holds 50

    if (parent == root)
        parent->right = succ->right;
    else
        parent->left = succ->right;
    delete succ;

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}