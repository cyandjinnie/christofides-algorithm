//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

// for size_t
#include <cstdio>
#include <vector>

using Vertex = size_t;

class IGraph {
 public:
  virtual size_t VerticesCount() const = 0;
  virtual double GetWeight(Vertex, Vertex) const = 0;
  virtual void GetNextVertices(Vertex, std::vector<Vertex>&) const = 0;
};