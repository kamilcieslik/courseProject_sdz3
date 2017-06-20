//
// Created by mrfarinq on 13.05.17.
//

#include <iomanip>
#include "UsefulStructuresForAlgorithms.h"

// -------------------------------------------------------------------
// Definicja przedmiotu plecaka na potrzeby problemu plecakowego.
// -------------------------------------------------------------------
Item::Item() : itemSize(0), itemValue(0), itemId(0), itemRatio(0) {

}

Item::Item(int _itemSize, int _itemValue, int _itemId, float _itemRatio) : itemSize(_itemSize), itemValue(_itemValue),
                                                                           itemId(_itemId),
                                                                           itemRatio(_itemRatio) {
    
}

// -----------------------------------------------------------------------------------
// Kolejka na bazie kopca na użytek zachłannego algorytmu plecakowego.
// Kolejka obsługuje dwa rodzaje sortowań: po wartości, po stosunku wartość/rozmiar.
// -----------------------------------------------------------------------------------
Heap::Heap(int _size, bool _setSortByValue) : numberOfItems(0), size(_size), setSortByValue(_setSortByValue) {
    arrayOfItems = new Item[_size];
}

Heap::~Heap() {
    delete[] arrayOfItems;
    numberOfItems = 0;
    size = 0;
    arrayOfItems = nullptr;
}

void Heap::PushItem(Item newItem) {
    if (numberOfItems >= size)
        throw std::overflow_error("Brak miejsca w kopcu.");
    int i, j;
    i = numberOfItems++;
    j = (i - 1) / 2;
    if (setSortByValue) {
        while (i && arrayOfItems[j].itemValue < newItem.itemValue) {
            arrayOfItems[i] = arrayOfItems[j];
            i = j;
            j = (i - 1) / 2;
        }
    } else {
        while (i && arrayOfItems[j].itemRatio < newItem.itemRatio) {
            arrayOfItems[i] = arrayOfItems[j];
            i = j;
            j = (i - 1) / 2;
        }
    }
    arrayOfItems[i] = newItem;
}

Item Heap::PopItem() {
    if (numberOfItems == 0)
        throw std::underflow_error("Kopiec jest pusty.");
    
    int i, j;
    Item lastLeaf;
    Item top = arrayOfItems[0];
    
    lastLeaf = arrayOfItems[--numberOfItems];
    
    i = 0;
    j = 1;
    
    if (setSortByValue) {
        while (j < numberOfItems) {
            if ((j + 1 < numberOfItems) && (arrayOfItems[j + 1].itemValue > arrayOfItems[j].itemValue))
                j++;
            if (lastLeaf.itemValue >= arrayOfItems[j].itemValue)
                break;
            arrayOfItems[i] = arrayOfItems[j];
            i = j;
            j = 2 * j + 1;
        }
    } else {
        while (j < numberOfItems) {
            if ((j + 1 < numberOfItems) && (arrayOfItems[j + 1].itemRatio > arrayOfItems[j].itemRatio))
                j++;
            if (lastLeaf.itemRatio >= arrayOfItems[j].itemRatio)
                break;
            arrayOfItems[i] = arrayOfItems[j];
            i = j;
            j = 2 * j + 1;
        }
    }
    
    arrayOfItems[i] = lastLeaf;
    return top;
}

int Heap::GetNumberOfItems() {
    return numberOfItems;
}


// -------------------------------------------------------------------
// Lista przechowująca rozwiązania problemu plecakowego.
// -------------------------------------------------------------------
ListOfPackedItems::ListOfPackedItems() : numberOfPackedItems(0) {
    head = nullptr;
    tail = nullptr;
}

ListOfPackedItems::~ListOfPackedItems() {
    DeletePackedItems();
}

void ListOfPackedItems::DeletePackedItems() {
    numberOfPackedItems = 0;
    PackedItem *packedItem;
    while (head != nullptr) {
        packedItem = head->next;
        delete head;
        head = packedItem;
    }
    head = nullptr;
    tail = nullptr;
}

void ListOfPackedItems::AddItemAtTheEnd(Item newItem) {
    numberOfPackedItems++;
    PackedItem *newPackedItem = new PackedItem();
    newPackedItem->previous = tail;
    newPackedItem->next = nullptr;
    tail = newPackedItem;
    if (newPackedItem->previous != nullptr) {
        newPackedItem->previous->next = newPackedItem;
    } else {
        head = newPackedItem;
    }
    newPackedItem->packedItem = newItem;
}

void ListOfPackedItems::ShowList() {
    if (numberOfPackedItems == 0) {
        throw std::logic_error("Brak przedmiotów w plecaku.");
    }
    
    std::cout << "Item\tSize\tValue\tRatio" << std::endl;
    std::cout << "------------------------------" << std::endl;
    
    int sumOfSizes = 0, sumOfValues = 0;
    PackedItem *packedItem = head;
    while (packedItem != nullptr) {
        std::cout << packedItem->packedItem.itemId << "\t";
        std::cout << packedItem->packedItem.itemSize << "\t";
        sumOfSizes += packedItem->packedItem.itemSize;
        std::cout << packedItem->packedItem.itemValue << "\t";
        sumOfValues += packedItem->packedItem.itemValue;
        std::cout << std::fixed << std::setprecision(2)
                  << (float) packedItem->packedItem.itemValue / (float) packedItem->packedItem.itemSize << std::endl;
        packedItem = packedItem->next;
    }
    std::cout << "------------------------------" << std::endl;
    std::cout << "Total\t" << sumOfSizes << "\t" << sumOfValues << std::endl;
    delete packedItem;
    printf("\n");
}
