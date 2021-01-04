//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

#include <graphs/FullyConnectedMetricGraph.hpp>

#include <vector>

struct Point2D {
  double x;
  double y;
};

class PointSet : public FullyConnectedMetricGraph {
 public:
  explicit PointSet(const std::vector<Point2D>& points);
  
  /* Private methods */
 private:
  static double Distance(const Point2D&, const Point2D&);
  
 /* protected: */
 /*  WeightMatrix weights_ <- actual body */
};
