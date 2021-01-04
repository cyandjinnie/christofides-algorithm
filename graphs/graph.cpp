//
// Created by Igor Maximov on 04.01.2021.
//

#include "graph.hpp"

#include <iostream>

bool operator<(const Edge& lhs, const Edge& rhs) {
  if (lhs.weight < rhs.weight) {
    return true;
  } else if (lhs.weight == rhs.weight) {
    if (lhs.from < rhs.from) {
      return true;
    } else if (lhs.from == rhs.from) {
      if (lhs.to < rhs.to) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

size_t Graph::VerticesCount() const {
  return next_vertices_.size();
}

void Graph::GetNextVertices(Vertex u, std::vector<Vertex>& next) const {
  next.clear();
  for (auto& [v, weight] : next_vertices_[u]) {
    next.push_back(v);
  }
}

void Graph::AddEgde(Vertex from, Vertex to, double weight) {
  assert(0 <= from && from < VerticesCount());
  assert(0 <= to && to < VerticesCount());
  next_vertices_[from].emplace_back(to, weight);
}

void Graph::GetNextVertices(Vertex u, std::vector<std::pair<Vertex, double>>& next) const {
  next = next_vertices_[u];
}

Graph::Graph(int num_vertices, const std::vector<Edge>& edges)
    : num_vertices_(num_vertices) {
  for (auto [w, u ,v] : edges) {
    next_vertices_[u].emplace_back(v, w);
    next_vertices_[v].emplace_back(u, w);
  }
}

double Graph::GetWeight(Vertex u, Vertex v) const {
  std::cerr << "Don't use this" << std::endl;
  exit(1);
}
