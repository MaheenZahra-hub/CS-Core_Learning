#include <iostream>
using namespace std;

// Function to find factorial using recursion
// Logic: n! = n * (n-1)!
int factorial(int n) {
    if (n <= 1) return 1; // Base case
    return n * factorial(n - 1); // Recursive call
}

int main() {
    int num = 5;
    cout << "Factorial of " << num << " is: " << factorial(num) << endl;
    return 0;
}