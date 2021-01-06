#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

#include <graphs/pointset.hpp>
#include <graphs/distmap.hpp>

#include <tsp/christofides.hpp>
#include <tsp/tourweight.hpp>
#include <tsp/solve.hpp>

using std::string, std::cin, std::cout, std::endl, std::ifstream;

static int test_counter = 0;
static string test_name;

using namespace std::chrono;

class RandomGen {
 public:
  explicit RandomGen(size_t seed)
    : generator_(std::mt19937(seed)) {}
  
  double RandomDouble(int lo, int hi) {
    std::uniform_real_distribution<double> range(lo, hi);
    return range(generator_);
  }
  
  int RandomNumber(int lo, int hi) {
    std::uniform_int_distribution<int> range(lo, hi);
    return range(generator_);
  }
  
  int RandomNumber(int bound) {
    std::uniform_int_distribution<int> range(0, bound);
    return range(generator_);
  }
  
 private:
  std::mt19937 generator_;
};
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

void RunTest(FullyConnectedMetricGraph* graph, bool verbose = false) {
  std::cout << "---------------[ Test '" << test_name << "' ]---------------\n";
  
  //////////////////////////
  // Approximate solution
  ExecutionClock clock;
  
  auto hamilton_cycle = TSP::ChristofidesApproxSolve(graph);
  double approx = TSP::TourWeight(hamilton_cycle, graph);
  
  auto christofides_time = clock.Measure();
  
  //////////////////////////
  // Optimal solution
  clock.Restart();
  
  double opt = TSP::OptimalTourWeight(graph);
  
  auto brute_force_time = clock.Measure();
  
  double ratio = approx/opt;
  
  cout << "[ #vertices = " << graph->VerticesCount() << " ]" << '\n';
  cout << "Christofides tour cost: " << approx << "\t\t" << "-- elapsed " << christofides_time.count() << " ms\n";
  cout << "Optimal tour cost: " << opt << "\t\t\t\t" << "-- elapsed " << brute_force_time.count() << " ms\n";
  cout << "Cost ratio: " << ratio << endl;
  
  if (verbose) {
    graph->PrintAdjMatrix();
    for (auto v : hamilton_cycle) {
      cout << v << ' ';
    }
  }
  
  if (ratio > 1.5) {
    cout << "Test FAILED, ratio > 1.5" << std::endl;
    exit(1);
  }
}
void RunTest(FullyConnectedMetricGraph* graph, double best_solution) {
  std::cout << "---------------[ Test '" << test_name << "' ]---------------\n";
  
  //////////////////////////
  // Approximate solution
  ExecutionClock clock;
  
  auto hamilton_cycle = TSP::ChristofidesApproxSolve(graph);
  double approx = TSP::TourWeight(hamilton_cycle, graph);
  
  auto christofides_time = clock.Measure();
  
  double opt = best_solution;
  double ratio = approx/opt;
  
  cout << "[ #vertices = " << graph->VerticesCount() << " ]" << '\n';
  cout << "Christofides tour cost: " << approx << "\t\t" << "-- elapsed " << christofides_time.count() << " ms\n";
  cout << "Known best tour cost: " << opt << "\n";
  cout << "Cost ratio: " << ratio << endl;
  
  if (ratio > 1.5) {
    cout << "Test FAILED, ratio > 1.5" << std::endl;
    exit(1);
  }
}

void RunTestPoints(const std::vector<Point2D>& points) {
  PointSet graph(points);
  RunTest(&graph);
}
void RunTestPoints(const std::vector<Point2D>& points, double best_solution) {
  PointSet graph(points);
  RunTest(&graph, best_solution);
}

void RunTest(const string& filename, bool verbose = false) {
  ifstream file(filename, std::ios::in);
  string test;
  std::getline(file, test);
  
  string test_type;
  std::getline(file, test_type);
  
  std::vector<Point2D> points;
  int num_v = 0;
  file >> num_v;
  
  for (int i = 0; i < num_v; ++i) {
    Point2D point = { 0, 0 };
    file >> point;
    
    points.push_back(point);
  }
  
  PointSet graph(points);
  RunTestPoints(points);
}
void RunTestRandomPoints(RandomGen& gen, bool verbose = false) {
  std::vector<Point2D> points;
  
  int num_v = gen.RandomNumber(8, 10);
  for (int i = 0; i < num_v; ++i) {
    double x = gen.RandomDouble(-10, 10);
    double y = gen.RandomDouble(-10, 10);
    
    points.push_back({ x, y });
  }
  
  RunTestPoints(points);
}

void RunPresettedTest(const string& filename) {
  ifstream file(filename, std::ios::in);
  
  if (!file) {
    std::cout << "Couldn't open file '" << filename << "'" << std::endl;
    exit(1);
  }
  
  double best_solution = 0;
  
  std::vector<Point2D> points;
  int num_v = 0;
  
  file >> num_v;
  file >> best_solution;
  
  string type;
  file >> type;
  
  if (type == "edges") {
    // Parse edges and perceive the graph as 2D points set
  
    for (int i = 0; i < num_v; ++i) {
      Point2D point = {0, 0};
      file >> point;
    
      points.push_back(point);
    }
  
    PointSet graph(points);
    RunTestPoints(points, best_solution);
    
  } else if (type == "matrix") {
    // Read cost matrix
    
    WeightsMatrix mat(num_v, std::vector<double>(num_v, 0));
    
    for (int i = 0; i < num_v; ++i) {
      for (int j = 0; j < num_v; ++j) {
        file >> mat[i][j];
      }
    }
    
    DistMap distmap(num_v, mat);
    RunTest(&distmap, best_solution);
  }
}

void RunAllTests(bool verbose = false) {
  ///////////////////
  // Random generated points on a plane
  
  size_t num_random_tests = 100;

  RandomGen gen(42);
  for (int i = 0; i < num_random_tests; ++i) {
    test_name = "random-points-" + std::to_string(++test_counter);

    RunTestRandomPoints(gen, verbose);
  }
  
  ////////////////////
  // Large tests
  
  string test_dir = "tests";
  auto test_files = { "us48.in", "tsplib42.in", "tsplib26.in", "gr17.in", "p01.in" };
  for (auto test : test_files) {
    test_name = test;
    RunPresettedTest("../" + test_dir + '/' + test);
  }
  
  std::cout << "Test passed – OK" << std::endl;
}

int main() {
  RunAllTests(false);
}