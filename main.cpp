#include <iostream>
#include <fstream>
#include <chrono>

#include <graphs/pointset.hpp>
#include <tsp/christofides.hpp>
#include <tsp/tourweight.hpp>
#include <tsp/solve.hpp>

using std::string, std::cin, std::cout, std::endl, std::ifstream;

static int test_counter = 0;

using namespace std::chrono;

class ExecutionClock {
 public:
  ExecutionClock()
      : start(high_resolution_clock::now()) {}
  
  [[nodiscard]] microseconds Measure() const {
    auto stop = high_resolution_clock::now();
    
    return duration_cast<microseconds>(stop - start);
  }
  
  void Restart() {
    start = high_resolution_clock::now();
  }
  
 private:
  decltype(high_resolution_clock::now()) start;
};

void RunTest(const string& filename, bool verbose = false) {
  ifstream file(filename, std::ios::in);
  string test_name;
  std::getline(file, test_name);
  
  string test_type;
  std::getline(file, test_type);
  std::cout << "---------------[ " << test_counter << ": " << test_name << " ]---------------\n";
  
  std::vector<Point2D> points;
  int num_v = 0;
  file >> num_v;
  
  for (int i = 0; i < num_v; ++i) {
    Point2D point = { 0, 0 };
    file >> point;
    
    points.push_back(point);
  }
  
  PointSet graph(points);
  
  auto hamilton_cycle = TSP::ChristofidesApproxSolve(&graph);
  
  if (verbose) {
    graph.PrintAdjMatrix();
    for (auto v : hamilton_cycle) {
      cout << v << ' ';
    }
  }
  
  ExecutionClock clock;
  
  double approx = TSP::TourWeight(hamilton_cycle, &graph);
  
  auto christofides_time = clock.Measure();
  clock.Restart();
  
  double opt = TSP::OptimalTourWeight(&graph);
  
  auto brute_force = clock.Measure();
  
  cout << "[ #vertices = " << points.size() << " ]" << '\n';
  
  cout << "Christofides tour cost: " << approx << "\t\t" << "-- elapsed " << christofides_time.count() << " ms\n";
  cout << "Optimal tour cost: " << opt << "\t\t\t\t" << "-- elapsed " << brute_force.count() << " ms\n";
  cout << "Cost ratio: " << approx/opt << endl;
}

int main() {
  auto tests_list = { "test1.txt",
                      "test2.txt",
                      "test3.txt",
                      "test4.txt",
                      "test5.txt",
                      "test6.txt",
                      "test7.txt",
                      "test8.txt",
                      "test9.txt",
                      "test10.txt",
                      "test11.txt",
                      "test12.txt" };
  
  for (auto test : tests_list) {
    RunTest(test);
  }
}