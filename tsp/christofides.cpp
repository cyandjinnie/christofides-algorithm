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
  EulerCycle output; // THIS IS MULTIGRAPH GOD DAMN IT
  
  // Fill with 'false'
  std::vector<std::vector<int>> times_left(
    graph->VerticesCount(),
    std::vector<int>(graph->VerticesCount(), 0));
  
  auto [E, _] = graph->EdgesWeights();
  for (auto [u, v] : E) {
    times_left[u][v]++;
  }
  
  // std::cout << E.size() << std::endl;
  
  std::stack<Vertex> stack;
  stack.push(0);
  
  while (!stack.empty()) {
    auto w = stack.top();
    
    bool found_edge = false;
    
    std::vector<Vertex> next_vertices;
    graph->GetNextVertices(w, next_vertices);
    
    std::set<Vertex> unique_vertices(next_vertices.begin(), next_vertices.end());
    next_vertices = std::vector<Vertex>(unique_vertices.begin(), unique_vertices.end());
    
    for (auto next : next_vertices) {
      int u = 0;
      int v = 0;
      
      if (next > w) {
        u = w;
        v = next;
      } else if (next < w) {
        u = next;
        v = w;
      } else {
        std::cerr << "WTF" << std::endl;
        exit(1);
      }
      
      if (times_left[u][v] > 0) {
        stack.push(next);
        --times_left[u][v];
        
        found_edge = true;
        break;
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
  
  auto odd_nodes = OddNodes(&mst);
  auto induced_odd_graph = InducedSubgraph(graph, odd_nodes);
  PairMatching matching = FindMinPerfPairMatching(&induced_odd_graph);
  
  auto multigraph = Combine(matching, &mst);
  
  // auto [E, _] = multigraph.EdgesWeights();
  // std::cout << "#edges in multigraph: " << E.size() << std::endl;
  
  auto euler_cycle = FindEulerCycle(&multigraph);
  
  return SkipDuplicateVertices(euler_cycle);
}

