
// cpp implementation of every pseudocode block in the write up

#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    explicit Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    // problem 1 insert(key) case 1 to 5 combined
    // returns true if inserted false if not
    bool insert(int key) {
        if (root == nullptr) {                    // i1 empty tree
            root = new Node(key);
            return true;
        }
        Node* cur = root;
        while (true) {
            if (key == cur->key) {                // i4 duplicate do nothing
                return false;
            } else if (key < cur->key) {          // i2 go left
                if (cur->left == nullptr) {       // i1 empty spot
                    cur->left = new Node(key);
                    return true;
                }
                cur = cur->left;
            } else {                              // i3 go right
                if (cur->right == nullptr) {      // i1 empty spot
                    cur->right = new Node(key);
                    return true;
                }
                cur = cur->right;
            }
        }
    }

    // problem 1 case 4  the loop that walks down with a parent pointer
    // same result as insert() kept separate to match the case 4pseudocode
    bool insertWithParent(int key) {
        Node* parent = nullptr;
        Node* cur = root;
        while (cur != nullptr) {
            parent = cur;
            if (key < cur->key)       cur = cur->left;   // i2
            else if (key > cur->key)  cur = cur->right;  // i3
            else                      return false;      // i4 duplicate
        }
        Node* newNode = new Node(key);
        if (parent == nullptr)          root = newNode;          // i1 empty tree
        else if (key < parent->key)     parent->left = newNode;  // i1 attach left
        else                            parent->right = newNode; // i1 attach right
        return true;
    }

    // problem 1 case 6 build form arr
    void buildFromArray(const int data[], int n) {
        for (int i = 0; i < n; i++) insert(data[i]);
    }

    // problem 2 serach target
    // returns true if found prints path and comparision count
    bool search(int target, int& comparisons, bool trace = true) const {
        comparisons = 0;
        Node* cur = root;
        if (trace) cout << "  path: ";
        while (cur != nullptr) {
            comparisons++;
            if (trace) cout << cur->key;
            if (target == cur->key) {                     // s2 found
                if (trace) cout << "  (S2 found)\n";
                return true;
            } else if (target < cur->key) {               // s3 go left
                if (trace) cout << " -S3-> ";
                cur = cur->left;
            } else {                                      // s4go right
                if (trace) cout << " -S4-> ";
                cur = cur->right;
            }
        }
        if (trace) cout << "NULL  (S1 not found)\n"; // s1 reached 
        return false;
    }

    // problem 2 case 6 find min and max nodes return node not key
    static Node* findMin(Node* node) {
        if (node == nullptr) return nullptr;
        Node* cur = node;
        while (cur->left != nullptr) cur = cur->left;    // keep going left
        return cur;
    }
    static Node* findMax(Node* node) {
        if (node == nullptr) return nullptr;
        Node* cur = node;
        while (cur->right != nullptr) cur = cur->right;  // keep going right
        return cur;
    }
    Node* getRoot() const { return root; }

    // problem 3 case 1 to 6 (delete node and key) all combined
    void remove(int key) { root = deleteNode(root, key); }

    // helpers for checking answers
    string levelOrder() const {
        string out;
        if (root == nullptr) return out;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* n = q.front(); q.pop();
            out += to_string(n->key) + " ";
            if (n->left)  q.push(n->left);
            if (n->right) q.push(n->right);
        }
        if (!out.empty()) out.pop_back();
        return out;
    }
    int height() const { return heightOf(root); }        // in edges empty tree = -1

private:
    Node* root;

    // delete node, key returns the new root of this subtree
    static Node* deleteNode(Node* node, int key) {
        if (node == nullptr)                       // case1 s1 key not in tree
            return nullptr;

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        } else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        } else {                                   // key == node->key found it
            if (node->left == nullptr && node->right == nullptr) {  // case2  d1 leaf
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {    // case 3 d2 only right child
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {   // case 4 d2 only left child
                Node* temp = node->left;
                delete node;
                return temp;
            } else {                               // cases 5 to 6 d3 two children
                Node* succ = findMin(node->right); // inorder successor
                node->key = succ->key;             // copy successors key
                node->right = deleteNode(node->right, succ->key); // then d1 or d2
            }
        }
        return node;
    }

    static int heightOf(Node* n) {
        if (n == nullptr) return -1;
        int l = heightOf(n->left), r = heightOf(n->right);
        return 1 + (l > r ? l : r);
    }

    static void destroy(Node* n) {
        if (n == nullptr) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
};


const int ARR[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 75};
const int N = 11;

int main() {
    // problem 1
    cout << "Problem 1: Insert\n";
    BST tree;
    tree.buildFromArray(ARR, N);
    cout << "Level order of final tree: " << tree.levelOrder() << "\n";
    cout << "Height (edges): " << tree.height() << "\n";

    cout << "Case 5: insert 40 again -> "
              << (tree.insert(40) ? "inserted" : "duplicate, ignored (I4)") << "\n";

    BST sortedTree;                                   // case 6
    const int sortedKeys[] = {20, 30, 40, 50, 60};
    sortedTree.buildFromArray(sortedKeys, 5);
    cout << "Case 6: sorted input level order: " << sortedTree.levelOrder()
              << ", height = " << sortedTree.height() << "\n";

    BST loopTree;                                     // case 4 loop version gives same tree
    for (int i = 0; i < N; i++) loopTree.insertWithParent(ARR[i]);
    cout << "Case 4 loop version level order: " << loopTree.levelOrder() << "\n";

    // problem 2
    cout << "\nProblem 2: Search\n";
    const int targets[] = {50, 45, 65, 33, 90};
    for (int t : targets) {
        int comps = 0;
        cout << "Search " << t << ":\n";
        bool found = tree.search(t, comps);
        cout << "  result: " << (found ? "found" : "not found")
                  << ", comparisons: " << comps << "\n";
    }
    cout << "Case 6: min = " << BST::findMin(tree.getRoot())->key
              << ", max = " << BST::findMax(tree.getRoot())->key << "\n";

    int worst = 0;                                    // part g
    for (int k = 0; k <= 100; k++) {
        int c = 0;
        tree.search(k, c, false);
        if (c > worst) worst = c;
    }
    cout << "Largest number of comparisons: " << worst
              << " (height + 1 = " << tree.height() + 1 << ")\n";

    // problem 3 
    // each case starts again from the original final tree of problem 1
    cout << "\nProblem 3: Delete\n";
    const int toDelete[] = {33, 20, 60, 80, 40, 50};
    for (int i = 0; i < 6; i++) {
        BST t;
        t.buildFromArray(ARR, N);
        t.remove(toDelete[i]);
        cout << "Case " << i + 1 << ": delete " << toDelete[i]
                  << " -> " << t.levelOrder() << "\n";
    }
    return 0;
}