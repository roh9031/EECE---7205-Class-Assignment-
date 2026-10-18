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

void printPreorder(Node* node)
{
    if (node == nullptr) return;
    cout << node->data << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

int main()
{
    Node* root = buildT();
    cout << "Before: "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    // Case 1 (Q3): delete the root using the inorder PREDECESSOR
    // 1. go left once, then right as far as possible
    Node* parent = root;
    Node* pred = root->left;            // go left once (20)
    while (pred->right != nullptr)      // then right as far as possible
    {
        parent = pred;
        pred = pred->right;             // pred = 30, parent = 20
    }

    // 2. copy the predecessor's value into the root
    root->data = pred->data;

    // 3. remove the predecessor node (it has no right child)
    if (parent == root)
        parent->left = pred->left;
    else
        parent->right = pred->left;
    delete pred;

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;
    cout << "Preorder: "; printPreorder(root); cout << endl;

    freeTree(root);
    return 0;
}