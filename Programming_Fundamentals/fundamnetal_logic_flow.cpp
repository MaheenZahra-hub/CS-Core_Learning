#include <iostream>
using namespace std;

// Function to demonstrate Modular Programming
bool isPrime(int n) {
    if (n <= 1) return false; // Base logic
    for (int i = 2; i * i <= n; i++) { // Optimized loop 
        if (n % i == 0) return false; // Modulus operator 
    }
    return true;
}

int main() {
    int num;
    cout << "Enter a number to check if it is Prime: ";
    cin >> num;

    if (isPrime(num)) {
        cout << num << " is a prime number." << endl;
    } else {
        cout << num << " is not a prime number." << endl;
    }
    return 0;
}