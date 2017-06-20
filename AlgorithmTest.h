//
// Created by mrfarinq on 22.05.17.
//

#ifndef SDIZO_2_ALGORITHMTEST_H
#define SDIZO_2_ALGORITHMTEST_H

class AlgorithmTest {

public:
    AlgorithmTest();
    
    ~AlgorithmTest();
    
    void DiscreteKnapsackProblem_Test(int numberOfRepetitions, int maxValueForItem);
    
    void TravellingSalesmanProblem_Test_Greedy(int numberOfRepetitions, int maxDistanceBetweenCity);
    
    void TravellingSalesmanProblem_Test_BruteForce(int numberOfRepetitions, int maxDistanceBetweenCity);
};


#endif //SDIZO_2_ALGORITHMTEST_H
