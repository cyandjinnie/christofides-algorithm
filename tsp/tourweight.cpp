#include "tourweight.hpp"

double TSP::TourWeight(HamiltonCycle tour, IGraph* graph) {
  double weight = 0;
  int n = tour.size();
  
  for (int i = 0; i < tour.size() - 1; ++i) {
    int u = tour[i];
    int v = tour[i + 1];
    
    double w = graph->GetWeight(u, v);
    weight += w;
  }
  
  weight += graph->GetWeight(tour[n - 1], tour[0]);
  
  return weight;
}
