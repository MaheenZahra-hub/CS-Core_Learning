#include <iostream>
using namespace std;

// Node structure
struct Node {
    float data;
    Node* next;
};

// Queue ADT
class Queue {
private:
    Node* front;  // points to first element
    Node* rear;   // points to last element

public:
    // Constructor
    Queue() {
        front = rear = NULL; // empty queue
    }

    // Check if queue is empty
    bool IsEmpty() {
        return front == NULL;
    }

    // Enqueue: add element at rear
    void Enqueue(float item) {
        Node* newNode = new Node();
        newNode->data = item;
        newNode->next = NULL;

        if (IsEmpty()) {
            front = rear = newNode; // first element
        } else {
            rear->next = newNode; // link new node at end
            rear = newNode;       // update rear
        }
    }

    // Dequeue: remove element from front
    float Dequeue() {
        if (IsEmpty()) {
            cout << "Queue Underflow\n";
            return -1; // or throw exception
        }

        Node* temp = front;      // node to remove
        float item = temp->data; // save data
        front = front->next;     // move front forward

        if (front == NULL) rear = NULL; // queue became empty

        delete temp;             // free memory
        return item;
    }

    // Peek front element
    float FrontItem() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return front->data;
    }

    // Display queue
    void Display() {
        if (IsEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        Node* temp = front;
        cout << "Queue elements: ";
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Queue q;

    q.Enqueue(1.1);
    q.Enqueue(2.2);
    q.Enqueue(3.3);

    q.Display(); // 1.1 2.2 3.3

    cout << "Dequeued: " << q.Dequeue() << endl; // 1.1
    cout << "Front: " << q.FrontItem() << endl;  // 2.2

    q.Display(); // 2.2 3.3

    return 0;
}
