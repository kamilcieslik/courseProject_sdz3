//
// Created by mrfarinq on 13.05.17.
//

#ifndef SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
#define SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H

#include <iostream>
#include <climits>

struct Item {
    int itemSize;
    int itemValue;
    int itemId;
    float itemRatio;
    
    Item();
    
    Item(int _itemSize, int _itemValue, int _itemId, float _itemRatio);
    
};

struct ListOfPackedItems {
    ListOfPackedItems();
    
    ~ListOfPackedItems();
    
    void DeletePackedItems();
    
    int numberOfPackedItems;
    struct PackedItem {
        Item packedItem;
        PackedItem *previous;
        PackedItem *next;
    };
    PackedItem *head, *tail;
    
    void AddItemAtTheEnd(Item newItem);
    
    void ShowList();
};


class Heap {
private:
    int size;
    int numberOfItems;
    Item *arrayOfItems;
    bool setSortByValue;
public:
    Heap(int _size, bool _setSortByValue);
    
    ~Heap();
    
    void PushItem(Item newItem);
    
    Item PopItem();
    
    int GetNumberOfItems();
};

#endif //SDIZO_2_USEFULSTRUCTURESFORALGORITHMS_H
