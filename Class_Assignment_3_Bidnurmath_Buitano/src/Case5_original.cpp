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

    // Case 5: key is not in the tree (25)
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }

    if (cur == nullptr)
        cout << key << " is not in the tree: nothing to delete" << endl;

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}