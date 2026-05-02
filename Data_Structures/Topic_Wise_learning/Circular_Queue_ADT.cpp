#include <iostream>
using namespace std;

const int MAX_ITEMS = 5; // Total size of the array

// --- ItemType Definition ---
class ItemType {
private:
    int value;
public:
    ItemType() { value = 0; }
    ItemType(int v) { value = v; }
    int GetVal() const { return value; }
    void SetVal(int v) { value = v; }
};

// --- CircularQueue Class ---
class CircularQueue {
private:
    ItemType arr[MAX_ITEMS];
    int front; // Points to the space BEFORE the first element
    int rear;  // Points to the last element added

public:
    CircularQueue() {
        front = MAX_ITEMS - 1;
        rear = MAX_ITEMS - 1;
    }

    void makeEmpty() {
        front = MAX_ITEMS - 1;
        rear = MAX_ITEMS - 1;
    }

    bool IsEmpty() {
        return (front == rear);
    }

    bool IsFull() {
        // Full if the next spot after rear is front
        return (front == (rear + 1) % MAX_ITEMS);
    }

    void Enqueue(ItemType newItem) {
        if (IsFull()) {
            cout << "Queue Overflow: Cannot add " << newItem.GetVal() << endl;
            return;
        }
        rear = (rear + 1) % MAX_ITEMS;
        arr[rear] = newItem;
    }

    ItemType Dequeue() {
        if (IsEmpty()) {
            cout << "Queue Underflow\n";
            return ItemType(-1); 
        }
        front = (front + 1) % MAX_ITEMS;
        return arr[front];
    }

    void Display() {
        if (IsEmpty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        cout << "Queue elements: ";
        int i = (front + 1) % MAX_ITEMS;
        while (true) {
            cout << arr[i].GetVal() << " ";
            if (i == rear) break;
            i = (i + 1) % MAX_ITEMS;
        }
        cout << endl;
    }
};

// --- Main Testing Logic ---
int main() {
    CircularQueue q;

    cout << "--- Testing Enqueue ---" << endl;
    q.Enqueue(ItemType(10));
    q.Enqueue(ItemType(20));
    q.Enqueue(ItemType(30));
    q.Enqueue(ItemType(40));
    
    // This will trigger Overflow because we leave one slot empty to detect "Full"
    q.Enqueue(ItemType(50)); 

    q.Display(); 

    cout << "\n--- Testing Dequeue ---" << endl;
    cout << "Dequeued: " << q.Dequeue().GetVal() << endl; // 10
    cout << "Dequeued: " << q.Dequeue().GetVal() << endl; // 20

    q.Display(); // Should show 30 40

    cout << "\n--- Testing Wrap Around ---" << endl;
    q.Enqueue(ItemType(60));
    q.Enqueue(ItemType(70));

    q.Display(); // Should show 30 40 60 70
    
    cout << "\n--- Clearing Queue ---" << endl;
    q.makeEmpty();
    q.Display();

    return 0;
}