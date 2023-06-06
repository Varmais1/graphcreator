#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include <cstring>

class edge {
 public:
  class vertex* first;
  edge(vertex* nFirst, vertex* nSecond, int nWeight);
  vertex* second;
  int weight;
  vertex* otherPoint(vertex* point);
};
#endif
