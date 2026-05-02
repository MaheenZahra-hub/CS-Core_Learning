#ifndef SORTEDLISTFILE_H
#define SORTEDLISTFILE_H

#include <iostream>
#include "ItemTypeFile.h"

using namespace std;

const int MAX_CONTACTS = 100;

/**
 * @class SortedType
 * @brief Manages a collection of contacts in a sorted array[cite: 3].
 */
class SortedType {
private:
    ItemTypeFile contacts[MAX_CONTACTS];
    int length;

public:
    SortedType() { length = 0; }

    bool isFull() const { return length == MAX_CONTACTS; }
    bool isEmpty() const { return length == 0; }
    int getLength() const { return length; }

    /**
     * @brief Inserts contact while maintaining alphabetical order[cite: 3].
     */
    void AddContact(const ItemTypeFile& newContact) {
        if (isFull()) {
            cout << "Error: List is full.\n";
            return;
        }

        int position = 0;
        // Compare using uppercase names for consistency
        while (position < length && contacts[position].getName() < newContact.getName()) {
            position++;
        }

        // Shift elements to the right[cite: 3]
        for (int i = length - 1; i >= position; i--) {
            contacts[i + 1] = contacts[i];
        }

        contacts[position] = newContact;
        length++;
        cout << "Contact saved successfully.\n";
    }

    /**
     * @brief Finds the first occurrence of a name using Linear Search[cite: 3].
     * @return Index of contact or -1 if not found.
     */
    int SearchContact(string searchName) const {
        // Standardize search term to match stored data
        for (int i = 0; i < searchName.length(); i++) 
            searchName[i] = toupper(searchName[i]);

        for (int pos = 0; pos < length; pos++) {
            if (contacts[pos].getName() == searchName) {
                return pos; // Return first match found[cite: 3]
            }
        }
        return -1;
    }

    /**
     * @brief Removes a contact and fills the gap by shifting left[cite: 3].
     */
    void DeleteContact(string nameToDelete) {
        int position = SearchContact(nameToDelete);

        if (position == -1) {
            cout << "Error: Contact '" << nameToDelete << "' not found.\n";
            return;
        }

        for (int i = position; i < length - 1; i++) {
            contacts[i] = contacts[i + 1];
        }

        length--;
        cout << "Contact deleted successfully.\n";
    }

    void DisplayContacts() const {
        if (isEmpty()) {
            cout << "The contact list is currently empty.\n";
            return;
        }
        for (int i = 0; i < length; i++) {
            contacts[i].displayContact();
        }
    }

    void DisplayOneContact(int index) const {
        if (index >= 0 && index < length)
            contacts[index].displayContact();
    }

    ItemTypeFile getContactAt(int index) const {
        if (index >= 0 && index < length) return contacts[index];
        return ItemTypeFile();
    }
};

#endif