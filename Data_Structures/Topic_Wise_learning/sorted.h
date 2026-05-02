class SortedType {
public:
    SortedType();

    void MakeEmpty();
    bool IsFull() const;
    int LengthIs() const;

    void RetrieveItem(ItemType& item, bool& found);
    void InsertItem(ItemType item);
    void DeleteItem(ItemType item);

    void ResetList();
    void GetNextItem(ItemType& item);

private:
    int length;
    ItemType info[MAX_ITEMS];
    int currentPos;
};
SortedType::SortedType() {
    length = 0;
    currentPos = -1;
}

void SortedType::MakeEmpty() {
    length = 0;
}

bool SortedType::IsFull() const {
    return (length == MAX_ITEMS);
}

int SortedType::LengthIs() const {
    return length;
}
void SortedType::RetrieveItem(ItemType& item, bool& found)
{
    int midpoint;
    int first=0;
    int last = length - 1;

    bool moreToSearch = first<=last;
    found = false;

    while (moreToSearch && !found) {
        midpoint=(first + last)/2;
        switch (item.ComparedTo(info[midpoint])) {
        case LESS:
            last = midpoint - 1;
            moreToSearch = first<=last;
            break;
        case GREATER:
            first = midpoint +1;
            moreToSearch = first<=last;
            break;
        case EQUAL:
            found = true;
            item = info[midpoint];
            break;
        }
    }
}
void SortedType::InsertItem(ItemType item) {
    int location = 0;

    // Find the correct position to insert
    while (location < length && item.ComparedTo(info[location]) == GREATER) {
        location++;
    }

    // Shift items to make space
    for (int index = length; index > location; index--) {
        info[index] = info[index - 1];
    }

    // Insert the new item
    info[location] = item;
    length++;
}

void SortedType::DeleteItem(ItemType item) {
    int location = 0;
    while (item.ComparedTo(info[location]) != EQUAL)
        location++;
    for (int index = location+1;index<length;index++)
        info[index - 1]=info [index]; // overwrite with last element
    length--;
}

void SortedType::ResetList() {
    currentPos = -1;
}

void SortedType::GetNextItem(ItemType& item) {
    currentPos++;
    item = info[currentPos];
}