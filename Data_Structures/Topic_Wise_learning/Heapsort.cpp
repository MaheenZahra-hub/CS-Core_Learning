#include <iostream>
using namespace std;

//ItemType class
class ItemType {
private:
    int key;

public:
    ItemType() { key = 0; }          // default constructor
    ItemType(int k) { key = k; }     // parameterized constructor

    void SetKey(int k) { key = k; }
    int GetKey() const { return key; }

    // Operator overloading for comparisons
    bool operator<(const ItemType& other) const { return key < other.key; }
    bool operator>(const ItemType& other) const { return key > other.key; }
    bool operator==(const ItemType& other) const { return key == other.key; }
};

// Heap class
class Heap {
private:
    ItemType* A;
    int heap_size;
    int length;

    void MaxHeapify(int i) {
        int l = 2 * i;      // left child
        int r = 2 * i + 1;  // right child
        int largest = i;

        if (l <= heap_size && A[l] > A[i])
            largest = l;
        if (r <= heap_size && A[r] > A[largest])
            largest = r;

        if (largest != i) {
            swap(A[i], A[largest]);
            MaxHeapify(largest);
        }
    }

    void BuildMaxHeap() {
        heap_size = length;
        for (int i = length / 2; i >= 1; i--)
            MaxHeapify(i);
    }

public:
    Heap(int arr[], int size) {
        length = size;                            // Store total number of elements
        heap_size = size;                         //current number of elements
        A = new ItemType[size + 1];               // Create a new internal array

        // Copy each element from input array into heap's internal array
        for (int i = 1; i <= size; i++)           
            A[i] = ItemType(arr[i]);
    }

    ~Heap() { delete[] A; }

    void HeapSort() {
        BuildMaxHeap();
        for (int i = length; i >= 2; i--) {
            swap(A[1], A[i]);
            heap_size--;
            MaxHeapify(1);
        }
    }

    void Print() const {
        for (int i = 1; i <= length; i++)
            cout << A[i].GetKey() << " ";
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int* input = new int[n + 1];
    cout << "Enter elements:\n";
    for (int i = 1; i <= n; i++)
        cin >> input[i];

    cout << "Original: ";
    for (int i = 1; i <= n; i++)
        cout << input[i] << " ";
    cout << endl;

    Heap heap(input, n);
    heap.HeapSort();

    cout << "Sorted:   ";
    heap.Print();

    delete[] input;

    cout << "Press Enter to exit...";
    cin.ignore();
    cin.get();

    return 0;
}
