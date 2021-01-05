#include "solve.hpp"
#include "tourweight.hpp"

double TSP::OptimalTourWeight(FullyConnectedMetricGraph *graph) {
  double answer = std::numeric_limits<double>::max();
  int n = graph->VerticesCount();
  
  std::vector<Vertex> permutation;
  permutation.reserve(n);
  for (int i = 0; i < n; ++i) {
    permutation.push_back(i);
  }
  
  do {
    double weight = TSP::TourWeight(permutation, graph);
    if (weight < answer) {
      answer = weight;
    }
  }
  while (std::next_permutation(permutation.begin(), permutation.end()));
  
  return answer;
}
