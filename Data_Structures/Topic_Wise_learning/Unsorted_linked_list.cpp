#include<iostream>
using namespace std;

template <class itemtype>
struct Nodetype{
    itemtype info;
    Nodetype* next;
};
template <class itemtype>
class unsortedtype{
    private:
    Nodetype<itemtype>* listData;
    int length;
    Nodetype<itemtype>* currentPos;
    
    public:
    unsortedtype(){
        length=0;
        listData= NULL;
        currentPos= NULL;
    }
    
    bool IsFull() const{
        Nodetype<itemtype>* location;
        try{
            location = new Nodetype<itemtype>;  //allocate node
            delete location; //free memory
            return false;  //if list is not full
        }
        catch(bad_alloc& exception){
            return true; //list is full
        }
    }
    
    int IsLength() const{
        return length;
    }

    void makeEmpty(){
        Nodetype<itemtype>* tempPtr;
        while(listData!=NULL){  //loop will stop when listdata becomes NULL
            tempPtr = listData; //tempPtr points on first node
            listData= listData->next; //move listdata to next location
            delete tempPtr; //delete the first node
        }
        length = 0; //reset length to 0
    }

    void retrieveItem(itemtype& item, bool& found){
        bool moreToSearch;  //to check if there are more nodes to search
        Nodetype<itemtype>* location; 
        location = listData;  //start from head of list
        found = false; //initially, assuming item is not found
        moreToSearch=(location != NULL); //check if list is not empty

        // Keep searching until either the item is found
        // or there are no more nodes left
        while(moreToSearch && !found){
            if (item == location->info)
            {
                // Item found: update 'found'
                found = true;
                // Assign the value from node to item (to return it)
                item = location->info;
            }
            else
            {
                //move to the next node
                location = location->next;
                //check if next node exists
                moreToSearch = (location!=NULL);
            }
        }
    }

    void insertItem(itemtype item){
        //create new node
        Nodetype<itemtype>* location;
        location = new Nodetype<itemtype>;
        // Store the item in the new node
        location -> info = item;
        // Make the new node point to the current head (listData)
        location -> next = listData;
        // Update head pointer: now the new node is the first node
        listData = location;
        length++; //increase count of node in the list
    }

    void DeleteItem(itemtype item){
        Nodetype<itemtype>* location = listData; //start from head
        Nodetype<itemtype>* tempLocation; //will point to node to be deleted 
        //case1: if node to be deleted is first node(head)
        if (item == listData->info)
        {
            tempLocation = location;  //store node to delete
            listData = listData->next;  //move head to next node
        }
        else
        {
            // Iterate until the node *before* the one to be deleted is found
            while(!(item==(location->next)->info)){
            location=location->next;   //move forward in the list
            }
            //case2: Node to delete is somewhere after head
            tempLocation=location->next;   //node to delete
            location->next= (location->next)->next;  //skip the node to be deleted
        }
        delete tempLocation;  //free memory of deleted node 
        length--;  //decrese length of the list
    }

    void resetList(){
        currentPos= NULL;
    }

    void getNextItem(itemtype& item){
        if (currentPos==NULL){
            currentPos=listData;
        }
        else{
            currentPos=  currentPos->next;
        }
        item= currentPos->info;
    }

};

int main(){
    unsortedtype<int> myList;

    // Insert some items
    myList.insertItem(10);
    myList.insertItem(20);
    myList.insertItem(30);
    myList.insertItem(40);

    cout << "List after inserting 40, 30, 20, 10 (head insertion): " << endl;
    myList.resetList();
    int item;
    for (int i = 0; i < myList.IsLength(); i++) {
        myList.getNextItem(item);
        cout << item << " ";
    }
    cout << endl;

    // Retrieve an item
    int searchItem = 20;
    bool found;
    myList.retrieveItem(searchItem, found);
    if (found)
        cout << "Item " << searchItem << " found in list." << endl;
    else
        cout << "Item not found." << endl;
    
    //Length of list before deletion
     cout << "Length of list before deletion = " << myList.IsLength() << endl;

    // Delete an item
    cout << "Deleting 30 from list..." << endl;
    myList.DeleteItem(30);

    cout << "List after deletion: " << endl;
    myList.resetList();
    for (int i = 0; i < myList.IsLength(); i++) {
        myList.getNextItem(item);
        cout << item << " ";
    }
    cout << endl;

    // Length of list after deletion
    cout << "Length of list after deletion = " << myList.IsLength() << endl;

    // Make list empty
    cout << "Making list empty..." << endl;
    myList.makeEmpty();
    cout << "Length of list after emptying = " << myList.IsLength() << endl;

    return 0;
}