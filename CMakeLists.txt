cmake_minimum_required(VERSION 3.7)
project(courseProject_sdz3)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_RELEASE "-fno-rtti -O2")
SET(CMAKE_CXX_FLAGS_DEBUG "-fno-rtti -O2")

set(SOURCE_FILES
        AlgorithmTest.cpp
        AlgorithmTest.h
        DiscreteKnapsackProblem.cpp
        DiscreteKnapsackProblem.h
        main.cpp
        TimeMeasurement.cpp
        TimeMeasurement.h
        TravellingSalesmanProblem.cpp
        TravellingSalesmanProblem.h
        UsefulStructuresForAlgorithms.cpp
        UsefulStructuresForAlgorithms.h)

add_executable(courseProject_sdz3 ${SOURCE_FILES})