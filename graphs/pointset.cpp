//
// Created by Igor Maximov on 04.01.2021.
//

#include "pointset.hpp"

#include <cmath>

double PointSet::Distance(const Point2D& u, const Point2D& v) {
  double dx = u.x - v.x;
  double dy = u.y - v.y;
  return sqrt(dx*dx + dy*dy);
}

/* Constructor from points array */
PointSet::PointSet(const std::vector<Point2D> &points) {
  int num_vertices = points.size();
  weights_.clear();
  
  for (Vertex u = 0; u < num_vertices; ++u) {
    std::vector<double> current_row;
    
    for (Vertex v = 0; v < num_vertices; ++v) {
      double w = (v == u) ? 0 : Distance(points[u], points[v]);
      current_row.push_back(w);
    }
    
    weights_.emplace_back(std::move(current_row));
  }
}
