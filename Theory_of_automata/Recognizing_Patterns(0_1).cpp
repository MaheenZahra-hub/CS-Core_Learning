#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Function for recognizing pattern of "10010"
void checkSubstring(string input) {
    int state = 0;

    for (char bit : input) {
        // Validation for input
        if (bit != '0' && bit != '1') {
            cout << "Invalid Input! Only 0s and 1s are allowed." << endl;
            system("pause");
            exit(0); // Stop the program
        }

        switch (state) {
            case 0:
                if (bit == '1') state = 1;
                else state = 0;
                break;

            case 1:
                if (bit == '0') state = 2;
                else state = 1; // Staying at '1' if we get "11"
                break;

            case 2:
                if (bit == '0') state = 3;
                else state = 1; // Back to state 1 if we get "101"
                break;

            case 3:
                if (bit == '1') state = 4;
                else state = 0; // Back to start if we get "1000"
                break;

            case 4:
                if (bit == '0') state = 5;
                else state = 1; // Back to state 1 if we get "10011"
                break;

            case 5:
                // Once "10010" is found, we stay in the accept state
                state = 5; 
                break;
        }
    }

    if (state == 5) {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }
}

int main() {
    string input;
    cout << "Enter a binary string: ";
    cin >> input;

    // Calling the function
    checkSubstring(input);
    
    system("pause");
    return 0;
}