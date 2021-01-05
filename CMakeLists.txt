cmake_minimum_required(VERSION 3.0)
project(christofides_algorithm)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Minimum-Cost-Perfect-Matching)
include_directories(mst)

set(MATCH_FRAMEWORK_SRC Minimum-Cost-Perfect-Matching/BinaryHeap.cpp
                        Minimum-Cost-Perfect-Matching/BinaryHeap.h
                        Minimum-Cost-Perfect-Matching/Globals.h
                        Minimum-Cost-Perfect-Matching/city-map.cpp
                        Minimum-Cost-Perfect-Matching/city-map.h
                        Minimum-Cost-Perfect-Matching/Matching.cpp
                        Minimum-Cost-Perfect-Matching/Matching.h)

add_executable(christofides_algorithm
        ${MATCH_FRAMEWORK_SRC}
        mst/prim.cpp
        mst/prim.hpp
        graphs/FullyConnectedMetricGraph.hpp
        interface/IGraph.hpp
        interface/IMutableGraph.hpp
        graphs/pointset.cpp
        graphs/pointset.hpp
        graphs/cityroadmap.hpp
        main.cpp
        graphs/graph.cpp
        graphs/graph.hpp
        graphs/FullyConnectedMetricGraph.cpp
        tsp/christofides.hpp
        tsp/christofides.cpp tsp/solve.hpp tsp/solve.cpp)
