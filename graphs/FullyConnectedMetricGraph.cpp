//
// Created by Igor Maximov on 04.01.2021.
//

#include "FullyConnectedMetricGraph.hpp"

#include <iostream>

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

using WeightList = IGraph::WeightList;
using EdgeList = IGraph::EdgeList;

std::pair<EdgeList, WeightList> FullyConnectedMetricGraph::EdgesWeights() const {
//  std::cerr << "Don't use this" << std::endl;
//  exit(1);

  EdgeList edges;
  WeightList weights;

  for (Vertex u = 0; u < VerticesCount(); ++u) {
    for (Vertex v = 0; v < VerticesCount(); ++v) {
      if (v > u) {
        edges.push_back({ u, v });
        weights.push_back(weights_[u][v]);
      }
    }
  }
  
  return std::make_pair(std::move(edges), std::move(weights));
}

void FullyConnectedMetricGraph::PrintAdjMatrix() const {
  for (Vertex u = 0; u < VerticesCount(); ++u) {
    for (Vertex v = 0; v < VerticesCount(); ++v) {
      std::cout << GetWeight(u, v) << "\t\t";
    }
    std::cout << "\n";
  }
}
