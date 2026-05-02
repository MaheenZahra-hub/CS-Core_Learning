#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

// Partition (First Pivot)
int partitionFirst(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= high && arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < j)
            swap(arr[i], arr[j]);
        else
            break;
    }
    swap(arr[low], arr[j]);
    return j;
}

// Quick Sort (First Pivot)
void quickSortFirst(int arr[], int low, int high) {
    if (low < high) {
        int p = partitionFirst(arr, low, high);
        quickSortFirst(arr, low, p - 1);
        quickSortFirst(arr, p + 1, high);
    }
}

// Partition (Random Pivot)
int partitionRandom(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[randomIndex]);
    return partitionFirst(arr, low, high);
}

// Quick Sort (Random Pivot)
void quickSortRandom(int arr[], int low, int high) {
    if (low < high) {
        int p = partitionRandom(arr, low, high);
        quickSortRandom(arr, low, p - 1);
        quickSortRandom(arr, p + 1, high);
    }
}

// Input Generator
void generateInput(int arr[], int n, string type) {
    if (type == "random") {
        for (int i = 0; i < n; i++)
            arr[i] = rand() % n;
    }
    else if (type == "sorted") {
        for (int i = 0; i < n; i++)
            arr[i] = i;
    }
    else if (type == "reverse") {
        for (int i = 0; i < n; i++)
            arr[i] = n - i;
    }
}

// Time Measurement (Microseconds)
long long measureTime(void (*sortFunc)(int[], int, int), int arr[], int n) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, 0, n - 1);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

int main() {
    srand(time(0));

    int sizes[] = {100, 500, 1000, 5000, 10000};
    string types[] = {"random", "sorted", "reverse"};

    for (string type : types) {
        cout << "\nInput Type: " << type << endl;

        for (int n : sizes) {

            int arr1[n], arr2[n];

            generateInput(arr1, n, type);

            // Copy array for second test
            for (int i = 0; i < n; i++)
                arr2[i] = arr1[i];

            long long t1 = measureTime(quickSortFirst, arr1, n);
            long long t2 = measureTime(quickSortRandom, arr2, n);

            cout << "n = " << n
                 << " | First Pivot: " << t1 << " micro sec"
                 << " | Random Pivot: " << t2 << " micro sec\n";
        }
    }

    return 0;
}