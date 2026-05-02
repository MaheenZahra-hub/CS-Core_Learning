#include <iostream>
#include <string>
#include "ItemTypeFile.h"
#include "SortedListFile.h"

using namespace std;

/**
 * @brief Entry point: Handles the user interface and menu loop[cite: 1].
 */
int main() {
    SortedType contactList;
    int choice;

    while (true) {
        cout << "\n===== CONTACT MANAGER MENU =====\n";
        cout << "1. Add New Contact\n";
        cout << "2. Search Contact\n";
        cout << "3. Delete Contact\n";
        cout << "4. Display All\n";
        cout << "5. Exit\n";
        cout << "Selection: ";

        // Robust Input Check[cite: 1]
        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number (1-5).\n";
            cin.clear();            // Reset fail flag
            cin.ignore(1000, '\n'); // Clear buffer
            continue;
        }
        cin.ignore(); // Clear newline for getline()

        if (choice == 1) {
            ItemTypeFile newContact;
            newContact.InputContact();
            contactList.AddContact(newContact);

        } else if (choice == 2) {
            string name;
            cout << "Enter name to search: ";
            getline(cin, name);
            
            int idx = contactList.SearchContact(name);
            if (idx != -1) {
                cout << "Match found:\n";
                contactList.DisplayOneContact(idx);
            } else {
                cout << "No contact found with that name.\n";
            }

        } else if (choice == 3) {
            string name;
            cout << "Enter name to delete: ";
            getline(cin, name);
            contactList.DeleteContact(name);

        } else if (choice == 4) {
            contactList.DisplayContacts();

        } else if (choice == 5) {
            cout << "Closing system. Goodbye!\n";
            break;

        } else {
            cout << "Choice out of range. Try again.\n";
        }
    }

    return 0;
}