/*
 * Description:
 * This program implements the Insertion Sort algorithm and measures
 * its performance on three types of input data:
 *
 * 1. Random input
 * 2. Already sorted input
 * 3. Reverse sorted input
 *
 * The execution time is measured in microseconds using the chrono library.
 * Dynamic memory allocation is used to create arrays of different sizes.
 */
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

/*
 * Purpose:
 * Sorts an array using the Insertion Sort algorithm.
 *
 * Parameters:
 * arr -> Array to be sorted
 * n   -> Number of elements
 *
 * How it works:
 * The algorithm builds the sorted portion of the array one element at a time.
 * For each element, it compares it with elements before it and shifts larger
 * elements one position to the right until the correct position is found.
 *
 */
void insertionSort(int arr[], int n) {
    for (int j = 1; j < n; j++) {
        int key = arr[j];
        int i = j - 1;

        while (i >= 0 && arr[i] > key) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = key;
    }
}

/*
 * Purpose:
 * Fills the array with random numbers between 0 and 9999.
 */
void generateRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

/*
 * Purpose:
 * Fills the array with values in ascending order from 0 to n-1.
 */
void generateSorted(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

/*
 * Purpose:
 * Fills the array with values in descending order.
 * This represents the worst case for Insertion Sort.
 */
void generateReverse(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

/*
 * Purpose:
 * Tests the execution time of Insertion Sort for a given input size.
 *
 * Steps:
 * 1. Creates three arrays dynamically.
 * 2. Generates random, sorted, and reverse sorted data.
 * 3. Measures sorting time for each case.
 * 4. Displays results in microseconds.
 * 5. Frees allocated memory.
 */
void testInsertionSort(int n) {
    cout << "\nInput Size: " << n << endl;

    int* randomArr = new int[n];
    int* sortedArr = new int[n];
    int* reverseArr = new int[n];

    generateRandom(randomArr, n);
    generateSorted(sortedArr, n);
    generateReverse(reverseArr, n);

    auto start = high_resolution_clock::now();
    insertionSort(randomArr, n);
    auto end = high_resolution_clock::now();
    cout << "Random Input Time: "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds" << endl;

    start = high_resolution_clock::now();
    insertionSort(sortedArr, n);
    end = high_resolution_clock::now();
    cout << "Sorted Input Time: "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds" << endl;

    start = high_resolution_clock::now();
    insertionSort(reverseArr, n);
    end = high_resolution_clock::now();
    cout << "Reverse Sorted Input Time: "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds" << endl;

    delete[] randomArr;
    delete[] sortedArr;
    delete[] reverseArr;
}

/*
 * Entry point of the program.
 *
 * Steps:
 * 1. Initializes random seed using current time.
 * 2. Defines different input sizes.
 * 3. Calls testInsertionSort() for each size.
 *
 * Output:
 * Displays execution time for random, sorted, and reverse sorted inputs
 * for each array size.
 */
int main() {
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    for (int i = 0; i < 5; i++) {
        testInsertionSort(sizes[i]);
    }

    return 0;
}
