#ifndef EDGE_H
#define EDGE_H
#include <iostream>
#include <cstring>
/* Name: Ishaan Varma
   Date: 6/9/2023
   Purpose: Where the edge class is defined.
 */
class edge {
 public:
  class vertex* first;
  edge(vertex* nFirst, vertex* nSecond, int nWeight);
  vertex* second;
  int weight;
  vertex* otherPoint(vertex* point);
};
#endif
