//
// Created by mrfarinq on 16.06.17.
//

#ifndef SDIZO_3_DISCRETEKNAPSACKPROBLEM_H
#define SDIZO_3_DISCRETEKNAPSACKPROBLEM_H

#include "UsefulStructuresForAlgorithms.h"
#include <iostream>


class DiscreteKnapsackProblem {
private:
    int capacityOfKnapsack;
    int amountOfItems;
    Item *itemsForTheKnapsack;
    ListOfPackedItems packedItems_Solution;
    bool setGreedyAlgorithmSortByValueVersion;
    bool setGreedyAlgorithm;

public:
    DiscreteKnapsackProblem();
    
    ~DiscreteKnapsackProblem();
    
    void DeleteDiscreteKnapsack();
    
    void ReadItemsFromFile(std::string path);
    
    void GenerateRandomItems(int amountOfItems = 0, int capacityOfKnapsack = 0, int maxValueForItem = 20);
    
    void PrintItemsForTheKnapsack();
    
    void GreedyAlgorithm(bool _setGreedyAlgorithmSortByValueVersion);
    
    void DynamicAlgorithm();
    
    void PrintSolution();
};


#endif //SDIZO_3_DISCRETEKNAPSACKPROBLEM_H
