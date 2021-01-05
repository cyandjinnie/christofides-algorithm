//
// Created by Igor Maximov on 04.01.2021.
//

#include "prim.hpp"

#include <map>
#include <iostream>

namespace MST {

SpanningTree Prim(IGraph *graph) {
  const double INF = std::numeric_limits<double>::max();
  
  std::vector<Edge> mst_edge_list;
  
  double weight_sum = 0;
  // (weight, from, to)
  std::set<std::pair<double, Vertex>> edges;
  std::vector<double> min_edge(graph->VerticesCount(), INF);
  std::map<Vertex, Vertex> prev_vertex;
  std::vector<bool> is_added(graph->VerticesCount(), false);
  min_edge[0] = 0;
  is_added[0] = true;
  edges.emplace(0, 0);
  for (int edges_added = 0; edges_added < graph->VerticesCount(); ++edges_added) {
    auto [key, current] = *edges.begin();
    edges.erase(edges.begin());
    weight_sum += key;
    is_added[current] = true;
    
    if (prev_vertex.find(current) != prev_vertex.end()) {
      // Add to output
      // std::cout << key << ' ' << prev_vertex[current] << ' ' << current << std::endl;
      
      mst_edge_list.push_back({ key, prev_vertex[current], current });
    }
    
    std::vector<Vertex> next_vertices;
    graph->GetNextVertices(current, next_vertices);
    
    for (auto next : next_vertices) {
      auto weight = graph->GetWeight(current, next);
      
      if (weight < min_edge[next] && !is_added[next]) {
        edges.erase(std::make_pair(min_edge[next], next));
        min_edge[next] = weight;
        edges.emplace(min_edge[next], next);
        
        prev_vertex[next] = current;
      }
    }
  }
  
  int num_vertices = graph->VerticesCount();
  
  // Minimal Spanning Tree we built
  return Graph(num_vertices, mst_edge_list);
}

}
