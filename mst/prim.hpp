//
// Created by Igor Maximov on 04.01.2021.
//

#pragma once

#include <set>
#include <vector>

#include <graphs/graph.hpp>
#include <interface/IMutableGraph.hpp>

namespace MST {

using SpanningTree = Graph;

SpanningTree Prim(IGraph *graph);

}
