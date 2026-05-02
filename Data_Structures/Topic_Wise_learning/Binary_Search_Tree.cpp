#include<iostream>
using namespace std;

class ItemType{
    private:
        int value;
    public:
        ItemType(){
            value=0;
        }

        ItemType(int val){
            value=val;
        }

        void SetValue(int num){
            value=num;
        }

        int GetValue() const {
            return value;
        }

        bool operator< (ItemType& other) const{
            return value < other.value;
        }
        
        bool operator> (ItemType& other) const{
            return value > other.value;
        }

        bool operator== (ItemType& other) const{
            return value == other.value;
        }
};

struct NodeType 
{
    ItemType key;
    NodeType* left;
    NodeType* right;
    NodeType* parent;
    NodeType (ItemType& k){
        key=k;
        left=nullptr;
        right=nullptr;
        parent=nullptr;
    }
};

class BST{ 
    private:
        NodeType* root;
        void transplant(NodeType* u, NodeType* v){
            if(u->parent==NULL){
                root=v;
            }
            else if(u==u->parent->left){
                u->parent->left=v;
            }
            else{
                u->parent->right=v;
            }
            if(v!=NULL){
                v->parent=u->parent;
            }
        }

        void inorder(NodeType* x){
            if (x!=NULL){
                inorder(x->left);
                cout << x->key.GetValue() << " ";
                inorder(x->right);
            }
        }
    public:
        BST(){
            root=nullptr;
        }

        NodeType* Search(ItemType k){
            NodeType* x=root;
            while(x!=nullptr && !(x->key==k)){
                if (k<x->key){
                    x=x->left;
                }
                else
                {x=x->right;}
            }
            return x;
        }

        void Insert(ItemType k)
        {
            NodeType* z= new NodeType(k);
            NodeType* x=root;
            NodeType* y= nullptr;
            while (x != nullptr) {
                y = x;
                if (z->key < x->key){
                    x = x->left;
                }
                else{
                    x = x->right;
                }
            }

            z->parent = y;
            if (y == nullptr)
                {root = z;}
            else if (z->key < y->key)
                {y->left = z;}
            else
                {y->right = z;}
        }
        
        void Delete(ItemType k){
            NodeType* z = Search(k); // Find the node to delete
            if (z == nullptr)
                {return;} // Key not found

            //case1: node has no left child
            if (z->left == nullptr) {
                transplant(z, z->right);
            }
            //case2: node has no right child
            else if (z->right == nullptr) {
                transplant(z, z->left);
            }
            //case3: node has two child
            else {
                //find the minimum in z->right subtree
                NodeType* y = z->right;
                while (y->left != nullptr)
                    y = y->left;
                //if successor 
                if (y->parent != z) {
                    transplant(y, y->right);
                    y->right = z->right;
                    if (y->right != nullptr){
                        y->right->parent = y;
                    }
                }
                transplant(z, y);
                y->left = z->left;
                if (y->left != nullptr)
                    y->left->parent = y;
            }
        delete z;
            }

        void Display(){
            inorder(root);
            cout<<endl;
        }

};

int main(){
    BST bst;
    bst.Insert(ItemType(13));
    bst.Insert(ItemType(13));
    bst.Insert(ItemType(7));
    bst.Insert(ItemType(20));
    bst.Insert(ItemType(9));
    bst.Insert(ItemType(5));

    cout << "Tree (inorder): ";
    bst.Display();

    bst.Delete(ItemType(7));
    cout << "After deleting 7: ";
    bst.Display();

    return 0;
};
