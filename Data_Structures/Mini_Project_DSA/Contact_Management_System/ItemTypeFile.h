#ifndef ITEMTYPEFILE_H
#define ITEMTYPEFILE_H

#include <iostream>
#include <string>
#include <algorithm> // For transform (case standardization)

using namespace std;

/**
 * @class ItemTypeFile
 * @brief Represents a single contact entity with validation and comparison capabilities.
 */
class ItemTypeFile {
private:
    string name;
    string phone;
    string address;

    /**
     * @brief Internal helper to convert string to uppercase for consistent sorting/searching.
     */
    string toUpper(string s) const {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }

public:
    // Default Constructor
    ItemTypeFile() {
        name = "";
        phone = "";
        address = "";
    }

    // Setters with validation[cite: 2]
    void setName(string n) {
        if (isValidName(n)) name = toUpper(n); 
    }
    
    void setPhone(string p) {
        if (isValidPhone(p)) phone = p;
    }

    void setAddress(string a) {
        if (isValidAddress(a)) address = a;
    }

    // Getters[cite: 2]
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getAddress() const { return address; }

    // Validation Logic[cite: 2]
    bool isValidName(string n) const {
        if (n.empty()) return false;
        for (char c : n) {
            if (!isalpha(c) && c != ' ') return false;
        }
        return true;
    }

    bool isValidPhone(string p) const {
        if (p.length() != 11) return false;
        for (char c : p) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    bool isValidAddress(string a) const {
        return !a.empty();
    }

    /**
     * @brief Interactive input for contact details with built-in retry logic[cite: 2].
     */
    void InputContact() {
        string temp;
        cout << "Enter Name (alphabets only): ";
        getline(cin, temp);
        while (!isValidName(temp)) {
            cout << "Invalid name. Use alphabets only: ";
            getline(cin, temp);
        }
        name = toUpper(temp);

        cout << "Enter Phone Number (11 Digits): ";
        getline(cin, phone);
        while (!isValidPhone(phone)) {
            cout << "Invalid. Enter exactly 11 digits: ";
            getline(cin, phone);
        }

        cout << "Enter Address: ";
        getline(cin, address);
        while (!isValidAddress(address)) {
            cout << "Address cannot be empty. Enter again: ";
            getline(cin, address);
        }
    }

    void displayContact() const {
        cout << "------------------------" << endl;
        cout << "Name:    " << name << endl;
        cout << "Phone:   " << phone << endl;
        cout << "Address: " << address << endl;
        cout << "------------------------" << endl;
    }
};

#endif