#include <iostream>
using namespace std;

#define MAX 5  // queue size
class CircularQueueRS {  // RS = Reserved Slot
private:
    float arr[MAX];
    int front, rear;

public:
    CircularQueueRS() {
        front = 0;
        rear = 0;
    }

    // Check if empty
    bool IsEmpty() {
        return front == rear;
    }

    // Check if full
    bool IsFull() {
        return (rear + 1) % MAX == front;
    }

    // Enqueue
    void Enqueue(float item) {
        if (IsFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        arr[rear] = item;
        rear = (rear + 1) % MAX;
    }

    // Dequeue
    float Dequeue() {
        if (IsEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        float item = arr[front];
        front = (front + 1) % MAX;
        return item;
    }

    // Peek front
    float FrontItem() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return arr[front];
    }

    // Display
    void Display() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (i != rear) {
            cout << arr[i] << " ";
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    CircularQueueRS q;

    q.Enqueue(1.1);
    q.Enqueue(2.2);
    q.Enqueue(3.3);
    q.Enqueue(4.4);  // MAX-1 elements only

    q.Display(); // 1.1 2.2 3.3 4.4

    cout << "Dequeued: " << q.Dequeue() << endl; // 1.1
    cout << "Dequeued: " << q.Dequeue() << endl; // 2.2

    q.Display(); // 3.3 4.4

    q.Enqueue(5.5);
    q.Enqueue(6.6); // Wraps around

    q.Display(); // 3.3 4.4 5.5 6.6

    q.Enqueue(7.7); // Overflow

    return 0;
}
