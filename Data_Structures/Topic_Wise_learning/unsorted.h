class UnsortedType {
public:
    UnsortedType();

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
UnsortedType::UnsortedType() {
    length = 0;
    currentPos = -1;
}

void UnsortedType::MakeEmpty() {
    length = 0;
}

bool UnsortedType::IsFull() const {
    return (length == MAX_ITEMS);
}

int UnsortedType::LengthIs() const {
    return length;
}
void UnsortedType::RetrieveItem(ItemType& item, bool& found)
{
    bool moreToSearch;
    int location = 0;
    found = false;
    moreToSearch = (location < length);

    while (moreToSearch && !found) {
        switch (item.ComparedTo(info[location])) {
        case LESS:
        case GREATER:
            location++;
            moreToSearch = (location < length);
            break;
        case EQUAL:
            found = true;
            item = info[location];
            break;
        }
    }
}
void UnsortedType::InsertItem(ItemType item) {
    info[length] = item;
    length++;
}

void UnsortedType::DeleteItem(ItemType item) {
    int location = 0;
    while (item.ComparedTo(info[location]) != EQUAL)
        location++;

    info[location] = info[length - 1]; // overwrite with last element
    length--;
}

void UnsortedType::ResetList() {
    currentPos = -1;
}

void UnsortedType::GetNextItem(ItemType& item) {
    currentPos++;
    item = info[currentPos];
}