//
// Created by mrfarinq on 16.06.17.
//

#include <fstream>
#include <random>
#include <climits>
#include <algorithm>
#include "TravellingSalesmanProblem.h"

TravellingSalesmanProblem::TravellingSalesmanProblem() : amountOfCities(0), arrayOfMatrixOfCities(nullptr),
                                                         optimalWay_Solution(nullptr) {
}

TravellingSalesmanProblem::~TravellingSalesmanProblem() {
    DeleteTravellingSalesman();
}

void TravellingSalesmanProblem::DeleteTravellingSalesman() {
    for (auto i = 0; i < amountOfCities; i++) {
        delete[] arrayOfMatrixOfCities[i];
    }
    delete[] arrayOfMatrixOfCities;
    arrayOfMatrixOfCities = nullptr;
    
    if (optimalWay_Solution != nullptr) {
        delete[] optimalWay_Solution;
        optimalWay_Solution = nullptr;
    }
}

void TravellingSalesmanProblem::ReadCitiesFromFile(std::string path) {
    if (arrayOfMatrixOfCities != nullptr)
        DeleteTravellingSalesman();
    
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        file >> amountOfCities;
        
        arrayOfMatrixOfCities = new int *[amountOfCities];
        for (auto i = 0; i < amountOfCities; i++) {
            arrayOfMatrixOfCities[i] = new int[amountOfCities];
        }
        int *securityMatrixForReadingPerLine = new int[amountOfCities];
        
        for (auto i = 0; i < amountOfCities; i++) {
            for (auto j = 0; j < amountOfCities; j++) {
                if (file.fail()) throw std::logic_error("Błąd odczytu danych w pliku.");
                file >> securityMatrixForReadingPerLine[j];
            }
            
            for (auto j = 0; j < amountOfCities; j++) {
                arrayOfMatrixOfCities[i][j] = securityMatrixForReadingPerLine[j];
            }
        }
        delete[] securityMatrixForReadingPerLine;
        file.close();
        
        PrintCitiesForTheTravellingSalesman();
    } else {
        std::cout << "Błąd otwarcia pliku.\n";
    }
}

void TravellingSalesmanProblem::GenerateRandomCities(int amountOfCities, int maxDistanceBetweenCity) {
    if (arrayOfMatrixOfCities != nullptr)
        DeleteTravellingSalesman();
    
    if (amountOfCities == 0) {
        std::cout << "Podaj ilość miast: ";
        std::cin >> this->amountOfCities;
        if (this->amountOfCities < 1) {
            throw std::invalid_argument("Liczba miast nie może być mniejsza od 1.");
        }
        
        arrayOfMatrixOfCities = new int *[this->amountOfCities];
        for (auto i = 0; i < this->amountOfCities; i++) {
            arrayOfMatrixOfCities[i] = new int[this->amountOfCities];
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist_distancesBetweenCities(1, maxDistanceBetweenCity);
        
        for (auto i = 0; i < this->amountOfCities; i++) {
            for (auto j = 0; j < this->amountOfCities; j++) {
                arrayOfMatrixOfCities[i][j] = dist_distancesBetweenCities(gen);
            }
        }
    } else {
        this->amountOfCities = amountOfCities;
        
        arrayOfMatrixOfCities = new int *[this->amountOfCities];
        for (auto i = 0; i < this->amountOfCities; i++) {
            arrayOfMatrixOfCities[i] = new int[this->amountOfCities];
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist_distancesBetweenCities(1, maxDistanceBetweenCity);
        
        for (auto i = 0; i < this->amountOfCities; i++) {
            for (auto j = 0; j < this->amountOfCities; j++) {
                arrayOfMatrixOfCities[i][j] = dist_distancesBetweenCities(gen);
            }
        }
    }
}

void TravellingSalesmanProblem::PrintCitiesForTheTravellingSalesman() {
    if (arrayOfMatrixOfCities == nullptr)
        throw std::logic_error("Brak miast do wyświetlenia.");
    
    std::cout << "\e[1mProblem\e[0m" << std::endl << std::endl;
    std::cout << "Number of cities:\t" << amountOfCities << std::endl << std::endl;
    
    std::cout << "\t";
    for (auto i = 0; i < amountOfCities; i++) {
        std::cout << i << ".\t";
    }
    std::cout << "\v" << std::endl;
    for (auto i = 0; i < amountOfCities; i++) {
        for (auto j = 0; j < amountOfCities; j++) {
            if (j == 0) {
                if (arrayOfMatrixOfCities[i][j] < 0) {
                    std::cout << i << ".\t\b" << arrayOfMatrixOfCities[i][j];
                } else {
                    std::cout << i << ".\t" << arrayOfMatrixOfCities[i][j];
                }
            } else {
                if (arrayOfMatrixOfCities[i][j] < 0) {
                    std::cout << "\t\b" << arrayOfMatrixOfCities[i][j];
                } else {
                    std::cout << "\t" << arrayOfMatrixOfCities[i][j];
                }
            }
        }
        std::cout << "\v" << std::endl;
    }
}

// -------------------------------------------------------------------
// Algorytm zachłanny dla problemu komiwojażera.
// -------------------------------------------------------------------
void TravellingSalesmanProblem::GreedyAlgorithm() {
    if (arrayOfMatrixOfCities == nullptr)
        throw std::logic_error("Brak miast do przeprowadzenia algorytmu problemu komiwojażera.");
    
    if (optimalWay_Solution != nullptr)
        delete[] optimalWay_Solution;
    
    setGreedyAlgorithm = true;
    optimalWay_Solution = new int[amountOfCities];
    
    bool *visitedCities = new bool[amountOfCities];
    for (int i = 0; i < amountOfCities; i++) {
        visitedCities[i] = false;
    }
    
    length = 0;
    int currentMinLength;
    
    int nextCity = 0;
    int city=nextCity;
    visitedCities[city] = true;
    
    optimalWay_Solution[0] = nextCity;
    
    for (int j = 0; j < amountOfCities - 1; j++) {
        city = nextCity;
        currentMinLength = INT_MAX;
        for (int i = 0; i < amountOfCities; i++) {
            if (arrayOfMatrixOfCities[city][i] < currentMinLength && !visitedCities[i]) {
                currentMinLength = arrayOfMatrixOfCities[city][i];
                nextCity = i;
            }
        }
        visitedCities[nextCity] = true;
        optimalWay_Solution[j] = nextCity;
        length += arrayOfMatrixOfCities[city][nextCity];
    }
    optimalWay_Solution[amountOfCities - 1] = 0;
    length += arrayOfMatrixOfCities[optimalWay_Solution[amountOfCities - 2]][0];
    
    delete[] visitedCities;
}

// --------------------------------------------------------------------------------
// Funkcja rekurencyjna przeszukująca permutacje na potrzeby algorytmu zupełnego.
// --------------------------------------------------------------------------------
void TravellingSalesmanProblem::CalculateTheMostOptimalPermutation(int amountOfElements, int *permutations) {
    if (amountOfElements == amountOfCities - 1) {
        int lengthInThisPermutation = 0;
        for (auto i = 0; i < amountOfCities - 1; i++) {
            lengthInThisPermutation += arrayOfMatrixOfCities[permutations[i]][permutations[i + 1]];
        }
        lengthInThisPermutation += arrayOfMatrixOfCities[permutations[amountOfCities - 1]][permutations[0]];
        if (lengthInThisPermutation < length) {
            length = lengthInThisPermutation;
            for (auto i = 0; i < amountOfCities; i++) {
                optimalWay_Solution[i] = permutations[i];
            }
            optimalWay_Solution[amountOfCities] = permutations[0];
        }
    } else {
        for (auto i = amountOfElements; i < amountOfCities; i++) {
            std::swap(permutations[amountOfElements], permutations[i]);
            CalculateTheMostOptimalPermutation(amountOfElements + 1, permutations);
            std::swap(permutations[amountOfElements], permutations[i]);
        }
    }
}

// -------------------------------------------------------------------
// Algorytm zupełny dla problemu komiwojażera.
// -------------------------------------------------------------------
void TravellingSalesmanProblem::BruteForceAlgorithm() {
    if (arrayOfMatrixOfCities == nullptr)
        throw std::logic_error("Brak miast do przeprowadzenia algorytmu problemu komiwojażera.");
    
    if (optimalWay_Solution != nullptr) {
        delete[] optimalWay_Solution;
    }
    
    setGreedyAlgorithm = false;
    optimalWay_Solution = new int[amountOfCities + 1];
    
    int *allPossiblePermutations = new int[amountOfCities];
    for (int i = 0; i < amountOfCities; i++) {
        allPossiblePermutations[i] = i;
    }
    
    length = INT_MAX;
    CalculateTheMostOptimalPermutation(0, allPossiblePermutations);
    
    delete[] allPossiblePermutations;
}


void TravellingSalesmanProblem::PrintSolution() {
    std::cout << "\e[1mSolution\e[0m" << std::endl;
    if (setGreedyAlgorithm) {
        std::cout << "\e[1mGreedy Algorithm\e[0m" << std::endl;
    } else {
        std::cout << "\e[1mFull Search Algorithm\e[0m" << std::endl;
    }
    
    std::cout << "-------------------" << std::endl;
    std::cout << "Length\t= " << length << std::endl;
    std::cout << "Path\t= ";
    if (setGreedyAlgorithm) {
        std::cout << "0 - ";
        for (auto i = 0; i < amountOfCities; i++) {
            if (i == amountOfCities - 1) {
                std::cout << optimalWay_Solution[i] << std::endl;
            } else {
                std::cout << optimalWay_Solution[i] << " - ";
            }
        }
    } else {
        for (auto i = 0; i < amountOfCities; i++) {
            std::cout << optimalWay_Solution[i] << " - ";
        }
        std::cout << "0" << std::endl;
    }
}
