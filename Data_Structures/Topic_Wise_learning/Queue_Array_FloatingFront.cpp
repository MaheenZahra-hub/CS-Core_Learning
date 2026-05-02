#include <iostream>
using namespace std;

#define MAX 100  // max size of queue

class Queue {
private:
    float arr[MAX];
    int front, rear;

public:
    // Constructor
    Queue() {
        front = -1;
        rear = -1;
    }

    // Check if queue is empty
    bool IsEmpty() {
        return (front == -1 || front > rear);
    }

    // Check if queue is full
    bool IsFull() {
        return (rear == MAX - 1);
    }

    // Enqueue operation
    void Enqueue(float item) {
        if (IsFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        if (front == -1) front = 0;  // first element
        arr[++rear] = item;
    }

    // Dequeue operation
    float Dequeue() {
        if (IsEmpty()) {
            cout << "Queue Underflow\n";
            return -1; // or throw exception
        }
        float item = arr[front++];
        // Optional: reset front/rear if queue becomes empty
        if (front > rear) front = rear = -1;
        return item;
    }

    // Peek front element
    float Front() {
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
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main() {
    Queue q;

    q.Enqueue(1.1);
    q.Enqueue(2.2);
    q.Enqueue(3.3);

    q.Display(); // Output: 1.1 2.2 3.3

    cout << "Dequeued: " << q.Dequeue() << endl; // 1.1
    cout << "Front: " << q.Front() << endl;      // 2.2

    q.Display(); // Output: 2.2 3.3

    return 0;
}

