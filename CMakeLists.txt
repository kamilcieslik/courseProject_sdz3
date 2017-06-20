cmake_minimum_required(VERSION 3.8)
project(sdizo_3)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS_RELEASE "-fno-rtti -O2")
SET(CMAKE_CXX_FLAGS_DEBUG  "-fno-rtti -O2")

set(SOURCE_FILES main.cpp
        TravellingSalesmanProblem.cpp
        TravellingSalesmanProblem.h
        DiscreteKnapsackProblem.cpp
        DiscreteKnapsackProblem.h
        TimeMeasurement.cpp
        TimeMeasurement.h
        UsefulStructuresForAlgorithms.cpp
        UsefulStructuresForAlgorithms.h
        )
add_executable(sdizo_3 ${SOURCE_FILES})