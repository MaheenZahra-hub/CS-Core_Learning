#include <iostream>
using namespace std;

class ItemType 
{
private:
    int value;
public:
    void Initialize(int num) 
	{
	 value=num; 
	}
	
    int GetValue() const 
	{
	 return value; 
	}

    bool operator<(ItemType other) const 
	{
	 return value < other.value;
    }
    
    bool operator>(ItemType other) const 
	{
	 return value > other.value; 
	}
	
    bool operator==(ItemType other) const 
	{
	 return value == other.value; 
	}
};


struct NodeType 
{
    ItemType info;
    NodeType* left;
    NodeType* right;
    NodeType* parent;
};


void Insert(NodeType*& x, ItemType item, NodeType* parent = NULL)
{
    if (x == NULL)
    {
        x = new NodeType;
        x->info = item;
        x->left = NULL;
        x->right = NULL;
        x->parent = parent;
    }
    else if (item < x->info)
    {
	    Insert(x->left, item, x);
	}
    else if (item > x->info)
    {
        Insert(x->right, item, x);
    }
    
}


void InOrder(NodeType* x)
{
    if (x != NULL)
    {
        InOrder(x->left);
        cout << x->info.GetValue() << " ";
        InOrder(x->right);
    }
}


NodeType* FindMin(NodeType* x)
{
    if (x == NULL)
	{
	 return NULL;
    }
    
    while (x->left != NULL)
    {
        x= x->left;
    }
    
    return x;
}


NodeType* FindMax(NodeType* x)
{
    if (x == NULL)
	{
	  return NULL;
    }
    
    while (x->right != NULL)
    {
        x=x->right;
    }
    
    return x;
}


NodeType* Search(NodeType* x, ItemType item)
{
    if (x == NULL || x->info == item)
    {
        return x;
    }
    
    else if (item < x->info)
    {
        return Search(x->left, item);
    }
    else
    {
        return Search(x->right, item);
    }
}


NodeType* Successor(NodeType* node)
{
    if (node == NULL) 
    
	{
	  return NULL;
    }

    
    if (node->right != NULL)
    {
        return FindMin(node->right);
    }

    NodeType* p = node->parent;
    
    while (p != NULL && node == p->right)
    {
        node = p;
        p = p->parent;
    }
    return p;
}


NodeType* Predecessor(NodeType* node)
{
    if (node == NULL)
	{
	 return NULL;
    }

    
    if (node->left != NULL)
    {
        return FindMax(node->left);
    }

    
    NodeType* p = node->parent;
    
    while (p != NULL && node == p->left)
    {
        node = p;
        p = p->parent;
    }
    return p;
}


int main()
{
    NodeType* root = NULL;
    ItemType item;

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
    {
        item.Initialize(values[i]);
        Insert(root, item);
    }

    cout << "Inorder Traversal: ";
    InOrder(root);
    cout << endl;

    NodeType* minNode = FindMin(root);
    NodeType* maxNode = FindMax(root);

    cout << "Minimum: " << minNode->info.GetValue() << endl;
    cout << "Maximum: " << maxNode->info.GetValue() << endl;

    item.Initialize(60);
    NodeType* node = Search(root, item);
    if (node != NULL)
    {
      NodeType* succ = Successor(node);
      NodeType* pred = Predecessor(node);

      cout << "Node: " << node->info.GetValue() << endl;

       if (succ != NULL)
         cout << "Successor: " << succ->info.GetValue() << endl;
       else
         cout << "Successor: None" << endl;

       if (pred != NULL)
         cout << "Predecessor: " << pred->info.GetValue() << endl;
       else
         cout << "Predecessor: None" << endl;
    }
    else
    {
       cout << "Node not found." << endl;
    }
    
    return 0;
}
