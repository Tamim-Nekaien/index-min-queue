//
// Created by Nathan on 5/27/2019.
// Commented by Tamim

#include <iostream>
#include <fstream>
#include <limits>
#include <math.h>
#include "graph.h"


int main(int argc, char* argv[]) {
  // Check if there are two arguments, error if not
  if (argc != 2) {
    std::cerr << "Usage: ./prim_mst <graph.dat>\n";
    return 1;
  }
  // open file
  std::ifstream ifs;
  ifs.open(argv[1]);
  if (!ifs) {
    std::cerr << "Error: cannot open file "
              << argv[1] << std::endl;
    return 1;
  }
  // check if there is a valid number on the first line
  int gsCheck = ifs.peek();
  if (gsCheck < '0' || gsCheck > '9') {
    std::cerr << "Error: invalid graph size\n";
    return 1;
  }
  // display answer
  try {
    // instance of Graph with file as parameter
    Graph graph(ifs);
    // create vector edges and set it equal to call graph function prim
    // Prim is where the tree is created (check file graph.h)
    std::vector<Edge> edges = graph.Prim();
    // initialize var totalDis for sum of weights
    double totalDis = 0;
    // for edges in edges
    for (auto &e : edges) {
      // if the weight is not the maximum finite value for numeric type
      if (e.Weight() != std::numeric_limits<double>::max()) {
        // if the start vertex in edge vector is less than () print value
        if (e.Start() - 1 <= 9999) {
          printf("%.4d", e.Start() - 1);
        } else {
          std::cout << e.Start() - 1;
        }
        // seperate the edge value
        std::cout << '-';
        // if the destination vertex in edge vector is less than () print value
        if (e.End() - 1 <= 9999) {
          printf("%.4d", e.End() - 1);
        } else {
          std::cout << e.End() - 1;
        }
        // display weight and round it
        std::cout << " (";
        double roundedWeight = roundf(e.Weight() * 100000) / 100000;
        printf("%.5f", roundedWeight);
        std::cout << ")\n";
        totalDis += e.Weight();
      }
    }
    // print the summation of all the weights
    printf("%.5f\n", totalDis);
  } catch (std::exception) {
    return 1;
  }
  // close file
  ifs.close();
  return 0;
}
