#include<iostream>
#include"itemtype.h"
#include"sorted.h"
using namespace std;

int main() {
    SortedType list;
    ItemType item;
    bool found;

    // Insert some items
    int keysToInsert[] = {50, 20, 70, 40, 60};
    cout << "Inserting items: ";
    for (int key : keysToInsert) {
        item.SetKey(key);
        list.InsertItem(item);
        cout << key << " ";
    }
    cout << endl;

    // Display all items
    cout << "Items in sorted order: ";
    list.ResetList();
    for (int i = 0; i < list.LengthIs(); i++) {
        list.GetNextItem(item);
        cout << item.GetKey() << " ";
    }
    cout << endl;

    // Retrieve an item
    item.SetKey(40);
    list.RetrieveItem(item, found);
    if (found)
        cout << "Item 40 found in the list." << endl;
    else
        cout << "Item 40 not found." << endl;

    // Delete an item
    item.SetKey(50);
    list.DeleteItem(item);
    cout << "After deleting 50, items are: ";
    list.ResetList();
    for (int i = 0; i < list.LengthIs(); i++) {
        list.GetNextItem(item);
        cout << item.GetKey() << " ";
    }
    cout << endl;

    // Check if list is full
    cout << "Is the list full? " << (list.IsFull() ? "Yes" : "No") << endl;

    // Make the list empty
    list.MakeEmpty();
    cout << "After making empty, list length: " << list.LengthIs() << endl;

    return 0;
}