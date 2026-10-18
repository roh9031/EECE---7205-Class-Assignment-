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

// Returns the (possibly new) root. Time: O(h).
Node* deleteNode(Node* root, int key)
{
    Node* parent = nullptr;
    Node* cur = root;

    // B1: search, remembering the parent
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else cur = cur->right;
    }

    // B2: not found
    if (cur == nullptr) return root;

    // B5: two children -> copy successor, then delete the successor node
    if (cur->left != nullptr && cur->right != nullptr)
    {
        Node* sp = cur;
        Node* succ = cur->right;
        while (succ->left != nullptr)
        {
            sp = succ;
            succ = succ->left;
        }
        cur->data = succ->data;
        if (sp == cur) sp->right = succ->right;
        else sp->left = succ->right;
        delete succ;
        return root;
    }

    // B3 / B4 (and B6): zero or one child
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent == nullptr) root = child;          // B6: root pointer changes
    else if (parent->left == cur) parent->left = child;
    else parent->right = child;
    delete cur;
    return root;
}

int main()
{
    Node* root = buildT();
    cout << "Start: "; printInorder(root); cout << endl;

    int keys[] = {40, 10, 60, 25};
    for (int k : keys)
    {
        root = deleteNode(root, k);
        cout << "Delete " << k << ": "; printInorder(root); cout << endl;
    }

    freeTree(root);
    return 0;
}