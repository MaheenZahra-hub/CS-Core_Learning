#include <iostream>
using namespace std;

// Passing addresses to swap actual values in memory
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    swap(&x, &y); // Sending the memory addresses
    cout << "x: " << x << ", y: " << y << endl; // Values are swapped
    return 0;
}