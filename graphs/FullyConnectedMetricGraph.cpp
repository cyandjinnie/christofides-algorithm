//
// Created by Igor Maximov on 04.01.2021.
//

#include "FullyConnectedMetricGraph.hpp"

double FullyConnectedMetricGraph::GetWeight(Vertex u, Vertex v) const {
  assert(VertexExists(u));
  assert(VertexExists(v));
  
  return weights_[u][v];
}

size_t FullyConnectedMetricGraph::VerticesCount() const {
  return weights_.size();
}

void FullyConnectedMetricGraph::GetNextVertices(Vertex v, std::vector<Vertex> &next) const {
  next.clear();
  
  for (Vertex i = 0; i < VerticesCount(); ++i) {
    if (v != i) {
      next.push_back(i);
    }
  }
}

bool FullyConnectedMetricGraph::VertexExists(Vertex u) const {
  return u < VerticesCount();
}
