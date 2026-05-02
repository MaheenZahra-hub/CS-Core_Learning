#include <iostream>
using namespace std;

//           ItemType
class ItemType {
private:
    int value;

public:
    // Default constructor
    ItemType() {
        value = 0;
    }

    // Parameterized constructor
    ItemType(int v) {
        value = v;
    }

    // Getter
    int getValue() const {
        return value;
    }

    // Setter
    void setValue(int v) {
        value = v;
    }

    // Comparison operators
    bool operator<(const ItemType& other) const {
        if (value < other.value)
            return true;
        else
            return false;
    }

    bool operator>(const ItemType& other) const {
        if (value > other.value)
            return true;
        else
            return false;
    }

    bool operator==(const ItemType& other) const {
        if (value == other.value)
            return true;
        else
            return false;
    }

    // Print
    void print() const {
        cout << value<<endl;
    }
};

//               Node
struct Node {
    ItemType key;
    Node* left;
    Node* right;
    Node* parent;
    int height;

    // Constructor
    Node(const ItemType& k) {
        key = k;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

//               AVL
class AVL {
private:
    Node* root;

    // Get height
    int height(Node* n) {
        if (n == nullptr) {
            return 0;
        } else {
            return n->height;
        }
    }

    // Get balance factor
    int getBalance(Node* n) {
        if (n == nullptr) {
            return 0;
        } else {
            return height(n->left) - height(n->right);
        }
    }

    // Update height of a node
    void updateHeight(Node* n) {
        if (n == nullptr) return;
        int leftHeight = 0;
        int rightHeight = 0;
        if (n->left != nullptr) leftHeight = n->left->height;
        if (n->right != nullptr) rightHeight = n->right->height;
        if (leftHeight > rightHeight)
            n->height = leftHeight + 1;
        else
            n->height = rightHeight + 1;
    }

    // Right rotation
    Node* rightRotation(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation
    Node* leftRotation(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Balance a node
    Node* balance(Node* node) {
        updateHeight(node);
        int bf = getBalance(node);

        // Left Left Case
        if (bf > 1 && getBalance(node->left) >= 0) {
            return rightRotation(node);
        }

        
        // Left Right Case
        if (bf > 1 && getBalance(node->left) < 0) {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right Right Case
        if (bf < -1 && getBalance(node->right) <= 0) {
            return leftRotation(node);
        }

        // Right Left Case
        if (bf < -1 && getBalance(node->right) > 0) {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }    
    
    // Recursive insert
    Node* insertRec(Node* node, const ItemType& key) {
        if (node == nullptr) {
            Node* newNode = new Node(key);
            return newNode;
        }

        if (key < node->key) {
            node->left = insertRec(node->left, key);
        } else if (key > node->key) {
            node->right = insertRec(node->right, key);
        } else {
            return node; // Duplicate keys not allowed
        }

        return balance(node);
    }

    //Find node with minimum value 
    Node* minValueNode(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Recursive delete
    Node* deleteRec(Node* node, const ItemType& key) {
        if (node == nullptr) {
            return node;
        }

        if (key < node->key) {
            node->left = deleteRec(node->left, key);
            if (node->left != nullptr) node->left->parent = node;
        } else if (key > node->key) {
            node->right = deleteRec(node->right, key);
            if (node->right != nullptr) node->right->parent = node;
        } else {
            // Node found
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp;
                if (node->left != nullptr){ 
                    temp = node->left;
                }
                else {
                    temp = node->right;
                }

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } 
            else {
                Node* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteRec(node->right, temp->key);
                if (node->right != nullptr) node->right->parent = node;
            }
        }

        if (node == nullptr){
             return node;
        }

        return balance(node);
    }

    // Recursive search
    bool searchRec(Node* node, const ItemType& key) {
        if ((node == nullptr) || (key==node->key)){
            return node;
        }

        if (key < node->key) {
            return searchRec(node->left, key);
        }
        else{
        return searchRec(node->right, key);
        }
    }

    // Inorder traversal
    void inorderPrint(Node* node) {
        if (node == nullptr){
         return;
        }
        inorderPrint(node->left);
        node->key.print();
        inorderPrint(node->right);
    }

    public:
    // Constructor
    AVL() {
        root = nullptr;
    }

    void insert(const ItemType& key) {
        root = insertRec(root, key);
    }

    void deleteItem(const ItemType& key) {
        root = deleteRec(root, key);
    }

    bool search(const ItemType& key) {
        return searchRec(root, key);
    }

    void printInorder() {
        inorderPrint(root);
        cout << endl;
    }
};

//             MAIN
int main() {
    AVL tree;

    tree.insert(ItemType(10));
    tree.insert(ItemType(20));
    tree.insert(ItemType(5));
    tree.insert(ItemType(4));
    tree.insert(ItemType(8));

    cout << "Inorder: ";
    tree.printInorder();

    cout << "Search 20: ";
    if (tree.search(ItemType(20))) {
        cout << "Found" << endl;
    } else {
        cout << "Not Found" << endl;
    }
    cout<<"Value to delete: 10"<<endl;
    tree.deleteItem(ItemType(10));

    cout << "Inorder after delete: ";
    tree.printInorder();

    return 0;
}