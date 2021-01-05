//
// Created by Igor Maximov on 04.01.2021.
//

#include "graph.hpp"

#include <iostream>
#include <vector>

namespace christofides {

bool operator<(const Edge &lhs, const Edge &rhs) {
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

void Graph::GetNextVertices(Vertex u, std::vector<Vertex> &next) const {
  next.clear();
  for (auto&[v, weight] : next_vertices_[u]) {
    next.push_back(v);
  }
}

void Graph::AddEgde(Vertex from, Vertex to, double weight) {
  // assert(0 <= from && from < VerticesCount());
  // assert(0 <= to && to < VerticesCount());
  
  next_vertices_[from].emplace_back(to, weight);
  next_vertices_[to].emplace_back(from, weight);
}

void Graph::GetNextVertices(Vertex u, std::vector<std::pair<Vertex, double>> &next) const {
  next = next_vertices_[u];
}

Graph::Graph(int num_vertices, const std::vector<Edge> &edges)
  : num_vertices_(num_vertices),
    next_vertices_(num_vertices, std::vector<std::pair<Vertex, double>>()){
  for (auto[w, u, v] : edges) {
    next_vertices_[u].emplace_back(v, w);
    next_vertices_[v].emplace_back(u, w);
  }
}

double Graph::GetWeight(Vertex u, Vertex v) const {
  double ans = 0;
  
  bool found = false;
  for (int i = 0; i < next_vertices_[u].size(); ++i) {
    auto [vertex, w] = next_vertices_[u][i];
    
    if (vertex == v) {
      found = true;
      ans = w;
    }
  }
  
  if (!found) {
    std::cerr << "Not found an edge!\n";
    exit(1);
  }
  
  return ans;
}

void Graph::SetVerticesCount(size_t new_cnt) {
  num_vertices_ = new_cnt;
  
  next_vertices_ = std::vector<std::vector<std::pair<Vertex, double>>>(
    new_cnt, std::vector<std::pair<Vertex, double>>());
}

using WeightList = IGraph::WeightList;
using EdgeList = IGraph::EdgeList;

std::pair<EdgeList, WeightList> Graph::EdgesWeights() const {
  EdgeList edges;
  WeightList weights;
  
  for (Vertex u = 0; u < VerticesCount(); ++u) {
    std::vector<Vertex> next_vertices;
    GetNextVertices(u, next_vertices);
    
    for (auto v : next_vertices) {
      double w = GetWeight(u, v);
      
      // Unique edges – to ensure
      if (v > u) {
        edges.emplace_back(u, v);
        weights.push_back(w);
      }
    }
  }
  
  return std::make_pair(std::move(edges), std::move(weights));
}

void Graph::PrintAdjMatrix() const {
  for (Vertex u = 0; u < VerticesCount(); ++u) {
    for (Vertex v = 0; v < VerticesCount(); ++v) {
      std::cout << GetWeight(u, v) << "\t\t";
    }
    std::cout << "\n";
  }
}

}