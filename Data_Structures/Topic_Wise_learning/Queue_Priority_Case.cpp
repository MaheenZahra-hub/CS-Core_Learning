#include <iostream>
using namespace std;

const int MAX_SIZE = 10;

class ItemType {
private:
    char key; 
    int prior;

public:
    ItemType()
     { 
        key = 0; 
        prior=0;
    }
    ItemType(char k, int p)
     { 
        key = k; 
        prior = p;
    }

    void SetKey(char k)
     { key = k; } 
    void SetPrior(int p)
     { prior = p;}
    char GetKey() const 
    { return key; }
    int GetPrior() const 
    { return prior;}
};

// Priority Queue Class
class PriorityQueue {
private:
    ItemType arr[MAX_SIZE];  // array to store queue elements
    int front;               // index of front element
    int rear;                // index of rear element

public:
    // Constructor: initializes the queue as empty
    PriorityQueue() {
        front = -1;
        rear = -1;
    }

    // Check if the queue is empty
    bool IsEmpty() {
        return (front == -1);
    }

    // Check if the queue is full
    bool IsFull() {
        return ((rear + 1) % MAX_SIZE == front);
    }

    // Insert element based on priority
    void Enqueue(ItemType item) {
        if (IsFull()) {
            cout << "Queue is full! Cannot add more elements.\n";
            return;
        }
        int priority = item.GetPrior();
        // If the queue is empty
        if (IsEmpty()) {
            front = rear = 0;
            arr[rear] = item;
            return;
        }

        // Priority 0 → Add at rear
        if (priority == 0) {
            rear = (rear + 1) % MAX_SIZE;
            arr[rear] = item;
        }
        // Priority 1 → Add at front
        else if (priority == 1) {
            front = (front - 1 + MAX_SIZE) % MAX_SIZE;
            arr[front] = item;
        }
        // If user enters invalid priority
        else {
            cout << "Invalid priority!\n";
        }
    }

      // Dequeue operation
ItemType Dequeue() {
    if (IsEmpty()) {
        cout << "Queue Underflow\n";
        return ItemType(); // return empty object instead of -1
    }

    ItemType item = arr[front];

    if (front == rear)  // only one element left
        front = rear = -1;
    else
        front = (front + 1) % MAX_SIZE;

    return item;
}

    // Display all elements of the queue
    void Display() {
        if (IsEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue elements: "<<endl;
        int i = front;
        while (true) {
            cout << arr[i].GetKey() << " ";
            cout << arr[i].GetPrior()<<endl;
            if (i == rear) break; // stop when last element reached
            i = (i + 1) % MAX_SIZE;
        }
        cout << endl;
    }

    // Make the queue empty
    void MakeEmpty() {
        front = rear = -1;
        cout << "Queue cleared successfully!\n";
    }
};

int main() {
    PriorityQueue q;

    q.Enqueue(ItemType('b', 0)); // goes to rear
    q.Enqueue(ItemType('a', 1)); // goes to front
    q.Enqueue(ItemType('c', 0)); // goes to rear
    q.Enqueue(ItemType('d', 1)); // goes to front

    q.Display();

    cout << "Dequeued: " << q.Dequeue().GetKey() << endl;
    cout << "Dequeued: " << q.Dequeue().GetKey() << endl;

    q.Display();

    q.Enqueue(ItemType('e', 0));
    q.Enqueue(ItemType('f', 1));

    q.Display();

    q.MakeEmpty();
    q.Display();

    return 0;
}
