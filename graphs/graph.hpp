//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

#include <interface/IMutableGraph.hpp>

struct Edge {
  double weight;
  Vertex from;
  Vertex to;
};

bool operator<(const Edge& lhs, const Edge& rhs);

class Graph : public IMutableGraph {
 public:
  explicit Graph(const int num_vertices)
    : next_vertices_(num_vertices, std::vector<std::pair<Vertex, double>>()),
      num_vertices_(num_vertices) {}
  
  Graph(int, const std::vector<Edge>&);
  
  double GetWeight(Vertex vertex, Vertex vertex1) const override;
  
  size_t VerticesCount() const override;
  void GetNextVertices(Vertex, std::vector<Vertex>&) const override;
  void AddEgde(Vertex, Vertex, double) override;
  
  // With weights
  void GetNextVertices(Vertex, std::vector<std::pair<Vertex, double>>&) const;
 
 private:
  const int num_vertices_;
  std::vector<std::vector<std::pair<Vertex, double>>> next_vertices_;
};
