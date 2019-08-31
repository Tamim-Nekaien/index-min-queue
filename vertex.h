//
// Created by Nathan on 5/27/2019.
// Commented by Tamim

#ifndef VERTEX_H_
#define VERTEX_H_

#include <vector>
#include <limits>
#include "edge.h"
// vertex object
class Vertex {
 public:
  // vertex constructor
  explicit Vertex(unsigned int begin) : begin(begin) {}
  // Adds an edge with an end and weight
  void AddEdge(unsigned int end, double weight);
  // Adds edge with a start, end, and weight
  void AddEdge(unsigned int start, unsigned int end, double weight);
  // Find the edge of vertex and return it
  Edge findEdge(unsigned int end);
  // adjacent vertex
  std::vector<unsigned int> Adj();
  // The first vertex
  unsigned int Begin();
  // Length of a vertex
  double Length(unsigned int end);
 private:
  // check if vertex contains edge
  bool Contains(unsigned int end);
  unsigned int begin;
  // vector holds edges
  std::vector<Edge> edges;
};
// Adding a vertex at the end of edges if one is not there
void Vertex::AddEdge(unsigned int end, double weight) {
  if (!Contains(end)) {
    edges.emplace_back(Edge(Begin(), end, weight));
  }
}
// Call adjacent vertex of vector, edges in the vector,
// for edges in vector, if the first vertex is the beginning edge
// push the adjecent vector to edge's end
std::vector<unsigned int> Vertex::Adj() {
  std::vector<unsigned int> adj;
  for (auto& e : edges) {
    if (e.Start() == begin) {
      adj.push_back(e.End());
    } else {
      adj.push_back(e.Start());
    }
  }
  return adj;
}
// return the beginning vertex
unsigned int Vertex::Begin() {
  return begin;
}
// returns the weight of the edges
double Vertex::Length(unsigned int end) {
  for (unsigned int i = 0; i < edges.size(); i++) {
    if (edges[i].End() == end && edges[i].Start() == begin) {
      return edges[i].Weight();
    }
    if (edges[i].End() == begin && edges[i].Start() == end) {
      return edges[i].Weight();
    }
  }
  return std::numeric_limits<double>::max();
}
// checks whether a vertex contains an edge
bool Vertex::Contains(unsigned int end) {
  for (auto& e : edges) {
    if (e.End() == end && e.Start() == begin) {
      return true;
    } else if (e.Start() == end && e.End() == begin) {
      return true;
    }
  }
  return false;
}
// adds checks the starting vertex, if not there add one
void Vertex::AddEdge(unsigned int start, unsigned int end, double weight) {
  if (!Contains(start)) {
    edges.emplace_back(Edge(start, end, weight));
  }
}
// Finds an edge associated with a vertex (end)
Edge Vertex::findEdge(unsigned int end) {
  for (auto& e : edges) {
    if (e.End() == end && e.Start() == begin) {
      return e;
    } else if (e.Start() == end && e.End() == begin) {
      return e;
    }
  }
  return Edge(0, 0, std::numeric_limits<double>::max());
}

#endif  // VERTEX_H_
