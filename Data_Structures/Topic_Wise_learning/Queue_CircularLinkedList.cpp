#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

bool isEmpty(Node* front) { return front == NULL; }

void enqueue(Node*& front, Node*& rear, int value) {
    Node* newNode = new Node;
    newNode->data = value;
    
    if(front == NULL) {
        front = rear = newNode;
        newNode->next = front;
        return;
    }

    rear->next = newNode;
    rear = newNode;
    rear->next = front;
}

int dequeue(Node*& front, Node*& rear) {
    if(front == NULL) { cout << "Queue Underflow\n"; return -1; }
    int value = front->data;
    
    if(front == rear) { // only one node
        delete front;
        front = rear = NULL;
        return value;
    }

    Node* temp = front;
    front = front->next;
    rear->next = front;
    delete temp;
    return value;
}

int peek(Node* front) {
    if(front == NULL) { cout << "Queue is empty\n"; return -1; }
    return front->data;
}

void display(Node* front, Node* rear) {
    if(front == NULL) { cout << "Queue is empty\n"; return; }
    Node* temp = front;
    do {
        cout << temp->data << " -> ";
        temp = temp->next;
    } while(temp != front);
    cout << "(back to front)\n";
}

int main() {
    Node* front = NULL;
    Node* rear = NULL;

    enqueue(front, rear, 10);
    enqueue(front, rear, 20);
    enqueue(front, rear, 30);
    display(front, rear); // 10 -> 20 -> 30 -> (back to front)

    cout << "Dequeue: " << dequeue(front, rear) << endl; // 10
    cout << "Front: " << peek(front) << endl;           // 20
    display(front, rear); // 20 -> 30 -> (back to front)
}
