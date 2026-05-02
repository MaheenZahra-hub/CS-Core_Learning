#include<iostream>
using namespace std;

class Flight {
private:
    int flightID;
    string destination;
    float departureTime; // in hours (e.g., 14.5 for 2:30 PM)
    float duration; // in hours
    string status; // "Departed", "Landed", "Delayed"
public:
    Flight() {
        flightID = 0;
        destination = "";
        departureTime = 0.0;
        duration = 0.0;
        status = "";
    }
    Flight(int id, string dest, float depTime, float dur, string stat) {
        flightID = id;
        destination = dest;
        departureTime = depTime;
        duration = dur;
        status = stat;
    }
    void SetFlightID(int id) { flightID = id; }
    void SetDestination(string dest) { destination = dest; }
    void SetDepartureTime(float time) { departureTime = time; }
    void SetDuration(float dur) { duration = dur; }
    void SetStatus(string stat) { status = stat; }

    int GetFlightID() const { return flightID; }
    string GetDestination() const { return destination; }
    float GetDepartureTime() const { return departureTime; }
    float GetDuration() const { return duration; }
    string GetStatus() const { return status; }
    // Display flight details
    void Display() const {
        cout << "Flight ID: " << flightID << ", Destination: " << destination 
             << ", Departure Time: " << departureTime << " hours, Duration: " << duration 
             << " hours, Status: " << status << endl;
    }
};

class ItemType {
private:
    Flight flight;
public:
    ItemType() {
        flight = Flight();
    }
    ItemType(Flight f) {
        flight = f;
    }
void SetFlight(Flight f) {
        flight = f;
    }
    Flight GetFlight() const {
        return flight;
    }
    bool operator<(ItemType& other) const {
        return flight.GetFlightID() < other.flight.GetFlightID();
    }
    
    bool operator>(ItemType& other) const {
        return flight.GetFlightID() > other.flight.GetFlightID();
    }
    bool operator==(ItemType& other) const {
        return flight.GetFlightID() == other.flight.GetFlightID();
    }
};

struct NodeType {
    ItemType key;
    NodeType* left;
    NodeType* right;
    NodeType* parent;
    NodeType(ItemType& k) {
        key = k;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class BST {
private:
    NodeType* root;

    void transplant(NodeType* u, NodeType* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }

    void inorder(NodeType* x) {
        if (x != nullptr) {
            inorder(x->left);
            x->key.GetFlight().Display();
            inorder(x->right);
        }
    }

    // Count nodes in the tree
    int countNodes(NodeType* x) {
        if (x == nullptr) return 0;
        return 1 + countNodes(x->left) + countNodes(x->right);
    }

    // Collect flights into an array
    void collectFlights(NodeType* x, Flight* flights, int& index) {
        if (x != nullptr) {
            collectFlights(x->left, flights, index);
            flights[index++] = x->key.GetFlight();
            collectFlights(x->right, flights, index);
        }
    }

    // Sort array by destination (bubble sort)
    void sortByDestination(Flight* flights, int count) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (flights[j].GetDestination() > flights[j + 1].GetDestination()) {
                    Flight temp = flights[j];
                    flights[j] = flights[j + 1];
                    flights[j + 1] = temp;
                }
            }
        }
    }

    // Sort array by status (bubble sort)
    void sortByStatus(Flight* flights, int count) {
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (flights[j].GetStatus() > flights[j + 1].GetStatus()) {
                    Flight temp = flights[j];
                    flights[j] = flights[j + 1];
                    flights[j + 1] = temp;
                }
            }
        }
    }

public:
    BST() {
        root = nullptr;
    }

    NodeType* Search(ItemType k) {
        NodeType* x = root;
        while (x != nullptr && !(x->key == k)) {
            if (k < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    }

    void Insert(ItemType k) {
        NodeType* z = new NodeType(k);
        NodeType* x = root;
        NodeType* y = nullptr;
        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    void Delete(ItemType k) {
        NodeType* z = Search(k);
        if (z == nullptr) {
            return;
        }
        if (z->left == nullptr) {
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            transplant(z, z->left);
        } else {
            NodeType* y = z->right;
            while (y->left != nullptr) {
                y = y->left;
            }
            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr) {
                    y->right->parent = y;
                }
            }

            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr) {
                y->left->parent = y;
            }
        }
        delete z;
    }
    
    void DisplayAll() {
        inorder(root);
        cout << endl;
    }

    // Display flights grouped by destination
    void DisplayGroupedByDestination() {
        int count = countNodes(root);
        if (count == 0) {
            cout << "No flights to display." << endl;
            return;
        }
        Flight* flights = new Flight[count];
        int index = 0;
        collectFlights(root, flights, index);
        sortByDestination(flights, count);
        string currentDest = "";
        for (int i = 0; i < count; i++) {
            if (flights[i].GetDestination() != currentDest) {
                currentDest = flights[i].GetDestination();
                cout << "Destination: " << currentDest << endl;
            }
            flights[i].Display();
        }
        cout << endl;
        delete[] flights;
    }

    // Display flights grouped by status
    void DisplayGroupedByStatus() {
        int count = countNodes(root);
        if (count == 0) {
            cout << "No flights to display." << endl;
            return;
        }
        Flight* flights = new Flight[count];
        int index = 0;
        collectFlights(root, flights, index);
        sortByStatus(flights, count);
        string currentStatus = "";
        for (int i = 0; i < count; i++) {
            if (flights[i].GetStatus() != currentStatus) {
                currentStatus = flights[i].GetStatus();
                cout << "Status: " << currentStatus << endl;
            }
            flights[i].Display();
        }
        cout << endl;
        delete[] flights;
    }

    // Display ETA and punctuality status
    void DisplayETA() {
        int count = countNodes(root);
        if (count == 0) {
            cout << "No flights to display." << endl;
            return;
        }
        Flight* flights = new Flight[count];
        int index = 0;
        collectFlights(root, flights, index);
        for (int i = 0; i < count; i++) {
            float eta = flights[i].GetDepartureTime() + flights[i].GetDuration();
            string punctuality;
            if (flights[i].GetStatus() == "Delayed") {
                punctuality = "Delayed";
            } else {
                punctuality = "On-Time";  // Simplified: On-Time unless Delayed
            }
            cout << "Flight ID: " << flights[i].GetFlightID() << ", ETA: " << eta 
                 << " hours, Punctuality: " << punctuality << endl;
        }
        cout << endl;
        delete[] flights;
    }

    // Surprise Feature: Display flights with duration greater than a specified value
    void DisplayFlightsByDuration(float minDuration) {
        int count = countNodes(root);
        if (count == 0) {
            cout << "No flights to display." << endl;
            return;
        }
        Flight* flights = new Flight[count];
        int index = 0;
        collectFlights(root, flights, index);
        cout << "Flights with duration > " << minDuration << " hours:" << endl;
        for (int i = 0; i < count; i++) {
            if (flights[i].GetDuration() > minDuration) {
                flights[i].Display();
            }
        }
        cout << endl;
        delete[] flights;
    }
};

int main() {
    BST bst;
    int choice;
    do {
        cout << "\nFlight Reservation Directory Menu:" << endl;
        cout << "1. Insert new flight record" << endl;
        cout << "2. Delete a flight record" << endl;
        cout << "3. Search for a flight" << endl;
        cout << "4. Display all flights (sorted by Flight ID)" << endl;
        cout << "5. Display flights grouped by destination" << endl;
        cout << "6. Display flights grouped by status" << endl;
        cout << "7. Display ETA and punctuality status for all flights" << endl;
        cout << "8. Surprise: Display flights with duration > X hours" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string dest, status;
                float depTime, dur;
                cout << "Enter Flight ID: ";
                cin >> id;
                cout << "Enter Destination: ";
                cin >> dest;
                cout << "Enter Departure Time (hours): ";
                cin >> depTime;
                cout << "Enter Duration (hours): ";
                cin >> dur;
                cout << "Enter Status (Departed/Landed/Delayed): ";
                cin >> status;
                Flight f(id, dest, depTime, dur, status);
                ItemType item(f);
                bst.Insert(item);
                cout << "Flight inserted." << endl;
                break;
            }

            case 2: {
                int id;
                cout << "Enter Flight ID to delete: ";
                cin >> id;
                Flight f(id, "", 0, 0, "");
                ItemType item(f);
                bst.Delete(item);
                cout << "Flight deleted if found." << endl;
                break;
            }

            case 3: {
                int id;
                cout << "Enter Flight ID to search: ";
                cin >> id;
                Flight f(id, "", 0, 0, "");
                ItemType item(f);
                NodeType* node = bst.Search(item);
                if (node != nullptr) {
                    cout << "Flight found: ";
                    node->key.GetFlight().Display();
                } else {
                    cout << "Flight not found." << endl;
                }
                break;
            }
            case 4:
                cout << "All flights (sorted by Flight ID):" << endl;
                bst.DisplayAll();
                break;
            case 5:
                bst.DisplayGroupedByDestination();
                break;

            case 6:
                bst.DisplayGroupedByStatus();
                break;
            case 7:
                bst.DisplayETA();
                break;
            case 8: {
                float minDur;
                cout << "Enter minimum duration (hours): ";
                cin >> minDur;
                bst.DisplayFlightsByDuration(minDur);
                break;
            }
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 9);
    return 0;
}
