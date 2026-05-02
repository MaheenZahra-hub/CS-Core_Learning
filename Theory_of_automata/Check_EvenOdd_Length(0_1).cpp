#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Function for checking even & odd length
void checkEvenLength(string input) {
    int state = 0; // We start at State 0 (Even)

    for (char bit : input) {

        // Validation for input
        if (bit != '0' && bit != '1') {
            cout << "Invalid Input! Only 0s and 1s are allowed." << endl;
            system("pause");
            exit(0); // Stop the program
        }

        if (state == 0) {
            state = 1; // If it was even, it's now odd
        } else {
            state = 0; // If it was odd, it's now even
        }
    }

    // After checking all bits, we decide the outcome
    if (state == 0) {
        cout << "Accepted, Length is Even" << endl;
    } else {
        cout << "Rejected, Length is Odd" << endl;
    }
}

int main() {
    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    // Calling the function
    checkEvenLength(input);

    system("pause");

    return 0;
}