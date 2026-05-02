#include <iostream>
#include "itemtype.h"
using namespace std;

class CircularQueue {
private:
    ItemType arr[MAX_ITEMS];
    ItemType item;
    int front;
    int rear;

public:
    // Constructor
    CircularQueue() {
        front = -1;
        rear = -1;
    }
    void makeEmpty(){
        front = MAX_ITEMS-1;
        rear = MAX_ITEMS-1;
    }

    // Check if queue is empty
    bool IsEmpty() {
        return front == rear;
    }

    // Check if queue is full
    bool IsFull() {
        return (front == (rear + 1) % MAX_ITEMS);
    }

    // Enqueue operation
    void Enqueue(ItemType item) {
        if (IsFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        if (IsEmpty())
         {
            front = 0; // first element
         }
        rear = (rear + 1) % MAX_ITEMS;
        arr[rear] = item;
    }

    // Dequeue operation
    ItemType Dequeue() {
        if (IsEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        ItemType item = arr[front];
        if (front == rear) { // last element removed
            front = rear = -1;
        } else {
            front = (front + 1) % MAX_ITEMS;
        }
        return item;
    }

    // Display queue elements
    void Display() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (i!=rear) {
            cout << arr[i].GetKey() << " ";
           // if (i == rear) break;
            i = (i + 1) % MAX_ITEMS;
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q;

    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    q.Enqueue(4);

    q.Display(); // 1 2 3 4

    cout << "Dequeued: "<< q.Dequeue().GetKey() << endl; // 1
    cout << "Dequeued: " << q.Dequeue().GetKey() << endl; // 2

    q.Display(); // 3, 4

    q.Enqueue(5);
    q.Enqueue(6); // wraps around

    q.Display(); // 3 4 5 6
    q.makeEmpty();
    q.Display();
    return 0;
}
