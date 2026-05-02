#include<iostream>
#include"itemtype.h"
#include"unsorted.h"
using namespace std;

int main() {
    UnsortedType list;  // Use UnsortedType
    ItemType item;
    bool found;

    // Insert items (unsorted order)
    list.InsertItem(ItemType(30));
    list.InsertItem(ItemType(10));
    list.InsertItem(ItemType(50));
    list.InsertItem(ItemType(20));

    cout << "List length: " << list.LengthIs() << endl;

    // Display items (in insertion order)
    cout << "Items in list: ";
    list.ResetList();
    for (int i = 0; i < list.LengthIs(); i++) {
        list.GetNextItem(item);
        cout << item.GetKey() << " ";  // Use GetKey()
    }
    cout << endl;

    // Retrieve item
    item.SetKey(20);  // Use SetKey()
    list.RetrieveItem(item, found);
    if (found)
        cout << "Item found: " << item.GetKey() << endl;
    else
        cout << "Item not found." << endl;

    // Delete item
    list.DeleteItem(ItemType(30));
    cout << "List length after delete: " << list.LengthIs() << endl;

    // Display after delete
    cout << "Items in list: ";
    list.ResetList();
    for (int i = 0; i < list.LengthIs(); i++) {
        list.GetNextItem(item);
        cout << item.GetKey() << " ";
    }
    cout << endl;

    return 0;
}