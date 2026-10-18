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

    Node* cur = root;
    int key = 60;                       // changed from 20
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }

    Node* parent = cur;
    Node* succ = cur->right;
    while (succ->left != nullptr)
    {
        parent = succ;
        succ = succ->left;
    }
    cout << "succ = " << succ->data << ", parent = " << parent->data << endl;

    cur->data = succ->data;

    if (parent == cur)
    {
        cout << "branch: parent == cur  -> parent->right = succ->right" << endl;
        parent->right = succ->right;
    }
    else
    {
        cout << "branch: else  -> parent->left = succ->right" << endl;
        parent->left = succ->right;
    }
    delete succ;

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}