#pragma once

#include <graphs/FullyConnectedMetricGraph.hpp>

using HamiltonCycle = std::vector<Vertex>;

namespace TSP {
  /* Brute-force solution, O(exp) */
  HamiltonCycle Solve(FullyConnectedMetricGraph* graph);
}