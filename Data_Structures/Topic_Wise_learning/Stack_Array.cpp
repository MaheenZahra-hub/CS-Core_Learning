#include <iostream>
using namespace std;

const int MAX_ITEMS = 100;  // Maximum size of the stack (fixed-size array)

//                ItemType Class 
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

//                   Exception Classes
// Empty classes used only to "throw" errors
class FullStack {};   // Thrown when stack is full
class EmptyStack {};  // Thrown when stack is empty

//                StackType Class 
// Implements a stack using an array
class StackType {
public:
    StackType();                 // Constructor: initialize empty stack
    bool IsEmpty() const;        // Check if stack is empty
    bool IsFull() const;         // Check if stack is full
    void Push(ItemType item);    // Add an item (push) on top of stack
    void Pop();                  // Remove the top item (pop)
    ItemType Top() const;        // Get the top item (without removing it)

private:
    int top;                     // Index of the top element
    ItemType items[MAX_ITEMS];   // Array to store stack elements
};

// Constructor: initially stack is empty (top = -1 means no elements)
StackType::StackType() {
    top = -1;
}

bool StackType::IsEmpty() const {
    return (top == -1);
}

bool StackType::IsFull() const {
    return (top == MAX_ITEMS - 1);
}

void StackType::Push(ItemType newItem) {
    if (IsFull())
        throw FullStack();   // Throw exception if stack is full
    top++;
    items[top] = newItem;    // Place new item on top
}

void StackType::Pop() {
    if (IsEmpty())
        throw EmptyStack();  // Throw exception if stack is empty
    top--;  // Just reduce top index, item is logically removed
}

ItemType StackType::Top() const {
    if (IsEmpty())
        throw EmptyStack();  // Throw exception if stack is empty
    return items[top];       // Return the current top element
}

//            Main Function 
int main() {
    StackType stack;  // Create a stack object

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
        cerr << "Error: Stack is full!\n";
    }
    catch (EmptyStack) {
        cerr << "Error: Stack is empty!\n";
    }

    return 0;
}
