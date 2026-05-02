/*
 * Description:
 * This program implements the Merge Sort algorithm and measures
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
 * Merges two sorted subarrays into a single sorted portion.
 * * Parameters:
 * arr   -> The original array containing the subarrays
 * left  -> Starting index of the left subarray
 * mid   -> Ending index of the left subarray
 * right -> Ending index of the right subarray
 */
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temporary dynamic arrays
    int* leftArr = new int[n1];
    int* rightArr = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0;    // Initial index of leftArr
    int j = 0;    // Initial index of rightArr
    int k = left; // Initial index of merged array

    // Merge the temp arrays back into arr[left..right]
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // Free memory
    delete[] leftArr;
    delete[] rightArr;
}

/*
 * Purpose:
 * Recursively divides the array and sorts it using Merge Sort.
 */
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find midpoint (formula avoids potential integer overflow)
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Data Generation Functions

void generateRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;
    }
}

void generateSorted(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generateReverse(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

/*
 * Purpose:
 * Tests the execution time of Merge Sort for a given input size.
 */
void testMergeSort(int n) {
    cout << "\nInput Size: " << n << endl;

    int* randomArr = new int[n];
    int* sortedArr = new int[n];
    int* reverseArr = new int[n];

    generateRandom(randomArr, n);
    generateSorted(sortedArr, n);
    generateReverse(reverseArr, n);

    // Test Random
    auto start = high_resolution_clock::now();
    mergeSort(randomArr, 0, n - 1);
    auto end = high_resolution_clock::now();
    cout << "Random Input Time: "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds" << endl;

    // Test Sorted
    start = high_resolution_clock::now();
    mergeSort(sortedArr, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "Sorted Input Time: "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds" << endl;

    // Test Reverse
    start = high_resolution_clock::now();
    mergeSort(reverseArr, 0, n - 1);
    end = high_resolution_clock::now();
    cout << "Reverse Sorted Input Time: "
         << duration_cast<microseconds>(end - start).count()
         << " microseconds" << endl;

    delete[] randomArr;
    delete[] sortedArr;
    delete[] reverseArr;
}

int main() {
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};

    for (int i = 0; i < 5; i++) {
        testMergeSort(sizes[i]);
    }

    return 0;
}