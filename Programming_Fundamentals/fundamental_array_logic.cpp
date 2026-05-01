#include <iostream>
using namespace std;

void reverseArray(int arr[], int size) {
    int start = 0, end = size - 1;
    while (start < end) {
        // Swap elements
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

int main() {
    int data[] = {10, 20, 30, 40, 50};
    reverseArray(data, 5);
    // Output the reversed array...
    return 0;
}