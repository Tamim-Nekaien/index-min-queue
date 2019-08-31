//
// Created by Nathan on 5/27/2019.
// Commented by Tamim

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <limits>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include "vertex.h"
#include "index_min_pq.h"

class Graph {
 public:
  // Create graph from input stream
  explicit Graph(std::ifstream &ifs);
  // Add an edge v-w
  void AddEdge(unsigned int v, unsigned int w, double weight);
  void AddEdge(unsigned int v, unsigned int w, double weight, int);
  // Vertices adjacent to v
  std::vector<unsigned int> Adj(unsigned int v);
  // Number of vertices
  unsigned int V();
  // Number of edges
  unsigned int E();
  // Return weight of length from beginning vertex to end
  double Length(unsigned int begin, unsigned int end);
  // vector of type Edge that uses function Prim
  std::vector<Edge> Prim();
 private:
   // vertex instance class from vertex.h
  std::vector<Vertex> vertexes;
  // number of Vertices
  unsigned int nv;
  // number of edges
  unsigned int ne = 0;
};
// code based off psuedocode
// uses spanning tree
std::vector<Edge> Graph::Prim() {
  // min pq has been initialized
  IndexMinPQ<double> minpq(ne+nv+1);
  // vector distance
  std::vector<double> dist(nv+1);
  // vector of type edge
  std::vector<Edge> edge(nv+1);
  // vector to keep track of
  std::vector<bool> marked(nv+1);
// check if a vertex has been visited
  for (unsigned int v = 1; v <= nv; v++) {
    dist[v] = std::numeric_limits<double>::max();
    edge[v];
    marked[v] = false;
  }
// if it has skip it
  for (unsigned int v = 1; v <= nv; v++) {
    if (marked[v]) {
      continue;
    }

    dist[v] = 0;
    // if it hasn't push it onto the queue
    minpq.Push(dist[v], v);
// while the queue is not empty
    while (minpq.Size()) {
      //remove top vertex from queue
      const auto& u = minpq.Top();
      minpq.Pop();
// mark vertex it as visited
      marked[u] = true;
// if an adjacent vector has been visited, mark it as visited
      for (auto& adj : Adj(u)) {
        if (marked[adj]) {
          continue;
        }
// if the length to the adjacent vector is less
//than current one, set that to new path
        if (Length(u, adj) < dist[adj]) {
          dist[adj] = Length(u, adj);
          edge[adj] = vertexes[u].findEdge(adj);
          if (minpq.Contains(adj)) {
            minpq.ChangeKey(dist[adj], adj);
          } else {
            minpq.Push(dist[adj], adj);
          }
        }
      }
    }
  }
  return edge;
}
// return number of vertices
unsigned int Graph::V() {
  return nv;
}
// return number of edges
unsigned int Graph::E() {
  return ne;
}
// adjacent vertex of current vertex v
std::vector<unsigned int> Graph::Adj(unsigned int v) {
  return vertexes[v].Adj();
}
// Adds edge to vertex [v] with a path [w] and weight[weight]
void Graph::AddEdge(unsigned int v, unsigned int w, double weight) {
  vertexes[v].AddEdge(w, weight);
}
// Adds length weight from one vertex to another
double Graph::Length(unsigned int begin, unsigned int end) {
  return vertexes[begin].Length(end);
}
// takes in file
Graph::Graph(std::ifstream &ifs) {
  // number of vertices
  unsigned int size;
  ifs >> size;
  for (unsigned int c = 0; c <= size; c++) {
    vertexes.emplace_back(Vertex(c));
  }
  nv = size;
  unsigned int start, end;
  double weight;
  // reading the file in the format written
  while (ifs >> start >> end >> weight) {
    // if there are more vertices than the size: error
    if (start >= size) {
      std::cerr << "Invalid source vertex number " << start << std::endl;
      throw std::out_of_range("Invalid source vertex number");
    }
    if (end >= size) {
      std::cerr << "Invalid dest vertex number " << end << std::endl;
      throw std::out_of_range("Invalid dest vertex number");
    }
    // if the weight is less than zero: error
    if (weight < 0) {
      std::cerr << "Invalid weight " << weight << std::endl;
      throw std::out_of_range("Invalid weight");
    }
    // Add edges
    AddEdge(start+1, end+1, weight);
    AddEdge(end+1, start+1, weight, 1);
    // increase number of edges in loop
    ne++;
  }
}

void Graph::AddEdge(unsigned int v, unsigned int w, double weight, int) {
  vertexes[v].AddEdge(w, v, weight);
}

#endif  // GRAPH_H_
