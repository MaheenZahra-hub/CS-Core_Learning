#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class CircularLinkedList {
    Node* head;
public:
    CircularLinkedList() { head = NULL; }

    void insertAtEnd(int x) {
        Node* temp = new Node();
        temp->data = x;
        if (!head) {
            head = temp;
            temp->next = head;
        } else {
            Node* p = head;
            while (p->next != head) p = p->next;
            p->next = temp;
            temp->next = head;
        }
    }

    void display() {
        if (!head) { cout << "List is empty\n"; return; }
        Node* p = head;
        do {
            cout << p->data << " ";
            p = p->next;
        } while (p != head);
        cout << endl;
    }

    void deleteFromBeginning() {
        if (!head) return;
        if (head->next == head) { delete head; head = NULL; return; }
        Node* last = head;
        while (last->next != head) last = last->next;
        Node* temp = head;
        head = head->next;
        last->next = head;
        delete temp;
    }
};

int main() {
    CircularLinkedList cll;
    cll.insertAtEnd(10);
    cll.insertAtEnd(20);
    cll.insertAtEnd(30);
    cll.display(); // 10 20 30
    cll.deleteFromBeginning();
    cll.display(); // 20 30
}
