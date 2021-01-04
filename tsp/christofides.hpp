#pragma once

#include <graphs/FullyConnectedMetricGraph.hpp>

using HamiltonCycle = std::vector<Vertex>;

namespace TSP {
  HamiltonCycle ChristofidesApproxSolve(FullyConnectedMetricGraph* graph);
}