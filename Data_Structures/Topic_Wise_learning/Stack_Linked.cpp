#include <iostream>
using namespace std;

//               ItemType Class 
// Represents the type of item stored in the stack.
class ItemType {
public:
    ItemType();                // Constructor: initializes value to 0
    void Print() const;        // Prints the value
    void Initialize(int number); // Assigns a value

private:
    int value;                 // The actual data stored
};

ItemType::ItemType() {
    value = 0;  // Default value
}

void ItemType::Print() const {
    cout << value << " ";
}

void ItemType::Initialize(int number) {
    value = number;
}

//                Exception Classes
// Used for error handling
class FullStack {};   // (not really needed in linked stack, no fixed size)
class EmptyStack {};  // Thrown when stack is empty

//                Node Structure 
// Represents one element (node) in the linked stack
struct Node {
    ItemType data;   // Data (same ItemType as before)
    Node* next;      // Pointer to next node
};

//                StackType Class
// Implements a stack using a linked list
class StackType {
public:
    StackType();                 // Constructor: creates empty stack
    ~StackType();                // Destructor: free all nodes
    bool IsEmpty() const;        // Check if stack is empty
    bool IsFull() const;         // Always false (no fixed size, unless memory ends)
    void Push(ItemType item);    // Add an item (push) on top of stack
    void Pop();                  // Remove the top item (pop)
    ItemType Top() const;        // Get the top item (without removing it)

private:
    Node* topPtr;                // Pointer to the top node
};

// Constructor: stack starts empty
StackType::StackType() {
    topPtr = nullptr;
}

// Destructor: delete all nodes to free memory
StackType::~StackType() {
    while (!IsEmpty()) {
        Pop();
    }
}

// Check if stack is empty
bool StackType::IsEmpty() const {
    return (topPtr == nullptr);
}

// Linked list version is never "full" (unless memory runs out)
bool StackType::IsFull() const {
    return false;
}

// Push: create a new node and add it on top
void StackType::Push(ItemType newItem) {
    Node* newNode = new Node;   // allocate memory for new node
    newNode->data = newItem;    // set data
    newNode->next = topPtr;     // new node points to old top
    topPtr = newNode;           // update top to new node
}

// Pop: remove the top node
void StackType::Pop() {
    if (IsEmpty())
        throw EmptyStack();     // error if empty

    Node* temp = topPtr;        // save current top
    topPtr = topPtr->next;      // move top to next node
    delete temp;                // delete old top
}

// Top: return the data of top node
ItemType StackType::Top() const {
    if (IsEmpty())
        throw EmptyStack();
    return topPtr->data;
}

//               Main Function 
int main() {
    StackType stack;  // Create a linked stack

    try {
        // Create three items
        ItemType item1, item2, item3;
        item1.Initialize(10);
        item2.Initialize(20);
        item3.Initialize(30);

        // Push items into stack
        cout << "Pushing items onto stack\n";
        stack.Push(item1);
        stack.Push(item2);
        stack.Push(item3);

        // Display top element
        cout << "Top element: ";
        stack.Top().Print();
        cout << endl;

        // Pop an element
        cout << "Popping items\n";
        stack.Pop();
        cout << "Now top element: ";
        stack.Top().Print();
        cout << endl;

        // Pop remaining items
        stack.Pop();
        stack.Pop();

        // Try popping from empty stack (will throw exception)
        cout << "Trying to pop from empty stack\n";
        stack.Pop();
    }
    catch (FullStack) {
        cerr << "Error: Stack is full!\n"; // Not really used in linked stack
    }
    catch (EmptyStack) {
        cerr << "Error: Stack is empty!\n";
    }

    return 0;
}
