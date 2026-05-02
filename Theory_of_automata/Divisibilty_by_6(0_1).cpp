#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

bool isDivisibleBy6(string binary) {
    if (binary.empty()) return false;

    int state = 0; //remainder starts at 0

    for (char bit : binary) {
        // Validation for input
        if (bit != '0' && bit != '1') {
            cout << "Error: Invalid character detected." << endl;
            system("pause");
            exit(0); // Stop the program
        }

        int digit = bit - '0';

        // Multiplying by 2 shifts the binary number left.
        // Adding the digit adds the new bit.
        state = (state * 2 + digit) % 6;
    }

    // If the final state (remainder) is 0 then number is divisible by 6
    return (state == 0);
}

int main() {
    string input;
    
    cout << " Binary Divisibility by 6 Checker " << endl;
    cout << "Enter a binary string: ";
    cin >> input;

    if (isDivisibleBy6(input)) {
        cout << "Accepted" << endl;
        cout << "The number is divisible by 6." << endl;
    } else {
        cout << "Rejected" << endl;
        cout << "The number is not divisible by 6." << endl;
    }
    system("pause");
    return 0;
}