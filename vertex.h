
#include <iostream>
#include <cstring>
#include "edge.h"
/* Name: Ishaan Varma
   Date: 6/9/2023
   Purpose: Where the vertex class is defined.
 */

class vertex {
 public:
  vertex(char nid);
  ~vertex();
  char id;
  class edge* all[20];
  int size;
};
