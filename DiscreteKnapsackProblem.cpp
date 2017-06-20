//
// Created by mrfarinq on 16.06.17.
//

#include <fstream>
#include <random>
#include <iomanip>
#include "DiscreteKnapsackProblem.h"


DiscreteKnapsackProblem::DiscreteKnapsackProblem() : capacityOfKnapsack(0), amountOfItems(0),
                                                     itemsForTheKnapsack(nullptr) {
    
}

DiscreteKnapsackProblem::~DiscreteKnapsackProblem() {
    DeleteDiscreteKnapsack();
}

void DiscreteKnapsackProblem::DeleteDiscreteKnapsack() {
    delete[] itemsForTheKnapsack;
    itemsForTheKnapsack = nullptr;
    packedItems_Solution.DeletePackedItems();
}

void DiscreteKnapsackProblem::ReadItemsFromFile(std::string path) {
    if (itemsForTheKnapsack != nullptr)
        DeleteDiscreteKnapsack();
    
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        file >> capacityOfKnapsack;
        file >> amountOfItems;
        itemsForTheKnapsack = new Item[amountOfItems];
        
        if (file.fail()) throw std::logic_error("Błąd odczytu danych w pliku.");
        else {
            int itemSize, itemValue;
            float itemRatio;
            for (auto i = 0; i < amountOfItems; i++) {
                file >> itemSize;
                file >> itemValue;
                itemRatio = (float) itemValue / (float) itemSize;
                
                if (file.fail()) throw std::logic_error("Błąd odczytu danych w pliku.");
                else {
                    itemsForTheKnapsack[i] = Item(itemSize, itemValue, i, itemRatio);
                }
            }
            file.close();
            
            PrintItemsForTheKnapsack();
        }
    } else {
        std::cout << "Błąd otwarcia pliku.\n";
    }
}


void DiscreteKnapsackProblem::GenerateRandomItems(int amountOfItems, int capacityOfKnapsack, int maxValueForItem) {
    if (itemsForTheKnapsack != nullptr)
        DeleteDiscreteKnapsack();
    
    if (amountOfItems == 0 && capacityOfKnapsack == 0) {
        std::cout << "Podaj ilość przedmiotów: ";
        std::cin >> this->amountOfItems;
        if (this->amountOfItems < 1) {
            throw std::invalid_argument("Liczba przedmiotów nie może być mniejsza od 1.");
        }
        
        itemsForTheKnapsack = new Item[this->amountOfItems];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist_sizesForItems(1, (int) (ceil(0.6 * maxValueForItem)));
        std::uniform_int_distribution<> dist_valuesForItems(1, maxValueForItem);
        
        int sumOfValuesOfAllItems = 0;
        int itemSize, itemValue;
        float itemRatio;
        for (auto i = 0; i < this->amountOfItems; i++) {
            itemSize = dist_sizesForItems(gen);
            itemValue = dist_valuesForItems(gen);
            itemRatio = (float) itemValue / (float) itemSize;
            itemsForTheKnapsack[i] = Item(itemSize, itemValue, i, itemRatio);
            sumOfValuesOfAllItems += itemsForTheKnapsack[i].itemValue;
        }
        
        std::uniform_int_distribution<> dist_capacityOfKnapsack((int) (ceil(0.1 * sumOfValuesOfAllItems)),
                                                                sumOfValuesOfAllItems);
        this->capacityOfKnapsack = dist_capacityOfKnapsack(gen);
    } else {
        this->amountOfItems = amountOfItems;
        this->capacityOfKnapsack = capacityOfKnapsack;
        
        itemsForTheKnapsack = new Item[this->amountOfItems];
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist_sizesForItems(1, (int) (ceil(0.6 * maxValueForItem)));
        std::uniform_int_distribution<> dist_valuesForItems(1, maxValueForItem);
        
        int sumOfValuesOfAllItems = 0;
        int itemSize, itemValue;
        float itemRatio;
        for (auto i = 0; i < this->amountOfItems; i++) {
            itemSize = dist_sizesForItems(gen);
            itemValue = dist_valuesForItems(gen);
            itemRatio = (float) itemValue / (float) itemSize;
            itemsForTheKnapsack[i] = Item(itemSize, itemValue, i, itemRatio);
            sumOfValuesOfAllItems += itemsForTheKnapsack[i].itemValue;
        }
    }
}

void DiscreteKnapsackProblem::PrintItemsForTheKnapsack() {
    if (itemsForTheKnapsack == nullptr)
        throw std::logic_error("Brak przedmiotów do wyświetlenia.");
    
    std::cout << "\e[1mProblem\e[0m" << std::endl << std::endl;
    std::cout << "Capacity:\t" << capacityOfKnapsack << std::endl;
    std::cout << "Items:\t\t" << amountOfItems << std::endl << std::endl;
    std::cout << "Item\tSize\tValue\tRatio" << std::endl;
    std::cout << "------------------------------" << std::endl;
    for (auto i = 0; i < amountOfItems; i++) {
        std::cout << itemsForTheKnapsack[i].itemId << "\t";
        std::cout << itemsForTheKnapsack[i].itemSize << "\t";
        std::cout << itemsForTheKnapsack[i].itemValue << "\t";
        std::cout << std::fixed << std::setprecision(2)
                  << (float) itemsForTheKnapsack[i].itemValue / (float) itemsForTheKnapsack[i].itemSize << std::endl;
    }
}

// ----------------------------------------------------------------------------------------------------
// Algorytm zachłanny dla problemu plecakowego, wersja z sortowaniem wg stosunku wartości przedmiotu.
// ----------------------------------------------------------------------------------------------------
void DiscreteKnapsackProblem::GreedyAlgorithmSortByValueVersion() {
    if (itemsForTheKnapsack == nullptr)
        throw std::logic_error("Brak przedmiotów do przeprowadzenia algorytmu problemu plecakowego.");
    Heap heapForItems(amountOfItems, true); //true - wybór sortowania po wartości.
    setGreedyAlgorithm = true;
    setGreedyAlgorithmSortByValueVersion = true;
    
    for (auto i = 0; i < amountOfItems; i++) {
        heapForItems.PushItem(itemsForTheKnapsack[i]);
    }
    int currentWeightOfItemsInTheKnapsack = 0;
    
    packedItems_Solution.DeletePackedItems();
    Item item;
    while (heapForItems.GetNumberOfItems() != 0) {
        item = heapForItems.PopItem();
        if (item.itemSize + currentWeightOfItemsInTheKnapsack <= capacityOfKnapsack) {
            packedItems_Solution.AddItemAtTheEnd(item);
            currentWeightOfItemsInTheKnapsack += item.itemSize;
        }
    }
}

// -----------------------------------------------------------------------------------------------
// Algorytm zachłanny dla problemu plecakowego, wersja z sortowaniem wg stosunku wartość/rozmiar.
// -----------------------------------------------------------------------------------------------
void DiscreteKnapsackProblem::GreedyAlgorithmSortByRatioVersion() {
    if (itemsForTheKnapsack == nullptr)
        throw std::logic_error("Brak przedmiotów do przeprowadzenia algorytmu problemu plecakowego.");
    Heap heapForItems(amountOfItems, false); //true - wybór sortowania po stosunku wartość/rozmiar.
    setGreedyAlgorithm = true;
    setGreedyAlgorithmSortByValueVersion = false;
    
    for (auto i = 0; i < amountOfItems; i++) {
        heapForItems.PushItem(itemsForTheKnapsack[i]);
    }
    int currentWeightOfItemsInTheKnapsack = 0;
    
    packedItems_Solution.DeletePackedItems();
    Item item;
    while (heapForItems.GetNumberOfItems() != 0) {
        item = heapForItems.PopItem();
        if (item.itemSize + currentWeightOfItemsInTheKnapsack <= capacityOfKnapsack) {
            packedItems_Solution.AddItemAtTheEnd(item);
            currentWeightOfItemsInTheKnapsack += item.itemSize;
        }
    }
}

// ----------------------------------------------------------------------------------
// Definicja funkcji zwracającej większą wartość na potrzeby algorytmu dynamicznego.
// ----------------------------------------------------------------------------------
int max(int firstValue, int secondValue) {
    int max;
    if (firstValue > secondValue)
        max = firstValue;
    else
        max =  secondValue;
    return max;
}

// -------------------------------------------------------------------
// Algorytm dynamiczny dla problemu plecakowego.
// -------------------------------------------------------------------
void DiscreteKnapsackProblem::DynamicAlgorithm() {
    if (itemsForTheKnapsack == nullptr)
        throw std::logic_error("Brak przedmiotów do przeprowadzenia algorytmu problemu plecakowego.");
    
    setGreedyAlgorithm = false;
    packedItems_Solution.DeletePackedItems();
    
    int **results = new int *[amountOfItems + 1];
    
    for (auto i = 0; i < amountOfItems + 1; ++i) {
        results[i] = new int[capacityOfKnapsack + 1];
    }
    
    for (auto itemIt = 0; itemIt <= amountOfItems; itemIt++) {
        for (auto capIt = 0; capIt <= capacityOfKnapsack; capIt++) {
            if (itemIt == 0 || capIt == 0) {
                results[itemIt][capIt] = 0;
            } else if (itemsForTheKnapsack[itemIt - 1].itemSize <= capIt) {
                results[itemIt][capIt] = max(itemsForTheKnapsack[itemIt - 1].itemValue +
                                             results[itemIt - 1][capIt - itemsForTheKnapsack[itemIt - 1].itemSize],
                                             results[itemIt - 1][capIt]);
            } else {
                results[itemIt][capIt] = results[itemIt - 1][capIt];
            }
        }
    }
    
    int howManyUnpackagedItemsHaveBeenLeft = amountOfItems;
    int howMuchCapacityHasBeenLeft = capacityOfKnapsack;
    while (howManyUnpackagedItemsHaveBeenLeft > 0 && howMuchCapacityHasBeenLeft > 0) {
        if (results[howManyUnpackagedItemsHaveBeenLeft][howMuchCapacityHasBeenLeft] !=
            results[howManyUnpackagedItemsHaveBeenLeft - 1][howMuchCapacityHasBeenLeft]) {
            packedItems_Solution.AddItemAtTheEnd(itemsForTheKnapsack[howManyUnpackagedItemsHaveBeenLeft - 1]);
            howMuchCapacityHasBeenLeft =
                    howMuchCapacityHasBeenLeft - itemsForTheKnapsack[howManyUnpackagedItemsHaveBeenLeft - 1].itemSize;
        }
        howManyUnpackagedItemsHaveBeenLeft--;
    }
    
    for (auto i = 0; i < amountOfItems + 1; ++i) {
        delete[] results[i];
    }
    delete[] results;
}

void DiscreteKnapsackProblem::PrintSolution() {
    try {
        std::cout << "\e[1mSolution\e[0m" << std::endl;
        if (setGreedyAlgorithm) {
            
            if (setGreedyAlgorithmSortByValueVersion)
                std::cout << "\e[1mGreedy Algorithm - Version: Sort By Value\e[0m" << std::endl << std::endl;
            else
                std::cout << "\e[1mGreedy Algorithm - Version: Sort By Ratio\e[0m" << std::endl << std::endl;
        } else {
            std::cout << "\e[1mDynamic Algorithm\e[0m" << std::endl << std::endl;
        }
        packedItems_Solution.ShowList();
    }
    catch (std::logic_error &e) {
        std::cout << e.what() << std::endl;
    }
}
