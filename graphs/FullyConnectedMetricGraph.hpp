//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

#include "interface/IGraph.hpp"

using WeightsMatrix = std::vector<std::vector<double>>;

class FullyConnectedMetricGraph : public IGraph {
 public:
  FullyConnectedMetricGraph() = default;
  
  FullyConnectedMetricGraph(size_t num_vertices, WeightsMatrix weights)
    : weights_(std::move(weights)) {}
  
  double GetWeight(size_t, size_t) const override;
  size_t VerticesCount() const override;
  void GetNextVertices(Vertex, std::vector<Vertex>&) const override;
 
  /* Methods */
 protected:
  bool VertexExists(Vertex u) const;
 
  /* Members */
 protected:
  WeightsMatrix weights_;
};
