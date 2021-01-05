//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

#include <graphs/graph.hpp>

using PairMatching = std::pair<std::vector<std::pair<Vertex, Vertex>>, std::vector<double>>;

/////////////////////////////////////////////////////////////////////////
// Interface between external code and our christofides environment

PairMatching FindMinPerfPairMatching(IGraph* graph);