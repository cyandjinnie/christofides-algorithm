//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

#include "IGraph.hpp"

class IMutableGraph : public IGraph {
 public:
  virtual void AddEgde(Vertex, Vertex, double) = 0;
  virtual void SetVerticesCount(size_t) = 0;
};
