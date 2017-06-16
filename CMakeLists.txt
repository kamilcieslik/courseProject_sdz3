cmake_minimum_required(VERSION 3.8)
project(sdizo_3)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
        TravellingSalesmanProblem.cpp
        TravellingSalesmanProblem.h
        DiscreteKnapsackProblem.cpp
        DiscreteKnapsackProblem.h
        TimeMeasurement.cpp
        TimeMeasurement.h
        )
add_executable(sdizo_3 ${SOURCE_FILES})