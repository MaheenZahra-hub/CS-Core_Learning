#include <iostream>
using namespace std;

#define MAX 5  // small size for easy testing

class CircularQueue {
private:
    float arr[MAX];
    int front, rear;

public:
    // Constructor
    CircularQueue() {
        front = -1;
        rear = -1;
    }

    // Check if queue is empty
    bool IsEmpty() {
        return front == -1;
    }

    // Check if queue is full
    bool IsFull() {
        return (front == (rear + 1) % MAX);
    }

    // Enqueue operation
    void Enqueue(float item) {
        if (IsFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        if (IsEmpty()) front = 0; // first element
        rear = (rear + 1) % MAX;
        arr[rear] = item;
    }

    // Dequeue operation
    float Dequeue() {
        if (IsEmpty()) {
            cout << "Queue Underflow\n";
            return -1;
        }
        float item = arr[front];
        if (front == rear) { // last element removed
            front = rear = -1;
        } else {
            front = (front + 1) % MAX;
        }
        return item;
    }

    // Peek front element
    float FrontItem() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return arr[front];
    }

    // Display queue elements
    void Display() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    CircularQueue q;

    q.Enqueue(1.1);
    q.Enqueue(2.2);
    q.Enqueue(3.3);
    q.Enqueue(4.4);

    q.Display(); // 1.1 2.2 3.3 4.4

    cout << "Dequeued: " << q.Dequeue() << endl; // 1.1
    cout << "Dequeued: " << q.Dequeue() << endl; // 2.2

    q.Display(); // 3.3 4.4

    q.Enqueue(5.5);
    q.Enqueue(6.6); // wraps around

    q.Display(); // 3.3 4.4 5.5 6.6

    return 0;
}
