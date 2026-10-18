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

void run(Node*& root, int key)
{
    // Q4: empty tree check (rule B2: nothing to find, nothing to delete)
    if (root == nullptr)
    {
        cout << "the tree is empty" << endl;
        return;
    }

    cout << "Before: "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;

    Node* parent = nullptr;             // Q3: remember the parent
    Node* cur = root;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }

    if (cur == nullptr)
    {
        cout << key << " is not in the tree: inserting it instead" << endl;
        Node* n = new Node(key);        // Q3: insert at the NULL link
        if (key < parent->data) parent->left = n;
        else parent->right = n;
    }

    cout << "After:  "; printInorder(root);
    cout << "(root = " << root->data << ")" << endl;
}

int main()
{
    Node* root = buildT();
    run(root, 25);
    freeTree(root);

    cout << "empty tree test" << endl;
    Node* empty = nullptr;
    run(empty, 25);
    return 0;
}