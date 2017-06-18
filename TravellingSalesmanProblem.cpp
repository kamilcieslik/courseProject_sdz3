//
// Created by mrfarinq on 16.06.17.
//

#include <fstream>
#include <random>
#include "TravellingSalesmanProblem.h"

TravellingSalesmanProblem::TravellingSalesmanProblem() : amountOfCities(0), arrayOfMatrixOfCities(nullptr) {

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
    PrintCitiesForTheTravellingSalesman();
}

void TravellingSalesmanProblem::PrintCitiesForTheTravellingSalesman() {
    if (arrayOfMatrixOfCities == nullptr)
        throw std::logic_error("Brak miast do wyświetlenia.");
    
    std::cout << "\e[1mProblem\e[0m" << std::endl << std::endl;
    std::cout << "Number of cities:\t" << amountOfCities << std::endl <<std::endl;
    
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

void TravellingSalesmanProblem::GreedyAlgorithm() {

}

void TravellingSalesmanProblem::BruteForceAlgorithm() {

}

void TravellingSalesmanProblem::PrintSolution() {

}
