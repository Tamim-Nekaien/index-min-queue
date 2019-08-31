//
// Created by Nathan on 5/27/2019.
// Commented by Tamim

#ifndef EDGE_H_
#define EDGE_H_

#include <limits>
// Edge object class is created here
class Edge {
 public:
   // Edge constructor
  Edge() : weight(std::numeric_limits<double>::max()) {}
  // every edge has a start point, end, and weight
  Edge(unsigned int start, unsigned int end, double weight) :
  start(start), end(end), weight(weight) {}
  unsigned int Start();
  unsigned int End();
  double Weight();
 private:
   // helper variables
  unsigned int start;
  unsigned int end;
  double weight;
};
// End returns given end value, start value, and weight
unsigned int Edge::End() {
  return end;
}

double Edge::Weight() {
  return weight;
}

unsigned int Edge::Start() {
  return start;
}

#endif  // EDGE_H_
