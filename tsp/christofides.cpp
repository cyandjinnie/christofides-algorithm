#include "christofides.hpp"
#include <mst/prim.hpp>
#include <min-matching/matching.hpp>
#include <graphs/graph.hpp>

#include <unordered_map>
#include <set>
#include <iostream>
#include <stack>

// using Multigraph = std::map<Vertex, std::vector<Vertex>>;

std::set<Vertex> OddNodes(IGraph* g) {
  std::set<Vertex> ans;
  
  for (int i = 0; i < g->VerticesCount(); ++i) {
    std::vector<Vertex> next_vertices;
    g->GetNextVertices(i, next_vertices);
    
    if (next_vertices.size() % 2 != 0) {
      ans.insert(i);
    }
  }
  
  return ans;
}

christofides::Graph InducedSubgraph(IGraph* g, std::set<Vertex> nodes) {
  auto [edges, _] = g->EdgesWeights();
  
  std::vector<std::pair<Vertex, Vertex>> remaining_edges;
  
  for (auto e : edges) {
    auto [u, v] = e;
    
    if (nodes.find(u) != nodes.end()
        && nodes.find(v) != nodes.end()) {
      remaining_edges.push_back(e);
    }
  }
  
  christofides::Graph output;
  std::vector<Vertex> next_vertices;
  
  output.SetVerticesCount(g->VerticesCount());
  
  /*std::cout << "------\n";
  std::cout << "no. of edges left in odd subgraph: " << remaining_edges.size() << std::endl;*/
  for (auto [u, v] : remaining_edges) {
    // std::cout << u << ' ' << v << '\n';
    
    output.AddEgde(u, v, g->GetWeight(u, v));
  }
  
  return output;
}

christofides::Graph Combine(PairMatching& m, IGraph* mst) {
  christofides::Graph ans;
  ans.SetVerticesCount(mst->VerticesCount());
  
  auto [mst_edges, mst_weights] = mst->EdgesWeights();
  
  for (int i = 0; i < mst_edges.size(); ++i) {
    auto [u, v] = mst_edges[i];
    auto w = mst_weights[i];
    
    ans.AddEgde(u, v, w);
  }
  
  auto& [matching_edges, matching_weights] = m;
  
  for (int i = 0; i < matching_edges.size(); ++i) {
    auto [u, v] = matching_edges[i];
    auto w = matching_weights[i];
    
    ans.AddEgde(u, v, w);
  }
  
  return ans;
}

using EulerCycle = std::vector<Vertex>;

EulerCycle FindEulerCycle(IGraph* graph) {
  EulerCycle output;
  
  // Fill with 'false'
  std::vector<std::vector<bool>> used(
    graph->VerticesCount(),
    std::vector<bool>(graph->VerticesCount(), false));
  
  std::stack<Vertex> stack;
  stack.push(0);
  
  while (!stack.empty()) {
    auto w = stack.top();
    
    bool found_edge = false;
    
    std::vector<Vertex> next_vertices;
    graph->GetNextVertices(w, next_vertices);
    
    for (auto u : next_vertices) {
      if (!used[w][u]) {
        stack.push(u);
        used[w][u] = true;
        
        found_edge = true;
      }
    }
    
    if (!found_edge) {
      stack.pop();
      output.push_back(w);
    }
  }
  
  return output;
}

HamiltonCycle SkipDuplicateVertices(const EulerCycle& euler) {
  std::set<Vertex> visited;
  HamiltonCycle hamilton;
  
  for (auto v : euler) {
    if (visited.find(v) == visited.end()) {
      hamilton.push_back(v);
      visited.insert(v);
    }
  }
  
  return hamilton;
}

HamiltonCycle TSP::ChristofidesApproxSolve(FullyConnectedMetricGraph *graph) {
  MST::SpanningTree mst = MST::Prim(graph);
  
  auto [E, W] = mst.EdgesWeights();
  
  auto odd_nodes = OddNodes(&mst);
  auto induced_odd_graph = InducedSubgraph(graph, odd_nodes);
  PairMatching matching = FindMinPerfPairMatching(&induced_odd_graph);
  
  auto [mst_edges, mst_weights] = mst.EdgesWeights();
  
  auto multigraph = Combine(matching, &mst);
  auto euler_cycle = FindEulerCycle(&multigraph);
  
  return SkipDuplicateVertices(euler_cycle);
}

