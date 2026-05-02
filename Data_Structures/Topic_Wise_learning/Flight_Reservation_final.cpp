#include<iostream>
#include<string>
using namespace std;

// Class to store each flight's details
class Flight {
private:
    int flightID;
    string destination;
    float departureTime; // e.g. 14.5 means 2:30 PM
    float duration;      // flight duration in hours
    string status;       // Departed, Landed, or Delayed

public:
    // Default constructor
    Flight() {
        flightID = 0;
        destination = "";
        departureTime = 0.0;
        duration = 0.0;
        status = "";
    }

    // Parameterized constructor
    Flight(int id, string dest, float depTime, float dur, string stat) {
        flightID = id;
        destination = dest;
        departureTime = depTime;
        duration = dur;
        status = stat;
    }

    // Setters
    void SetFlightID(int id){ flightID = id; }
    void SetDestination(string dest) { destination = dest; }
    void SetDepartureTime(float time) { departureTime = time; }
    void SetDuration(float dur) { duration = dur; }
    void SetStatus(string stat) { status = stat; }

    // Getters
    int GetFlightID() const { return flightID; }
    string GetDestination() const { return destination; }
    float GetDepartureTime() const { return departureTime; }
    float GetDuration() const { return duration; }
    string GetStatus() const { return status; }

    // Show flight info
    void Display() const {
        cout << "Flight ID: " << flightID << ", Destination: " << destination 
             << ", Departure Time: " << departureTime << " hours, Duration: " << duration 
             << " hours, Status: " << status << endl;
    }
};

// Wrapper for Flight used as key in BST
class ItemType {
private:
    Flight flight;
public:
    // Default
    ItemType() { flight = Flight(); }

    // Parameterized
    ItemType(Flight f) { flight = f; }

    // Set/Get
    void SetFlight(Flight f) { flight = f; }
    Flight GetFlight() const { return flight; }

    // Compare by Flight ID for BST sorting
    bool operator<(const ItemType& other) const { 
        return flight.GetFlightID() < other.flight.GetFlightID();
    }
    bool operator>(const ItemType& other) const { 
        return flight.GetFlightID() > other.flight.GetFlightID();
    }
    bool operator==(const ItemType& other) const { 
        return flight.GetFlightID() == other.flight.GetFlightID();
    }
};

// Node for BST
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

// BST class handles flight storage and search
class BST {
private:
    NodeType* root;
    const int MAX_FLIGHTS = 100; // Max array size for flight collection

    // Helper: replace one node with another
    void transplant(NodeType* nodeToReplace, NodeType* replacementNode) {
        if (nodeToReplace->parent == nullptr)
            root = replacementNode;
        else if (nodeToReplace == nodeToReplace->parent->left)
            nodeToReplace->parent->left = replacementNode;
        else
            nodeToReplace->parent->right = replacementNode;

        if (replacementNode != nullptr)
            replacementNode->parent = nodeToReplace->parent;
    }

    // Inorder traversal to print sorted flights
    void inorder(NodeType* node) {
        if (node != nullptr) {
            inorder(node->left);
            node->key.GetFlight().Display();
            inorder(node->right);
        }
    }

    // Gather flights into array (for grouping)
    void collectFlights(NodeType* node, Flight flights[], int& count) {
        if (node != nullptr && count < MAX_FLIGHTS) {
            collectFlights(node->left, flights, count);
            flights[count++] = node->key.GetFlight();
            collectFlights(node->right, flights, count);
        }
    }

public:
    // Constructor
    BST() {
         root = nullptr; 
    }

    // Search using ItemType key
    NodeType* Search(ItemType k) const { 
        NodeType* currentNode = root;
        while (currentNode != nullptr && !(currentNode->key == k)) {
            if (k < currentNode->key)
                currentNode = currentNode->left;
            else
                currentNode = currentNode->right;
        }
        return currentNode;
    }

    // Search directly by flight ID
    NodeType* SearchByFlightID(int flightID) const {
        NodeType* current = root;
        while (current != nullptr) {
            int currentID = current->key.GetFlight().GetFlightID();
            if (flightID < currentID)
                current = current->left;
            else if (flightID > currentID)
                current = current->right;
            else
                return current; // found
        }
        return nullptr; // not found
    }

    // Insert new flight node
    void Insert(ItemType k) {
        NodeType* newNode = new NodeType(k);
        NodeType* currentNode = root;
        NodeType* parentNode = nullptr;

        // Find correct spot
        while (currentNode != nullptr) {
            parentNode = currentNode;
            if (newNode->key < currentNode->key)
                currentNode = currentNode->left;
            else
                currentNode = currentNode->right;
        }

        // Link new node
        newNode->parent = parentNode;
        if (parentNode == nullptr)
            root = newNode;
        else if (newNode->key < parentNode->key)
            parentNode->left = newNode;
        else
            parentNode->right = newNode;
    }

    // Delete a flight
    void Delete(ItemType k) {
        NodeType* nodeToDelete = Search(k);
        if (nodeToDelete == nullptr) {
            cout << "Flight not found for deletion." << endl;
            return;
        }

        // Handle 3 deletion cases
        if (nodeToDelete->left == nullptr)
            transplant(nodeToDelete, nodeToDelete->right);
        else if (nodeToDelete->right == nullptr)
            transplant(nodeToDelete, nodeToDelete->left);
        else {
            // Find successor (smallest in right subtree)
            NodeType* successorNode = nodeToDelete->right;
            while (successorNode->left != nullptr)
                successorNode = successorNode->left;

            // Adjust links
            if (successorNode->parent != nodeToDelete) {
                transplant(successorNode, successorNode->right);
                successorNode->right = nodeToDelete->right;
                if (successorNode->right != nullptr)
                    successorNode->right->parent = successorNode;
            }

            transplant(nodeToDelete, successorNode);
            successorNode->left = nodeToDelete->left;
            if (successorNode->left != nullptr)
                successorNode->left->parent = successorNode;
        }
        delete nodeToDelete;
        cout << "Flight deleted if found." << endl;
    }

    // Show all flights (sorted)
    void DisplayAll() {
        if (root == nullptr) {
            cout << "No flights in the system." << endl;
            return;
        }
        inorder(root);
        cout << endl;
    }

    // Show flights grouped by destination
    void DisplayByDestination() {
        Flight flights[MAX_FLIGHTS];
        int count = 0;
        collectFlights(root, flights, count); // Gather all flights from BST into an array

        if (count == 0) {
            cout << "No flights in the system." << endl;
            return; // Stop if there are no flights
        }

        // Sort flights alphabetically by destination
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (flights[j].GetDestination() > flights[j + 1].GetDestination()) {
                    swap(flights[j], flights[j + 1]);
                }
            }
        }

        cout << "Flights grouped by destination:" << endl;
        string currentDestination = "";

        // Print grouped output
        for (int i = 0; i < count; i++) {
            if (flights[i].GetDestination() != currentDestination) {
                currentDestination = flights[i].GetDestination();
                cout << "\nDestination: " << currentDestination << endl;
            }
            flights[i].Display();
        }
        cout << endl;
    }

    // Show flights grouped by status (sorted for clean grouping)
    void DisplayByStatus() {
        Flight flights[MAX_FLIGHTS];
        int count = 0;
        collectFlights(root, flights, count); // Gather all flights from BST into an array

        if (count == 0) {
            cout << "No flights in the system." << endl;
            return; // Stop if there are no flights
        }

        // Sort flights alphabetically by status
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (flights[j].GetStatus() > flights[j + 1].GetStatus()) {
                    swap(flights[j], flights[j + 1]);
                }
            }
        }

        cout << "Flights grouped by status:" << endl;
        string currentStatus = "";

        // Print grouped output
        for (int i = 0; i < count; i++) {
            if (flights[i].GetStatus() != currentStatus) {
                currentStatus = flights[i].GetStatus();
                cout << "\nStatus: " << currentStatus << endl;
            }
            flights[i].Display();
        }
        cout << endl;
    }

    // Calculate and show ETA
    void DisplayETA() {
        Flight flights[MAX_FLIGHTS];
        int count = 0;
        collectFlights(root, flights, count); // Gather all flights from BST into an array

        if (count == 0) {
            cout << "No flights in the system." << endl;
            return; // Stop if there are no flights
        }

        cout << "ETA and Punctuality Status:" << endl;
        for (int i = 0; i < count; i++) {
            // ETA = departure time + duration
            float eta = flights[i].GetDepartureTime() + flights[i].GetDuration();

            // Mark flight as delayed or on-time
            string punctuality = (flights[i].GetStatus() == "Delayed") ? "Delayed" : "On-Time";

            // Display calculated ETA and punctuality
            cout << "Flight ID: " << flights[i].GetFlightID() 
                << ", ETA: " << eta << " hours, Punctuality: " << punctuality << endl;
        }
        cout << endl;
    }

    // Fun suggestion feature based on duration and time
    void DisplayPreFlightRitualSuggestion(int flightID) const {
        NodeType* node = SearchByFlightID(flightID);

        if (node != nullptr) {
            const Flight& flight = node->key.GetFlight();
            float duration = flight.GetDuration();
            float departureTime = flight.GetDepartureTime();

            cout << "\n====== Pre-Flight Ritual Suggestion for Flight " 
                 << to_string(flight.GetFlightID()) << " ======" << endl;

            // Duration-based tips
            if (duration < 1.0)
                cout << "No need to recline your seat—just buckle in and enjoy the quick hop." << endl;
            else if (duration >= 1.0 && duration < 2.0)
                cout << "Quick trip! Double-check you have all your essentials at the gate." << endl;
            else if (duration >= 2.0 && duration < 6.0)
                cout << "Medium flight, you should grab a podcast or e-book." << endl;
            else if (duration >= 6.0 && duration < 10.0)
                cout << "Long one! Stretch, hydrate, and relax." << endl;
            else
                cout << "Ultra-long haul! Pack snacks, socks, and music." << endl;

            // Time-based tips
            if (departureTime >= 0.0 && departureTime < 8.0)
                cout << "Early flight? Coffee helps!" << endl;
            else if (departureTime >= 12.0 && departureTime < 14.0)
                cout << "Midday? Light snack before boarding." << endl;
            else if (departureTime >= 20.0 && departureTime <= 24.0)
                cout << "Late flight? Bring earplugs or a sleep mask." << endl;

            cout << "Safe travels!" << endl;
            cout << "=============================================" << endl;
        } else {
            cout << "Flight ID " << flightID << " not found for ritual suggestion." << endl;
        }
        cout << endl;
    }
};

int main() {
    BST bst;
    int choice;

    do {
        // Display main menu
        cout << "----------------------------------------------" << endl;
        cout << "\nFlight Reservation Directory Menu:" << endl;
        cout << "----------------------------------------------" << endl;
        cout << "1. Add a new flight\n";
        cout << "2. Delete flight\n";
        cout << "3. Search flight by ID\n";
        cout << "4. View all flights\n";
        cout << "5. Filter flights by destination\n";
        cout << "6. Filter flights by status\n";
        cout << "7. Show estimated arrival times\n";
        cout << "8. Get pre-flight ritual suggestions\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // Add new flight
                int id;
                string dest, status;
                float depTime, dur;
                cout << "Enter Flight ID: ";
                cin >> id;
                cout << "Enter Destination: ";
                cin >> dest;
                cout << "Enter Departure Time (hours, e.g., 14.5 for 2:30 PM): ";
                cin >> depTime;
                cout << "Enter Duration (hours): ";
                cin >> dur;
                cout << "Enter Status (use exact case: Departed/Landed/Delayed): ";
                cin >> status;

                Flight f(id, dest, depTime, dur, status);
                ItemType item(f);
                bst.Insert(item);
                cout << "Flight inserted." << endl;
                break;
            }

            case 2: {
                // Delete a flight
                int id;
                cout << "Enter Flight ID to delete: ";
                cin >> id;
                Flight f(id, "", 0, 0, "");
                ItemType item(f);
                bst.Delete(item);
                break;
            }

            case 3: {
                // Search flight
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
                // View all flights
                cout << "All flights (sorted by Flight ID):" << endl;
                bst.DisplayAll();
                break;

            case 5:
                // Group by destination
                bst.DisplayByDestination();
                break;

            case 6:
                // Group by status
                bst.DisplayByStatus();
                break;

            case 7:
                // Show ETA
                bst.DisplayETA();
                break;

            case 8: { 
                // Pre-flight ritual
                int id;
                cout << "Enter Flight ID for ritual suggestion: ";
                cin >> id;
                bst.DisplayPreFlightRitualSuggestion(id);
                break;
            }

            case 9:
                cout << "Exiting" << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 9);

    return 0;
}
