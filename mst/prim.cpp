//
// Created by Igor Maximov on 04.01.2021.
//

#include "prim.hpp"

namespace MST {

SpanningTree Prim(IGraph *graph) {
  const double inf = std::numeric_limits<double>::max();
  double weight_sum = 0;
  
  // (weight, from, to)
  std::set<Edge> edges;
  std::vector<double> min_edge(graph->VerticesCount(), inf);
  std::vector<bool> is_added(graph->VerticesCount(), false);
  
  std::vector<Edge> mst_edge_list;
  
  min_edge[0] = 0;
  is_added[0] = true;
  edges.insert({ 0, 0, 0 });
  
  for (int edges_added = 0; edges_added < graph->VerticesCount(); ++edges_added) {
    Edge e = *edges.begin();
    edges.erase(edges.begin());
    
    auto [key, prev, current] = e;
    weight_sum += key;
    is_added[current] = true;
    
    // Add to output tree, skip first iter
    if (prev != current) {
      mst_edge_list.push_back(e);
    }
    
    std::vector<Vertex> next_vertices;
    graph->GetNextVertices(current, next_vertices);
    
    for (auto next : next_vertices) {
      double weight = graph->GetWeight(current, next);
      
      if (weight < min_edge[next] && !is_added[next]) {
        /*edges.erase(std::make_pair(min_edge[next], next));
        min_edge[next] = weight;
        edges.emplace(min_edge[next], next);*/
        
        edges.erase({ min_edge[next], current, next });
        min_edge[next] = weight;
        edges.insert({ min_edge[next], current, next });
      }
    }
  }
  
  int num_vertices = graph->VerticesCount();
  
  // Minimal Spanning Tree we built
  return Graph(num_vertices, mst_edge_list);
}

}
