const int MAX_ITEMS = 10;

enum RelationType {LESS, GREATER, EQUAL};

class ItemType {
public:
    ItemType();                 // default constructor
    ItemType(int key);          // constructor with key

    RelationType ComparedTo(ItemType item) const;

    void SetKey(int key);
    int GetKey() const;

private:
    int key;   // the "key" that uniquely identifies the item
};
ItemType::ItemType() {
    key = 0;
}

ItemType::ItemType(int key) {
    this->key = key;
}

RelationType ItemType::ComparedTo(ItemType item) const {
    if (key < item.key)
        return LESS;
    else if (key > item.key)
        return GREATER;
    else
        return EQUAL;
}

void ItemType::SetKey(int key) {
    this->key = key;
}

int ItemType::GetKey() const {
    return key;
}