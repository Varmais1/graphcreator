#include "edge.h"
/* Name: Ishaan Varma
   Date: 6/9/2023
   Purpose: Where the dge class is implemented.
*/
edge::edge(vertex* nFirst, vertex* nSecond, int nWeight) {
  first = nFirst;
  second = nSecond;
  weight = nWeight;
}

vertex* edge::otherPoint(vertex* point) {
  if(point == first) {
    return second;
  }
  else if(point == second) {
    return first;
  }
  else {
    return NULL;
  }
}
