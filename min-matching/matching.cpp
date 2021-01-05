//
// Created by Igor Maximov on 04.01.2021.
//

#include "matching.hpp"

// External
#include <Minimum-Cost-Perfect-Matching/Matching.h>

#include <unordered_map>
#include <iostream>

namespace external {
  using Graph = Graph;
  using Matching = Matching;
}

struct Bimap {
  std::unordered_map<int, int> forward;
  std::unordered_map<int, int> back;
  
  void Insert(int u, int v) {
    forward.insert({ u, v });
    back.insert({ v, u });
  }
  
  int ToExternal(int u) {
    return forward.at(u);
  }
  
  int ToNative(int v) {
    return back.at(v);
  }
};

PairMatching FindMinPerfPairMatching(IGraph* graph) {
  auto [edges, weights] = graph->EdgesWeights();
  
  // std::list<std::pair<int, int>> edges_list(edges.begin(), edges.end());
  
  Bimap vertices_map;
  std::vector<bool> seen(graph->VerticesCount(), false); // seen vertices
  int vertices_cnt = 0;
  
  for (auto& [u, v] : edges) {
    if (!seen[u]) {
      int current_image = vertices_cnt++;
      vertices_map.Insert(u, current_image);
      seen[u] = true;
    }
    
    if (!seen[v]) {
      int current_image = vertices_cnt++;
      vertices_map.Insert(v, current_image);
      seen[v] = true;
    }
  }
  
  std::list<std::pair<int, int>> edges_list;
  
  int i = 0;
  for (auto& [u, v] : edges) {
    int u_stroke = vertices_map.ToExternal(u);
    int v_stroke = vertices_map.ToExternal(v);
    
    edges_list.emplace_back(u_stroke, v_stroke);
  
    // std::cout << u_stroke << ' ' << v_stroke << ' ' << weights[i] << std::endl;
    ++i;
  }
  
  external::Graph g(vertices_cnt);
  for (auto [u, v] : edges_list) {
    g.AddEdge(u, v);
  }
  external::Matching matching(g);
  
  auto [matching_edges, _] =
    matching.SolveMinimumCostPerfectMatching(weights);
  
  std::vector<std::pair<Vertex, Vertex>> ans_edges;
  std::vector<double> ans_weights;
  
  for (int i : matching_edges) {
    ans_edges.push_back(edges[i]);
    ans_weights.push_back(weights[i]);
  }
  
  return std::make_pair(std::move(ans_edges), std::move(ans_weights));
}