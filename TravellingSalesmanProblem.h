//
// Created by mrfarinq on 16.06.17.
//

#ifndef SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
#define SDIZO_3_TRAVELLINGSALESMANPROBLEM_H

#include <iostream>

class TravellingSalesmanProblem {
private:
    int amountOfCities;
    int **arrayOfMatrixOfCities;
    int *optimalWay_Solution;
    int *allPossiblePermutations;
    int length;
    bool setGreedyAlgorithm;
public:
    TravellingSalesmanProblem();

    ~TravellingSalesmanProblem();

    void DeleteTravellingSalesman();

    void ReadCitiesFromFile(std::string path);

    void GenerateRandomCities(int amountOfCities = 0, int maxDistanceBetweenCity = 99);

    void PrintCitiesForTheTravellingSalesman();

    void GreedyAlgorithm();

    void CalculateTheMostOptimalPermutation(int recursive_param);

    void BruteForceAlgorithm();

    void PrintSolution();
};


#endif //SDIZO_3_TRAVELLINGSALESMANPROBLEM_H
