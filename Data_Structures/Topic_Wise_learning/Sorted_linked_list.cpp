#include<iostream>
using namespace std;

template <class itemtype>
struct Nodetype{
    itemtype info;
    Nodetype* next;
};

template <class itemtype>
class sortedtype{
private:
    Nodetype<itemtype>* listData;
    int length;

public:
    sortedtype(){
        length = 0;
        listData = NULL;
    }

    ~sortedtype(){
        makeEmpty();  // prevent memory leaks
    }

    bool IsFull() const{
        Nodetype<itemtype>* location;
        try{
            location = new Nodetype<itemtype>;
            delete location;
            return false;
        }
        catch(bad_alloc){
            return true;
        }
    }

    int IsLength() const{
        return length;
    }

    void makeEmpty(){
        Nodetype<itemtype>* tempPtr;
        while(listData != NULL){
            tempPtr = listData;
            listData = listData->next;
            delete tempPtr;
        }
        length = 0;
    }

    void RetrieveItem(itemtype& item, bool& found){
        Nodetype<itemtype>* location = listData;
        found = false;

        while(location != NULL){
            if(location->info < item){
                location = location->next;
            }
            else if(location->info == item){
                found = true;
                item = location->info;
                return;
            }
            else{
                return; // stop early because list is sorted
            }
        }
    }

    void InsertItem(itemtype item){
        Nodetype<itemtype>* newNode = new Nodetype<itemtype>;
        newNode->info = item;
        newNode->next = NULL;

        Nodetype<itemtype>* location = listData;
        Nodetype<itemtype>* prevNode = NULL;

        // Find correct position
        while(location != NULL && location->info < item){
            prevNode = location;
            location = location->next;
        }

        // Insert at beginning
        if(prevNode == NULL){
            newNode->next = listData;
            listData = newNode;
        }
        else{
            newNode->next = location;
            prevNode->next = newNode;
        }

        length++;
    }

    void DeleteItem(itemtype item){
        Nodetype<itemtype>* location = listData;
        Nodetype<itemtype>* prevNode = NULL;

        // Find the item
        while(location != NULL && location->info != item){
            prevNode = location;
            location = location->next;
        }

        // If not found, do nothing
        if(location == NULL){
            return;
        }

        // Delete first node
        if(prevNode == NULL){
            listData = listData->next;
        }
        else{
            prevNode->next = location->next;
        }

        delete location;
        length--;
    }

    void PrintList() const{
        Nodetype<itemtype>* temp = listData;
        while(temp != NULL){
            cout << temp->info << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ----------- TEST MAIN -----------
int main(){
    sortedtype<int> list;

    list.InsertItem(5);
    list.InsertItem(2);
    list.InsertItem(8);
    list.InsertItem(1);

    cout << "List after insertion: ";
    list.PrintList();   // Expected: 1 2 5 8

    int item = 5;
    bool found;

    list.RetrieveItem(item, found);
    if(found)
        cout << "Item found: " << item << endl;
    else
        cout << "Item not found\n";

    list.DeleteItem(2);
    cout << "After deleting 2: ";
    list.PrintList();   // Expected: 1 5 8

    cout << "Length: " << list.IsLength() << endl;

    list.makeEmpty();
    cout << "After makeEmpty: ";
    list.PrintList();   // Expected: (empty)

    return 0;
}