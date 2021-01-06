#pragma once

#include "FullyConnectedMetricGraph.hpp"

class DistMap : public FullyConnectedMetricGraph {
 public:
  DistMap(int num_v, const WeightsMatrix& weights)
      : FullyConnectedMetricGraph(num_v, weights) {}
};
